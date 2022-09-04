#include "commandcreate.h"
#include <QDebug>

CommandCreate::CommandCreate(QMap<QString, Table*> &tables, QString &name, int &size, QObject *parent):
    QObject{parent}, tableName_(name), tableSize_(size), map_(tables)
{}

QByteArray CommandCreate::exec()
{
    QJsonObject obj;
    obj.insert("command", "CREATE");
    QString result;
    if (map_.contains(tableName_)){
        result = "ALREADY EXISTS";
    } else{
        auto table = new Table(tableName_, tableSize_);
        map_.insert(tableName_, table);
        result = "SUCCESS";
    }
    obj.insert("result", result);
    QJsonDocument doc(obj);
    auto ans = doc.toJson(QJsonDocument::Indented);
    qDebug() << QString(ans);
    return ans;
}
