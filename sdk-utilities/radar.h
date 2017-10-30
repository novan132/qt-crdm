#ifndef RADAR_H
#define RADAR_H

#include <QString>
#include <QDataStream>

#include "sdk-utilities_global.h"

class SDKUTILITIESSHARED_EXPORT Radar
{
public:
    explicit Radar(int id = -1, const QString& name = "", int port = -1, const QString& status = "");
    ~Radar();

    int id() const;
    void setId(int id);
    QString name() const;
    void setName(const QString& name);
    int port() const;
    void setPort(int port);
    QString status() const;
    void setStatus(const QString& status);

    friend QDataStream& operator<<(QDataStream& out, const Radar& radar);
    friend QDataStream& operator>>(QDataStream& in, Radar& radar);

private:
    int mId;
    QString mName;
    int mPort;
    QString mStatus;
};

inline QDataStream& operator<<(QDataStream& out, const Radar& radar)
{
    out << radar.mId
        << radar.mName
        << radar.mPort
        << radar.mStatus;
    return out;
}

inline QDataStream& operator>>(QDataStream& in, Radar& radar)
{
    in >> radar.mId
       >> radar.mName
       >> radar.mPort
       >> radar.mStatus;
    return in;
}

#endif // RADAR_H
