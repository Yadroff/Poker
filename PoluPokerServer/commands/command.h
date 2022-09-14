#ifndef COMMAND_H
#define COMMAND_H

#include <QJsonDocument>

class Command
{
public:
    ~Command(){}

    virtual QJsonDocument exec() = 0;
};

#endif // COMMAND_H
