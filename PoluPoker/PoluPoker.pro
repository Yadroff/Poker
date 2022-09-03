QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    authentication.cpp \
    button.cpp \
    card.cpp \
    gameui.cpp \
    load.cpp \
    main.cpp \
    mainwindow.cpp \
    player.cpp \
    screencontroller.cpp \
    seat.cpp \
    senderreciver.cpp \
    serverconnecter.cpp

HEADERS += \
    authentication.h \
    button.h \
    card.h \
    gameui.h \
    load.h \
    mainwindow.h \
    player.h \
    screencontroller.h \
    seat.h \
    senderreciver.h \
    serverconnecter.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    authentication.ui \
    gameui.ui \
    load.ui
RESOURCES += \
    images.qrc \
    sounds.qrc
