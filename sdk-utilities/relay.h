#ifndef RELAY_H
#define RELAY_H

#include <QString>
#include <QDataStream>

#include "sdk-utilities_global.h"

class SDKUTILITIESSHARED_EXPORT Relay
{
public:
    explicit Relay(qint8 id = -1, const QString& name = "", const QString& status = "");
    ~Relay();

    qint8 id() const;
    void setId(qint8 id);
    QString name() const;
    void setName(const QString& name);
    QString status() const;
    void setStatus(const QString& status);

    friend QDataStream& operator<<(QDataStream& out, const Relay& relay);
    friend QDataStream& operator>>(QDataStream& in, Relay& relay);

private:
    qint8 mId;
    QString mName;
    QString mStatus;
};

inline QDataStream& operator<<(QDataStream& out, const Relay& relay)
{
    out << relay.mId
        << relay.mName
        << relay.mStatus;
    return out;
}
inline QDataStream& operator>>(QDataStream& in, Relay& relay)
{
    in >> relay.mId
       >> relay.mName
       >> relay.mStatus;
    return in;
}

#endif // RELAY_H
