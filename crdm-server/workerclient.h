#ifndef WORKERCLIENT_H
#define WORKERCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>

#include "message.h"
#include "databasemanager.h"

class Radar;
class Relay;

class WorkerClient : public QObject
{
    Q_OBJECT
public:
    explicit WorkerClient(int socketDescriptor);

signals:
    void radarsChanged(); // signal to notify owner of this class, that radar is changed

public slots:
    void start();
    //void handleRadarUpdate(Message& message);   // this function is also accessed from the owner of WorkerClient
    void updateRevision(int revision);
    void updateRadarStatuses(QVector<Radar> radars);

private slots:
    void readMessage();


private:
    void handleStatusRequest(Message& message);
    void handleRadarDelete(Message& message);
    void handleRadarAdd(Message& message);
    void handleRelayCommand(Message& message);
    void sendDataResult();

private:
    int mSocketDescriptor;
    QTcpSocket mSocket;
    QDataStream mSocketReader;
    DatabaseManager& mDb;
    QVector<Radar> mRadars;
    QVector<Relay> mRelays;
    int mRevision;

};

#endif // WORKERCLIENT_H
