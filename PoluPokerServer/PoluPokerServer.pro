QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    table/card.cpp \
    table/combination.cpp \
    commands/commandconnect.cpp \
    commands/commandcreate.cpp \
    commands/commandauth.cpp \
    main.cpp \
    table/player.cpp \
    server.cpp \
    table/table.cpp \
    sender.cpp

HEADERS += \
    table/card.h \
    commands/command.h \
    commands/combination.h \
    commands/commandconnect.h \
    commands/commandcreate.h \
    commands/commandauth.h \
    table/player.h \
    server.h \
    table/table.h \
    sender.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
