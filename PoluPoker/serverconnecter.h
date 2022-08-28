#ifndef SERVERCONNECTER_H
#define SERVERCONNECTER_H

#include <QUdpSocket>
#include <iostream>

#include <QObject>

const quint16 UDP_SERVER_PORT = 45454;

class ServerConnecter : public QObject
{
    Q_OBJECT
public:
    explicit ServerConnecter(QObject *parent = nullptr);
    ~ServerConnecter();
    void setRun(bool run);
private:
    QString serverAddress_;
    quint16 serverPort_;
    QUdpSocket *socket_;
    bool runFlag;
private slots:
    void readData();
    void run();
signals:
    void finished(const QString &);
};

#endif // SERVERCONNECTER_H
