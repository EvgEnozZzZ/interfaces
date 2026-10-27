#include "Database.h"

#include <QDate>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

Database::Database(QObject *parent)
    : QObject(parent)
{
    db_ = QSqlDatabase::addDatabase("QSQLITE");
    db_.setDatabaseName("fleet_dispatch.db");
}

bool Database::initialize()
{
    if (!db_.open()) {
        qWarning() << "Database open failed:" << db_.lastError().text();
        return false;
    }

    QSqlQuery query(db_);

    query.exec("CREATE TABLE IF NOT EXISTS vehicles ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "registration_number TEXT NOT NULL, "
               "brand TEXT NOT NULL, "
               "model TEXT NOT NULL, "
               "vehicle_type TEXT NOT NULL, "
               "capacity_tons REAL DEFAULT 0, "
               "mileage_km INTEGER DEFAULT 0, "
               "status TEXT NOT NULL, "
               "next_service_date TEXT, "
               "notes TEXT)");

    if (!query.isActive()) {
        qWarning() << "vehicles table creation failed:" << query.lastError().text();
        return false;
    }

    query.exec("CREATE TABLE IF NOT EXISTS drivers ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "full_name TEXT NOT NULL, "
               "license_number TEXT NOT NULL, "
               "license_category TEXT NOT NULL, "
               "phone TEXT, "
               "status TEXT NOT NULL, "
               "medical_check_date TEXT, "
               "notes TEXT)");

    if (!query.isActive()) {
        qWarning() << "drivers table creation failed:" << query.lastError().text();
        return false;
    }

    query.exec("CREATE TABLE IF NOT EXISTS trips ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "vehicle_id INTEGER NOT NULL, "
               "driver_id INTEGER NOT NULL, "
               "route_name TEXT NOT NULL, "
               "cargo TEXT, "
               "departure_date TEXT NOT NULL, "
               "priority TEXT NOT NULL, "
               "status TEXT NOT NULL, "
               "created_at TEXT DEFAULT CURRENT_DATE, "
               "FOREIGN KEY(vehicle_id) REFERENCES vehicles(id), "
               "FOREIGN KEY(driver_id) REFERENCES drivers(id))");

    if (!query.isActive()) {
        qWarning() << "trips table creation failed:" << query.lastError().text();
        return false;
    }

    query.exec("INSERT OR IGNORE INTO vehicles (id, registration_number, brand, model, vehicle_type, capacity_tons, mileage_km, status, next_service_date, notes) "
               "VALUES (1, 'А123БВ', 'Volvo', 'FH', 'Грузовой', 12.5, 125000, 'Свободен', '2026-11-10', 'Основной транспорт')");

    query.exec("INSERT OR IGNORE INTO vehicles (id, registration_number, brand, model, vehicle_type, capacity_tons, mileage_km, status, next_service_date, notes) "
               "VALUES (2, 'В456КТ', 'Mercedes', 'Actros', 'Грузовой', 10.0, 98000, 'В рейсе', '2026-10-25', 'Резервный транспорт')");

    query.exec("INSERT OR IGNORE INTO drivers (id, full_name, license_number, license_category, phone, status, medical_check_date, notes) "
               "VALUES (1, 'Иван Петров', 'AB1234567', 'C', '+7(900)111-22-33', 'Свободен', '2026-12-01', 'Опыт 8 лет')");

    query.exec("INSERT OR IGNORE INTO drivers (id, full_name, license_number, license_category, phone, status, medical_check_date, notes) "
               "VALUES (2, 'Сергей Кузнецов', 'CD7654321', 'C,E', '+7(900)555-44-66', 'В рейсе', '2026-11-14', 'Обслуживает дальние маршруты')");

    query.exec("INSERT OR IGNORE INTO trips (id, vehicle_id, driver_id, route_name, cargo, departure_date, priority, status) "
               "VALUES (1, 1, 1, 'Москва - Санкт-Петербург', 'Складские материалы', '2026-10-20', 'Высокий', 'Запланирован')");

    return query.isActive();
}

QList<QVariantMap> Database::getVehicles() const
{
    QList<QVariantMap> result;
    QSqlQuery query(db_);
    query.prepare("SELECT * FROM vehicles ORDER BY registration_number");
    if (!query.exec()) {
        qWarning() << "getVehicles failed:" << query.lastError().text();
        return result;
    }

    while (query.next()) {
        QVariantMap row;
        row["id"] = query.value("id");
        row["registration_number"] = query.value("registration_number");
        row["brand"] = query.value("brand");
        row["model"] = query.value("model");
        row["vehicle_type"] = query.value("vehicle_type");
        row["capacity_tons"] = query.value("capacity_tons");
        row["mileage_km"] = query.value("mileage_km");
        row["status"] = query.value("status");
        row["next_service_date"] = query.value("next_service_date");
        row["notes"] = query.value("notes");
        result.append(row);
    }

    return result;
}

