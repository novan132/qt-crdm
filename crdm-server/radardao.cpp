
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>

#include "radardao.h"
#include "radar.h"

RadarDao::RadarDao(QSqlDatabase &database):
    mDatabase(database)
{

}

void RadarDao::init() const
{
    if (!mDatabase.tables().contains("radars")){
        QSqlQuery query(mDatabase);
        query.exec("CREATE TABLE radars (id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "name TEXT, port INTEGER, status TEXT)");
    }
}

void RadarDao::addRadar(Radar &radar) const
{
    QSqlQuery query(mDatabase);
    query.prepare("INSERT INTO radars (name, port, status)"
                  "VALUES (:name, :port, :status)");
    query.bindValue(":name", radar.name());
    query.bindValue(":port", radar.port());
    query.bindValue(":status", radar.status());
    query.exec();
    radar.setId(query.lastInsertId().toInt());
}

void RadarDao::updateRadar(const Radar &radar) const
{
    QSqlQuery query(mDatabase);
    query.prepare("UPDATE radars SET name = (:name), port = (:port), status = (:status)"
                  "WHERE id = (:id)");
    query.bindValue(":name", radar.name());
    query.bindValue(":port", radar.port());
    query.bindValue(":status", radar.status());
    query.bindValue(":id", radar.id());
    query.exec();
}

void RadarDao::removeRadar(int id) const
{
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM radars WHERE id = (:id)");
    query.bindValue(":id", id);
    query.exec();
}

QVector<Radar *> RadarDao::radars() const
{
    QSqlQuery query("SELECT * FROM radars", mDatabase);
    query.exec();

    // remember to delete Radar*
    QVector<Radar*> list;

    while (query.next()){
        Radar* radar = new Radar();
        radar->setId(query.value("id").toInt());
        radar->setName(query.value("name").toString());
        radar->setPort(query.value("port").toInt());
        radar->setStatus(query.value("status").toString());
        list.push_back(radar);
    }
    return list;
    // Radar* not deleted here
}
