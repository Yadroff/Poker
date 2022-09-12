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
set(CMAKE_INCLUDE_CURRENT_DIR ON)
if (CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif ()
add_executable(PoluPoker main.cpp authentication.cpp authentication.h authentication.ui button.cpp button.h card.cpp card.h
        dialogwindow.cpp dialogwindow.h gameui.cpp gameui.h gameui.ui images.qrc mainwindow.h mainwindow.cpp player.h player.cpp screencontroller.h screencontroller.cpp
        seat.h seat.cpp senderreciver.h senderreciver.cpp serverconnecter.h serverconnecter.cpp sounds.qrc load.h load.cpp load.ui)
target_link_libraries(PoluPoker Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Network Qt5::Multimedia)

