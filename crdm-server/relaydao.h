#ifndef RELAYDAO_H
#define RELAYDAO_H

class QSqlDatabase;
class Relay;

class RelayDao
{
public:
    RelayDao(QSqlDatabase& database);
    void init() const;

    void addRelay(Relay& relay) const;
    void updateRelay(const Relay& relay) const;
private:
    QSqlDatabase& mDatabase;
};

#endif // RELAYDAO_H
