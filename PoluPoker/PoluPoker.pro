QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    authentication/authentication.cpp \
    button.cpp \
    gameUI/card.cpp \
    gameUI/gameui.cpp \
    loader.cpp \
    main.cpp \
    menu/mainwindow.cpp \
    gameUI/player.cpp \
    screencontroller.cpp \
    gameUI/seat.cpp \
    serverChatting/senderreciver.cpp \
    serverChatting/serverconnecter.cpp

HEADERS += \
    authentication/authentication.h \
    button.h \
    gameUI/card.h \
    gameUI/gameui.h \
    loader.h \
    menu/mainwindow.h \
    gameUI/player.h \
    screencontroller.h \
    gameUI/seat.h \
    serverChatting/senderreciver.h \
    serverChatting/serverconnecter.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    authentication/authentication.ui \
    gameUI/gameui.ui \
    loader.ui
RESOURCES += \
    images.qrc \
    sounds.qrc
