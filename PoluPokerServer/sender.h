#ifndef POLUPOKERSERVER_SENDER_H
#define POLUPOKERSERVER_SENDER_H

#include <QUdpSocket>


class Sender: public QObject {
    Q_OBJECT
public:
    Sender();
    void setRunningFlag(bool flag);
private:
    bool runningFlag;
    int serverPort;
    QUdpSocket *socket_;
private slots:
    void run();
signals:
    void finished();
};


#endif