QList<QVariantMap> Database::getDrivers() const
{
    QList<QVariantMap> result;
    QSqlQuery query(db_);
    query.prepare("SELECT * FROM drivers ORDER BY full_name");

    if (!query.exec()) {
        qWarning() << "getDrivers failed:" << query.lastError().text();
        return result;
    }

    while (query.next()) {
        QVariantMap row;
        row["id"] = query.value("id");
        row["full_name"] = query.value("full_name");
        row["license_number"] = query.value("license_number");
        row["license_category"] = query.value("license_category");
        row["phone"] = query.value("phone");
        row["status"] = query.value("status");
        row["medical_check_date"] = query.value("medical_check_date");
        row["notes"] = query.value("notes");
        result.append(row);
    }

    return result;
}

QList<QVariantMap> Database::getTrips() const
{
    QList<QVariantMap> result;
    QSqlQuery query(db_);
    query.prepare("SELECT t.id, t.route_name, t.cargo, t.departure_date, t.priority, t.status, "
                  "v.registration_number AS vehicle_name, d.full_name AS driver_name "
                  "FROM trips t "
                  "LEFT JOIN vehicles v ON v.id = t.vehicle_id "
                  "LEFT JOIN drivers d ON d.id = t.driver_id "
                  "ORDER BY t.departure_date DESC");

    if (!query.exec()) {
        qWarning() << "getTrips failed:" << query.lastError().text();
        return result;
    }

    while (query.next()) {
        QVariantMap row;
        row["id"] = query.value("id");
        row["route_name"] = query.value("route_name");
        row["cargo"] = query.value("cargo");
        row["departure_date"] = query.value("departure_date");
        row["priority"] = query.value("priority");
        row["status"] = query.value("status");
        row["vehicle_name"] = query.value("vehicle_name");
        row["driver_name"] = query.value("driver_name");
        result.append(row);
    }

    return result;
}

QMap<int, QString> Database::getVehicleNames() const
{
    QMap<int, QString> result;
    QSqlQuery query(db_);
    query.prepare("SELECT id, registration_number FROM vehicles ORDER BY registration_number");
    if (!query.exec()) {
        qWarning() << "getVehicleNames failed:" << query.lastError().text();
        return result;
    }

    while (query.next()) {
        result.insert(query.value("id").toInt(), query.value("registration_number").toString());
    }
    return result;
}

QMap<int, QString> Database::getDriverNames() const
{
    QMap<int, QString> result;
    QSqlQuery query(db_);
    query.prepare("SELECT id, full_name FROM drivers ORDER BY full_name");
    if (!query.exec()) {
        qWarning() << "getDriverNames failed:" << query.lastError().text();
        return result;
    }

    while (query.next()) {
        result.insert(query.value("id").toInt(), query.value("full_name").toString());
    }
    return result;
}

bool Database::addVehicle(const QVariantMap &data)
{
    QSqlQuery query(db_);
    query.prepare("INSERT INTO vehicles (registration_number, brand, model, vehicle_type, capacity_tons, mileage_km, status, next_service_date, notes) "
                  "VALUES (:registration_number, :brand, :model, :vehicle_type, :capacity_tons, :mileage_km, :status, :next_service_date, :notes)");
    query.bindValue(":registration_number", data.value("registration_number"));
    query.bindValue(":brand", data.value("brand"));
    query.bindValue(":model", data.value("model"));
    query.bindValue(":vehicle_type", data.value("vehicle_type"));
    query.bindValue(":capacity_tons", data.value("capacity_tons"));
    query.bindValue(":mileage_km", data.value("mileage_km"));
    query.bindValue(":status", data.value("status"));
    query.bindValue(":next_service_date", data.value("next_service_date"));
    query.bindValue(":notes", data.value("notes"));
    return query.exec();
}

bool Database::updateVehicle(int id, const QVariantMap &data)
{
    QSqlQuery query(db_);
    query.prepare("UPDATE vehicles SET registration_number = :registration_number, brand = :brand, model = :model, vehicle_type = :vehicle_type, capacity_tons = :capacity_tons, mileage_km = :mileage_km, status = :status, next_service_date = :next_service_date, notes = :notes WHERE id = :id");
    query.bindValue(":registration_number", data.value("registration_number"));
    query.bindValue(":brand", data.value("brand"));
    query.bindValue(":model", data.value("model"));
    query.bindValue(":vehicle_type", data.value("vehicle_type"));
    query.bindValue(":capacity_tons", data.value("capacity_tons"));
    query.bindValue(":mileage_km", data.value("mileage_km"));
    query.bindValue(":status", data.value("status"));
    query.bindValue(":next_service_date", data.value("next_service_date"));
    query.bindValue(":notes", data.value("notes"));
    query.bindValue(":id", id);
    return query.exec();
}

