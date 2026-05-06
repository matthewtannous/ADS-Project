cmake_minimum_required(VERSION 4.1)
project(ADS_Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(ADS_Project
        src/main.cpp
        src/Users.cpp
        src/Users.h
        src/User.cpp
        src/User.h
        src/utils.cpp
        src/utils.h
        src/Post.cpp
        src/Post.h
        src/Message.h
        src/Message.cpp
        src/MessageManager.h
        src/MessageManager.cpp
        src/Notification.h
        src/Notification.cpp
        src/NotificationManager.h
        src/NotificationManager.cpp)

target_include_directories(ADS_Project PRIVATE
        App
        Users
        Posts
        Utils
        Messaging
        Notifications)
