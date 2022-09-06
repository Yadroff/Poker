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
set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_executable(PoluPokerServer main.cpp card.h card.cpp combination.cpp combination.h command.h commandconnect.h commandconnect.cpp
        commandcreate.h commandcreate.cpp commandlogin.h commandlogin.cpp commandregist.h commandregist.cpp image.qrc
        player.h player.cpp sender.h sender.cpp server.h server.cpp)
target_link_libraries(PoluPokerServer Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Network Qt5::Sql)

