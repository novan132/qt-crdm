#ifndef RELAYDAO_H
#define RELAYDAO_H

#include <QVector>

#include "relay.h"

class QSqlDatabase;


class RelayDao
{
public:
    RelayDao(QSqlDatabase& database);
    void init() const;

    void addRelay(Relay relay) const;
    void updateRelay(const Relay relay) const;

    QVector<Relay> relays() const;
private:
    QSqlDatabase& mDatabase;
};

#endif // RELAYDAO_H
