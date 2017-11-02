#include "workerradar.h"

WorkerRadar::WorkerRadar(Radar radar) :
    QObject(),
    mRadar(radar),
    mUdpSocket(this),
    mRadarBeatTimer(new QTimer(this)),
    mRadarNotifyTimer(new QTimer(this))
{

}

WorkerRadar::~WorkerRadar()
{
    delete mRadarBeatTimer;
    delete mRadarNotifyTimer;
}

void WorkerRadar::start()
{
    mUdpSocket.bind(mRadar.port());
    connect(&mUdpSocket, &QUdpSocket::readyRead,
            this, &WorkerRadar::readPendingDatagrams);

    mRadarBeatTimer->setInterval(3000);
    connect(mRadarBeatTimer, &QTimer::timeout,
            this, &WorkerRadar::updateRadarInactive);
    mRadarBeatTimer->start();

    mRadarNotifyTimer->setInterval(2000);
    connect(mRadarNotifyTimer, &QTimer::timeout,
            this, &WorkerRadar::notifyRadarStatus);
    mRadarNotifyTimer->start();
}

void WorkerRadar::notifyRadarStatus()
{
    emit radarStatusUpdated(mRadar);
}

void WorkerRadar::stopRadarUpdate()
{
    mRadarBeatTimer->stop();
    mRadarNotifyTimer->stop();
    mUdpSocket.close();
}

void WorkerRadar::readPendingDatagrams()
{
    mRadarBeatTimer->stop();
    QByteArray datagram;
    datagram.resize(mUdpSocket.pendingDatagramSize());
    mUdpSocket.readDatagram(datagram.data(), datagram.size());
    mRadar.setStatus("active");
    mRadarBeatTimer->start();
}

void WorkerRadar::updateRadarInactive()
{
    mRadar.setStatus("inactive");
}
