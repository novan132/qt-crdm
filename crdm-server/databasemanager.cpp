
#include <QSqlDatabase>

#include "databasemanager.h"

DatabaseManager &DatabaseManager::instance()
{
    static DatabaseManager singleton;
    return singleton;
}

DatabaseManager::~DatabaseManager()
{
    mDatabase->close();
    delete mDatabase;
}

DatabaseManager::DatabaseManager(const QString &path):
    mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))),
    radarDao(*mDatabase),
    relayDao(*mDatabase)
{
    mDatabase->setDatabaseName(path);
    mDatabase->open();

    radarDao.init();
    relayDao.init();
}