bool Database::deleteVehicle(int id)
{
    QSqlQuery query(db_);
    query.prepare("DELETE FROM vehicles WHERE id = :id");
    query.bindValue(":id", id);
    return query.exec();
}

bool Database::addDriver(const QVariantMap &data)
{
    QSqlQuery query(db_);
    query.prepare("INSERT INTO drivers (full_name, license_number, license_category, phone, status, medical_check_date, notes) "
                  "VALUES (:full_name, :license_number, :license_category, :phone, :status, :medical_check_date, :notes)");
    query.bindValue(":full_name", data.value("full_name"));
    query.bindValue(":license_number", data.value("license_number"));
    query.bindValue(":license_category", data.value("license_category"));
    query.bindValue(":phone", data.value("phone"));
    query.bindValue(":status", data.value("status"));
    query.bindValue(":medical_check_date", data.value("medical_check_date"));
    query.bindValue(":notes", data.value("notes"));
    return query.exec();
}

bool Database::updateDriver(int id, const QVariantMap &data)
{
    QSqlQuery query(db_);
    query.prepare("UPDATE drivers SET full_name = :full_name, license_number = :license_number, license_category = :license_category, phone = :phone, status = :status, medical_check_date = :medical_check_date, notes = :notes WHERE id = :id");
    query.bindValue(":full_name", data.value("full_name"));
    query.bindValue(":license_number", data.value("license_number"));
    query.bindValue(":license_category", data.value("license_category"));
    query.bindValue(":phone", data.value("phone"));
    query.bindValue(":status", data.value("status"));
    query.bindValue(":medical_check_date", data.value("medical_check_date"));
    query.bindValue(":notes", data.value("notes"));
    query.bindValue(":id", id);
    return query.exec();
}

bool Database::deleteDriver(int id)
{
    QSqlQuery query(db_);
    query.prepare("DELETE FROM drivers WHERE id = :id");
    query.bindValue(":id", id);
    return query.exec();
}

bool Database::addTrip(const QVariantMap &data)
{
    QSqlQuery query(db_);
    query.prepare("INSERT INTO trips (vehicle_id, driver_id, route_name, cargo, departure_date, priority, status) "
                  "VALUES (:vehicle_id, :driver_id, :route_name, :cargo, :departure_date, :priority, :status)");
    query.bindValue(":vehicle_id", data.value("vehicle_id"));
    query.bindValue(":driver_id", data.value("driver_id"));
    query.bindValue(":route_name", data.value("route_name"));
    query.bindValue(":cargo", data.value("cargo"));
    query.bindValue(":departure_date", data.value("departure_date"));
    query.bindValue(":priority", data.value("priority"));
    query.bindValue(":status", data.value("status"));
    return query.exec();
}

bool Database::updateTrip(int id, const QVariantMap &data)
{
    QSqlQuery query(db_);
    query.prepare("UPDATE trips SET vehicle_id = :vehicle_id, driver_id = :driver_id, route_name = :route_name, cargo = :cargo, departure_date = :departure_date, priority = :priority, status = :status WHERE id = :id");
    query.bindValue(":vehicle_id", data.value("vehicle_id"));
    query.bindValue(":driver_id", data.value("driver_id"));
    query.bindValue(":route_name", data.value("route_name"));
    query.bindValue(":cargo", data.value("cargo"));
    query.bindValue(":departure_date", data.value("departure_date"));
    query.bindValue(":priority", data.value("priority"));
    query.bindValue(":status", data.value("status"));
    query.bindValue(":id", id);
    return query.exec();
}

bool Database::deleteTrip(int id)
{
    QSqlQuery query(db_);
    query.prepare("DELETE FROM trips WHERE id = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QVariantMap Database::getSummary() const
{
    QVariantMap summary;
    QSqlQuery query(db_);

    query.exec("SELECT COUNT(*) FROM vehicles");
    if (query.next()) {
        summary["vehicles_total"] = query.value(0).toInt();
    }

    query.exec("SELECT COUNT(*) FROM drivers");
    if (query.next()) {
        summary["drivers_total"] = query.value(0).toInt();
    }

    query.exec("SELECT COUNT(*) FROM trips");
    if (query.next()) {
        summary["trips_total"] = query.value(0).toInt();
    }

    query.exec("SELECT COUNT(*) FROM vehicles WHERE status = 'Свободен'");
    if (query.next()) {
        summary["vehicles_available"] = query.value(0).toInt();
    }

    query.exec("SELECT COUNT(*) FROM drivers WHERE status = 'Свободен'");
    if (query.next()) {
        summary["drivers_available"] = query.value(0).toInt();
    }

    query.exec("SELECT COUNT(*) FROM trips WHERE status = 'Запланирован'");
    if (query.next()) {
        summary["trips_planned"] = query.value(0).toInt();
    }

    return summary;
}
