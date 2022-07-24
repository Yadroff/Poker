#include "button.h"
#include <QLabel>
#include <QBoxLayout>

Button::Button(const QString &nameButton, const QString &buttonText)
{
    this->setAccessibleName(nameButton);
    QPixmap pixmap(":/images/homeScreenRectButton.png");
    QIcon buttonIcon(pixmap);
    this->setIcon(buttonIcon);
    this->setIconSize(pixmap.rect().size());
    this->setFixedSize(pixmap.rect().size());
    this->setFlat(true);
    auto *text = new QLabel(buttonText);
    QFont font("Arial", 30, QFont::Bold);
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addStretch();
    layout->addWidget(text, 0, Qt::AlignCenter);
    text->setFont(font);
}
