
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>

#include "relaydao.h"
#include "relay.h"

RelayDao::RelayDao(QSqlDatabase &database):
    mDatabase(database)
{

}

void RelayDao::init() const
{
    if (!mDatabase.tables().contains("relays")){
        QSqlQuery query(mDatabase);
        query.exec("CREATE TABLE relays (id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "name TEXT, status TEXT)");
    }
}

void RelayDao::addRelay(Relay &relay) const
{
    QSqlQuery query(mDatabase);
    query.prepare("INSERT INTO relays (name, status) "
                  "VALUES (:name, :status)");
    query.bindValue(":name", relay.name());
    query.bindValue(":status", relay.status());
    query.exec();
    relay.setId(query.lastInsertId().toInt());
}

void RelayDao::updateRelay(const Relay &relay) const
{
    QSqlQuery query(mDatabase);
    query.prepare("UPDATE relays SET name = (:name), status = (:status)"
                  "WHERE id = (:id)");
    query.bindValue(":name", relay.name());
    query.bindValue(":status", relay.status());
    query.bindValue(":id", relay.id());
}

QVector<Relay *> RelayDao::relays() const
{
    QSqlQuery query("SELECT * FROM relays", mDatabase);
    query.exec();

    // Remeber to delete Relay*
    QVector<Relay*> list;

    while (query.next()){
        Relay* relay = new Relay();
        relay->setId(query.value("id").toInt());
        relay->setName(query.value("name").toString());
        relay->setStatus(query.value("status").toString());
        list.push_back(relay);
    }
    return list;
    // Relay* not deleted here
}
