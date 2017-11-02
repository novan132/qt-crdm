
#include <QDebug>

#include "workerclient.h"
#include "messageutils.h"
#include "radar.h"
#include "relay.h"

WorkerClient::WorkerClient(int socketDescriptor) :
    QObject(),
    mSocketDescriptor(socketDescriptor),
    mSocket(this),
    mSocketReader(&mSocket),
    mDb(DatabaseManager::instance()),
    mRadars(mDb.radarDao.radars()),
    mRelays(mDb.relayDao.relays()),
    mRevision(0)
{

}

void WorkerClient::start()
{
    connect(&mSocket, &QTcpSocket::readyRead,
            this, &WorkerClient::readMessage);
    connect(&mSocket, &QTcpSocket::disconnected, [this]{

    });
    mSocket.setSocketDescriptor(mSocketDescriptor);
}

void WorkerClient::readMessage()
{
    auto message = MessageUtils::readMessage(mSocketReader);

    if (message.type == Message::Type::INVALID_REQUEST){
        return;
    }

    switch (message.type){
        case Message::Type::STATUS_REQUEST:
            handleStatusRequest(message);
            break;
        case Message::Type::RADAR_DELETE:
            handleRadarDelete(message);
            break;
        case Message::Type::RADAR_ADD:
            handleRadarAdd(message);
            break;
        case Message::Type::RELAY_COMMAND:
            handleRelayCommand(message);
            break;
        default:
            break;
    }
}

void WorkerClient::handleStatusRequest(Message &/*message*/)
{
    sendDataResult();
}

void WorkerClient::handleRadarDelete(Message &message)
{
    QDataStream in(&message.data, QIODevice::ReadOnly);
    int id;
    in >> id;
    mDb.radarDao.removeRadar(id);
    // update list radar
    mRadars = mDb.radarDao.radars();
    emit radarsChanged();
}

void WorkerClient::updateRevision(int revision)
{
    mRevision = revision;
    mRadars = mDb.radarDao.radars();
}

void WorkerClient::updateRadarStatuses(QVector<Radar> radars)
{
    for (Radar radar: mRadars){
        for (Radar r: radars){
            if (radar.id() == r.id()){
                radar.status() = r.status();
                break;
            }
        }
    }
}

void WorkerClient::handleRadarAdd(Message &message)
{
    QDataStream in(&message.data, QIODevice::ReadOnly);
    Radar radar;
    in >> radar;
    mDb.radarDao.addRadar(radar);
    // update list radar
    mRadars = mDb.radarDao.radars();
    emit radarsChanged();
}

void WorkerClient::handleRelayCommand(Message &message)
{
    QDataStream in(&message.data, QIODevice::ReadOnly);
    Relay relay;
    in >> relay;
    mDb.relayDao.updateRelay(relay);
    // update list relay
    mRelays = mDb.relayDao.relays();
}

void WorkerClient::sendDataResult()
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << mRadars
        << mRelays;
    MessageUtils::sendMessage(mSocket,
                              Message::Type::DATA_RESULT,
                              data,
                              mRevision);
}
