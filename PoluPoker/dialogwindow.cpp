#include "dialogwindow.h"
#include <QBoxLayout>
#include <iostream>

DialogWindow::DialogWindow(QWidget *parent)
    : QWidget{parent}
{
    auto *layout = new QBoxLayout(QBoxLayout::TopToBottom);
    auto *lineLayout = new QHBoxLayout();
    edit_ = new QLineEdit();
    createTableButton_ = new Button("Crate table button", "Create");
    cancelButton_ = new Button("Cancel button", "Cancel");
    lineLayout->addWidget(edit_);
    lineLayout->addWidget(createTableButton_);
    layout->addLayout(lineLayout);
    layout->addWidget(cancelButton_);
    this->setLayout(layout);
    this->setFixedSize(500, 150);
}
