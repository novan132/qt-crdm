#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>

#include "radardao.h"
#include "relaydao.h"

class QSqlDatabase;

const QString DATABASE_FILENAME = "crdm.db";

class DatabaseManager
{
public:
    static DatabaseManager& instance();
    ~DatabaseManager();



protected:
    DatabaseManager(const QString& path = DATABASE_FILENAME);
    DatabaseManager& operator=(const DatabaseManager& rhs);

private:
    QSqlDatabase* mDatabase;

public:
    const RadarDao radarDao;
    const RelayDao relayDao;

};

#endif // DATABASEMANAGER_H
