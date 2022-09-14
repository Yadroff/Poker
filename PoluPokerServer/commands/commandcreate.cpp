#include "commandcreate.h"
#include <QDebug>

CommandCreate::CommandCreate(QMap<QString, Table*> &tables, QString &name, int &size):
    tableName_(name), tableSize_(size), map_(tables)
{}

QJsonDocument CommandCreate::exec()
{
    QJsonObject obj;
    obj.insert("command", "CREATE");
    QString result;
    if (map_.contains(tableName_)){
        result = "ALREADY EXISTS";
    } else{
        auto table = new Table(tableName_, (char) tableSize_);
        map_.insert(tableName_, table);
        result = "SUCCESS";
    }
    obj.insert("result", result);
    QJsonDocument doc(obj);
}
