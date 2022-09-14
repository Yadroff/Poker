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
        Commands/command.h
        Commands/commandcreate.h
        Commands/commandconnect.h
        Commands/commandauth.h
        Table/card.h
        Table/combination.h
        Table/player.h
        Table/table.h
        server.h
        sender.h
        )

set(SOURCES
        main.cpp
        Commands/commandcreate.cpp
        Commands/commandconnect.cpp
        Commands/commandauth.cpp
        Table/card.cpp
        Table/combination.cpp
        Table/player.cpp
        Table/table.cpp
        server.cpp
        sender.cpp
        )

set(RESOURCES
        image.qrc
        )

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} ${RESOURCES} ${QMLS})
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Network Qt5::Sql)

