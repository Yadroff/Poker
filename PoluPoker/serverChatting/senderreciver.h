#ifndef SENDERRECIVER_H
#define SENDERRECIVER_H

#include <QObject>
#include <QTcpSocket>

#include <QJsonDocument>

class SenderReceiver : public QObject {
 Q_OBJECT
 public:
  explicit SenderReceiver(QTcpSocket *socket, QObject *parent = nullptr);
  ~SenderReceiver();
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
  void connectSuccess(const QString &name, const int &bet, const int &pot);
  void connectError(const QString &error);
  void addPlayerToTable(const QString &playerName, const int &seat, const int &money, const int &cards);
};

#endif // SENDERRECIVER_H
