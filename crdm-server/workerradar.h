#ifndef WORKERRADAR_H
#define WORKERRADAR_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>

#include "radar.h"

class WorkerRadar : public QObject
{
    Q_OBJECT
public:
    explicit WorkerRadar(Radar radar);
    ~WorkerRadar();
    void start();

signals:
    void radarStatusUpdated(Radar radar);

public slots:
    void stopRadarUpdate();

private slots:
    void notifyRadarStatus();
    void readPendingDatagrams();
    void updateRadarInactive();

private:
    Radar mRadar;
    QUdpSocket mUdpSocket;
    QTimer* mRadarBeatTimer;
    QTimer* mRadarNotifyTimer;
};

#endif // WORKERRADAR_H
