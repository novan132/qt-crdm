#ifndef RADARDAO_H
#define RADARDAO_H

#include <QVector>

#include "radar.h"

class QSqlDatabase;

class RadarDao
{
public:
    RadarDao(QSqlDatabase& database);
    void init() const;

    void addRadar(Radar radar) const;
    void updateRadar(const Radar radar) const;
    void removeRadar(int id) const;
    QVector<Radar> radars() const;

private:
    QSqlDatabase& mDatabase;
};

#endif // RADARDAO_H
