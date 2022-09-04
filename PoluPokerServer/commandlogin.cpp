#include "commandlogin.h"
#include <QDebug>

CommandLogin::CommandLogin(QSqlDatabase *base, QString &login, QString &password, QObject *parent)
    : QObject{parent}, base_(base), login_(login), password_(password)
{

}

QByteArray CommandLogin::exec()
{
    //TODO: Добавить эту проверку в сервер
//    QString answer;
//            foreach(auto &j, players_.keys()) {
//            if (players_[j] == username) {
//                answer = "LOGIN ALREADY LOGGED IN";
//                return answer;
//            }
//        }
    QSqlQuery qry;
    QJsonObject obj;
    QJsonDocument doc;
    obj.insert("command", "LOGIN");
    bool ok = qry.prepare("SELECT * FROM Users WHERE username = :username AND password = :password");
    if (!ok) {
        obj.insert("result" ,qry.lastError().text());
        doc.setObject(obj);
        QByteArray ans = doc.toJson(QJsonDocument::Indented);
        qDebug() << QString(ans);
        return ans;
    }
    qry.bindValue(":username", login_);
    qry.bindValue(":password", password_);
    if (!qry.exec()) {
        obj.insert("result", qry.lastError().text());
        doc.setObject(obj);
        QByteArray ans = doc.toJson(QJsonDocument::Indented);
        qDebug() << QString(ans);
        return ans;
    }
    if (qry.next()) {
        obj.insert("result", "SUCCESS");
        //TODO: добавить в список клиентов нового юзера
//        players_[clients_[id]] = username;
    } else {
        obj.insert("result", "FAIL");
    }
    doc.setObject(obj);
    QByteArray ans = doc.toJson(QJsonDocument::Indented);
    qDebug() << QString(ans);
    return ans;
}
