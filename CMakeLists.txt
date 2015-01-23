cmake_minimum_required(VERSION 2.8.4)
project(LeapGame)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system")

set(SOURCE_FILES main.cpp
                 core/controllers/Controller.cpp
                 core/controllers/Home/HomeController.cpp
                 core/controllers/Game/GameController.cpp
                 core/kernel/SFMLKernel.cpp)
add_executable(LeapGame ${SOURCE_FILES})