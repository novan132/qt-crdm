#include "radar.h"

Radar::Radar(int id, const QString &name, int port, const QString &status):
    mId(id),
    mName(name),
    mPort(port),
    mStatus(status)
{

}

Radar::~Radar()
{

}

int Radar::id() const
{
    return mId;
}

void Radar::setId(int id)
{
    mId = id;
}

QString Radar::name() const
{
    return mName;
}

void Radar::setName(const QString &name)
{
    mName = name;
}

int Radar::port() const
{
    return mPort;
}

void Radar::setPort(int port)
{
    mPort = port;
}

QString Radar::status() const
{
    return mStatus;
}

void Radar::setStatus(const QString &status)
{
    mStatus = status;
}


