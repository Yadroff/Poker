#include "commandregist.h"
#include <QDebug>
CommandRegist::CommandRegist(QSqlDatabase *base, QString &login, QString &password, QObject *parent):
    QObject{parent}, base_(base), login_(login), password_(password)
{

}

QByteArray CommandRegist::exec()
{
    QJsonObject obj;
    QJsonDocument doc;
    obj.insert("command", "REGIST");
    QString answer;
    QSqlQuery qry;
    bool ok = qry.prepare("INSERT INTO Users (username, password) "
                          "VALUES (:username, :password)");
    if (!ok) {
        obj.insert("result", qry.lastError().text());
        doc.setObject(obj);
        QByteArray arr = doc.toJson(QJsonDocument::Indented);
        qDebug() << QString(arr);
        return arr;
    }
    qry.bindValue(":username", login_);
    qry.bindValue(":password", password_);

    if (qry.exec()) {
        obj.insert("result", "SUCCESS");
        doc.setObject(obj);
        QByteArray arr = doc.toJson(QJsonDocument::Indented);
        qDebug() << QString(arr);
        return arr;
    } else {
        obj.insert("result", qry.lastError().text());
        doc.setObject(obj);
        QByteArray arr = doc.toJson(QJsonDocument::Indented);
        qDebug() << QString(arr);
        return arr;
    }
//    qDebug() << "OPEARTION: REGIST " << login_ << password_ << answer;
}
