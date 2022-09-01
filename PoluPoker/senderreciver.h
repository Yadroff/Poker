#ifndef SENDERRECIVER_H
#define SENDERRECIVER_H

#include <QObject>
#include <QTcpSocket>

class SenderReciver : public QObject
{
    Q_OBJECT
public:
    explicit SenderReciver(QTcpSocket *socket, QObject *parent = nullptr);
    ~SenderReciver();
public slots:
    void send(const QString &str);
private:
    QTcpSocket *socket_;
private slots:
    void readData();
    void parse(const QString &data);
    void parseLogin(const QVector<QString> &commands);
    void parseRegist(const QVector<QString> &commands);
signals:
    void loginRegistFail(const QString &error);
    void loginRegistSuccess();
};

#endif // SENDERRECIVER_H
