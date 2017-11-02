
#include <QDebug>

#include "crdmserver.h"

CrdmServer::CrdmServer(QObject *parent):
    QTcpServer(parent),
    mWorkerClients(),
    mWorkerRadars(),
    mRevision(0),
    mDb(DatabaseManager::instance()),
    mRadars(),
    radarStatusNotifyTimer(new QTimer(this))
{
    listen(QHostAddress::Any, 5000);
    radarStatusNotifyTimer->setInterval(3000);
    connect(radarStatusNotifyTimer, &QTimer::timeout,
            this, &CrdmServer::updateRadarStatuses);
}

CrdmServer::~CrdmServer()
{

}

void CrdmServer::dispatchRadars()
{
    QVector<Radar> radars = mDb.radarDao.radars();
    for (auto radar: radars){
        mRadars.push_back(radar);
        QThread* thread = new QThread(this);
        WorkerRadar* workerRadar = new WorkerRadar(radar);
        mWorkerRadars.insert(workerRadar, thread);
        workerRadar->moveToThread(thread);
        connect(this, &CrdmServer::radarDispatchAborted,
                workerRadar, &WorkerRadar::stopRadarUpdate);
        connect(thread, &QThread::started,
                workerRadar, &WorkerRadar::start);
        connect(workerRadar, &WorkerRadar::radarStatusUpdated,
                this, &CrdmServer::updateRadarStatus);
        thread->start();
    }
}

void CrdmServer::removeWorkerRadars()
{
    for (auto workerRadar: mWorkerRadars.keys()){
        QThread* thread = mWorkerRadars.take(workerRadar);
        thread->quit();
        thread->wait(1000);
        delete thread;
        delete workerRadar;
    }
}

void CrdmServer::updateRadars()
{
    emit radarDispatchAborted();
    radarStatusNotifyTimer->stop();
    removeWorkerRadars();
    mRadars.clear();
    dispatchRadars();
    mRevision++;
    emit revisionUpdated(mRevision);
    radarStatusNotifyTimer->start();
}

void CrdmServer::updateRadarStatus(Radar radar)
{
    for(Radar rd: mRadars){
        if (rd.id() == radar.id()){
            rd.status() = radar.status();
        }
    }
}

void CrdmServer::updateRadarStatuses()
{
    emit radarStatusesUpdated(mRadars);
}

void CrdmServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "Connected worker client";
    QThread* thread = new QThread(this);
    WorkerClient* client = new WorkerClient(socketDescriptor);
    int workerClientCount = mWorkerClients.keys().size();
    mWorkerClients.insert(client, thread);
    client->moveToThread(thread);

    connect(this, &CrdmServer::revisionUpdated,
            client, &WorkerClient::updateRevision);
    connect(client, &WorkerClient::radarsChanged,
            this, &CrdmServer::updateRadars);
    connect(this, &CrdmServer::radarStatusesUpdated,
            client, &WorkerClient::updateRadarStatuses);
    connect(thread, &QThread::started,
            client, &WorkerClient::start);

    thread->start();

    if (workerClientCount == 0 && mWorkerClients.size() == 1){
        dispatchRadars();
    }
    radarStatusNotifyTimer->start();
}
