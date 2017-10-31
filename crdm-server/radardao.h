#ifndef RADARDAO_H
#define RADARDAO_H

class QSqlDatabase;
class Radar;

class RadarDao
{
public:
    RadarDao(QSqlDatabase& database);
    void init() const;

    void addRadar(Radar& radar) const;
    void updateRadar(const Radar& radar) const;
    void removeRadar(int id) const;

private:
    QSqlDatabase& mDatabase;
};

#endif // RADARDAO_H
