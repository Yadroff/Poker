cmake_minimum_required(VERSION 3.20)
project(PoluPoker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Multimedia REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
include_directories("${CMAKE_SOURCE_DIR}")
set(HEADERS
        authentication/authentication.h
        gameUI/card.h
        gameUI/gameui.h
        gameUI/player.h
        gameUI/seat.h
        menu/mainwindow.h
        serverChatting/senderreciver.h
        serverChatting/serverconnecter.h
        load.h
        button.h
        screencontroller.h
        )

set(SOURCES
        main.cpp
        authentication/authentication.cpp
        gameUI/card.cpp
        gameUI/gameui.cpp
        gameUI/player.cpp
        gameUI/seat.cpp
        menu/mainwindow.cpp
        serverChatting/senderreciver.cpp
        serverChatting/serverconnecter.cpp
        load.cpp
        button.cpp
        screencontroller.cpp
        )

set(UIS
        authentication/authentication.ui
        gameUI/gameui.ui
        load.ui
        )

set(RESOURCES
        images.qrc
        sounds.qrc
        )

set(QMLS
        )

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} ${RESOURCES} ${QMLS} ${UIS})
target_link_libraries(PoluPoker Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Network Qt5::Multimedia)

