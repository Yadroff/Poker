#ifndef SENDERRECIVER_H
#define SENDERRECIVER_H

#include <QObject>
#include <QTcpSocket>

#include <QJsonDocument>

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

    QByteArray toJSON(const QString &string);
private slots:
    void readData();
    void parse(const QJsonDocument &json);
signals:
    void loginRegistFail(const QString &error);
    void loginRegistSuccess(const QStringList &tables);
	void createSuccess(const QString &name);
	void createError(const QString &error);
};

#endif // SENDERRECIVER_H
