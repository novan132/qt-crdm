#include "relay.h"

Relay::Relay(qint8 id, const QString &name, const QString &status):
    mId(id),
    mName(name),
    mStatus(status)
{

}

Relay::~Relay()
{

}

qint8 Relay::id() const
{
    return mId;
}

void Relay::setId(qint8 id)
{
    mId = id;
}

QString Relay::name() const
{
    return mName;
}

void Relay::setName(const QString &name)
{
    mName = name;
}

QString Relay::status() const
{
    return mStatus;
}

void Relay::setStatus(const QString &status)
{
    mStatus = status;
}

