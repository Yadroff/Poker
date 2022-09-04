#ifndef COMMAND_H
#define COMMAND_H

#include <QByteArray>

class Command
{
public:
    virtual ~Command() = 0;

    virtual QByteArray exec() = 0;
};

#endif // COMMAND_H
