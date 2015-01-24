cmake_minimum_required(VERSION 2.8.4)
project(LeapGame)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    core/controllers/Game/GameController.cpp
    core/controllers/Home/HomeController.cpp
    core/controllers/Controller.cpp
    core/kernel/SFMLKernel.cpp
    include/Controller.hpp
    include/Game.hpp
    include/Home.hpp
    include/SFMLKernel.hpp
    leap/leap.cpp
    LeapEngine/includes/Leap.h
    LeapEngine/includes/LeapEngine.hpp
    LeapEngine/includes/LeapMath.h
    LeapEngine/src/LeapEngine.cpp
    LeapEngine/src/Sample.cpp
    main.cpp)

add_executable(LeapGame ${SOURCE_FILES})