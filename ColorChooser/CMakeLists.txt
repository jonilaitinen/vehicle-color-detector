cmake_minimum_required(VERSION 3.5)

project(APP LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

find_package(Qt5 COMPONENTS Core Gui Widgets  REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(app

main.cpp
        mainwindow.cpp 
        colordetector.cpp

mainwindow.h 
         colordetector.h

mainwindow.ui

  
)
target_link_libraries(app ${OpenCV_LIBS} Qt5::Core Qt5::Widgets Qt5::Gui  )