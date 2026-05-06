cmake_minimum_required(VERSION 4.1)
project(ADS_Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(ADS_Project
        main.cpp
        Users.cpp
        Users.h
        User.cpp
        User.h
        utils.cpp
        utils.h
        Post.cpp
        Post.h
)

target_include_directories(ADS_Project PRIVATE
        App
        Users
        Posts
        Utils
        Messaging
        Notifications)
