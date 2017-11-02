#ifndef CRDMSERVER_H
#define CRDMSERVER_H

#include <QTcpServer>
#include <QList>
#include <QMap>
#include <QThread>

#include "workerclient.h"
#include "workerradar.h"
#include "radar.h"
#include "databasemanager.h"

class QTimer;

class CrdmServer: public QTcpServer
{
    Q_OBJECT
public:
    CrdmServer(QObject* parent = 0);
    ~CrdmServer();

private:
    void dispatchRadars();
    void removeWorkerRadars();

signals:
    void revisionUpdated(int revision);
    void radarDispatchAborted();
    void radarStatusesUpdated(QVector<Radar> radars);

public slots:
    void updateRadars();
    void updateRadarStatus(Radar radar);
    void updateRadarStatuses();

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    QMap<WorkerClient*, QThread*> mWorkerClients;
    QMap<WorkerRadar*, QThread*> mWorkerRadars;
    int mRevision;
    DatabaseManager& mDb;
    QVector<Radar> mRadars;
    QTimer* radarStatusNotifyTimer;
};

#endif // CRDMSERVER_H
