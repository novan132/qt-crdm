
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
