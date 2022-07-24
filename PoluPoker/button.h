#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

class Button: public QPushButton
{
    Q_OBJECT
public:
    Button(const QString &nameButton, const QString &buttonText);
};

#endif // BUTTON_H
