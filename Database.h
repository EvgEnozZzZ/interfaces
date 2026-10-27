#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QSqlDatabase>
#include <QVariantMap>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);

    bool initialize();

    QList<QVariantMap> getVehicles() const;
    QList<QVariantMap> getDrivers() const;
    QList<QVariantMap> getTrips() const;

    QMap<int, QString> getVehicleNames() const;
    QMap<int, QString> getDriverNames() const;

    bool addVehicle(const QVariantMap &data);
    bool updateVehicle(int id, const QVariantMap &data);
    bool deleteVehicle(int id);

    bool addDriver(const QVariantMap &data);
    bool updateDriver(int id, const QVariantMap &data);
    bool deleteDriver(int id);

    bool addTrip(const QVariantMap &data);
    bool updateTrip(int id, const QVariantMap &data);
    bool deleteTrip(int id);

    QVariantMap getSummary() const;

private:
    QSqlDatabase db_;
};

#endif // DATABASE_H
