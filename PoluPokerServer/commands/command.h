#ifndef COMMAND_H
#define COMMAND_H

#include <QJsonDocument>

class Command
{
public:
    ~Command()= default;

    virtual QJsonDocument exec() = 0;
};

#endif // COMMAND_H
