#include "commandcreate.h"
#include <QDebug>

/*!
 * @brief Конструктор класса команды создания стола
 * @param tables - мапа [название стола, стол *]
 * @param name - название нового стола
 * @param size - размер нового стола
 */
CommandCreate::CommandCreate(QMap<QString, Table*> &tables, QString &name, int &size):
    tableName_(name), tableSize_(size), map_(tables)
{}

/*!
 * @brief Исполнение команды создания стола
 * @return JSON документ с результатом выполнения команды
 */
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
	return doc;
}
