cmake_minimum_required(VERSION 4.1)
project(ADS_Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(ADS_Project
        main.cpp
        Users/Users.cpp
        Users/Users.h
        User/User.cpp
        User/User.h
        utils/utils.cpp
        utils/utils.h
        Users/Users.cpp)
