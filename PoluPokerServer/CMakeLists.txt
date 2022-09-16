cmake_minimum_required(VERSION 3.20)
project(PoluPokerServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Sql REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
include_directories("${CMAKE_SOURCE_DIR}")
set(HEADERS
        commands/command.h
        commands/commandcreate.h
        commands/commandconnect.h
        commands/commandauth.h
        table/card.h
        table/combination.h
        table/player.h
        table/table.h
        server.h
        sender.h
        )

set(SOURCES
        main.cpp
        commands/commandcreate.cpp
        commands/commandconnect.cpp
        commands/commandauth.cpp
        table/card.cpp
        table/combination.cpp
        table/player.cpp
        table/table.cpp
        server.cpp
        sender.cpp
        )

set(RESOURCES
        image.qrc
        )

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} ${RESOURCES} ${QMLS})
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Network Qt5::Sql)

