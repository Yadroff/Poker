#ifndef DIALOGWINDOW_H
#define DIALOGWINDOW_H

#include <QLineEdit>
#include "button.h"
class DialogWindow : public QWidget
{
    Q_OBJECT
public:
    explicit DialogWindow(QWidget *parent = nullptr);
private:
    Button *createTableButton_;
    Button *cancelButton_;
    QLineEdit *edit_;
};

#endif // DIALOGWINDOW_H
