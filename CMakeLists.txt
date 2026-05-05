cmake_minimum_required(VERSION 4.1)
project(ADS_Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(ADS_Project
        App/main.cpp
        Users/Users.cpp
        Users/Users.h
        Users/User.cpp
        Users/User.h
        Utils/utils.cpp
        Utils/utils.h
        Users/Users.cpp
        Posts/Post.cpp
        Posts/Post.h
        Messaging/Message.h
        Messaging/Message.cpp
        Messaging/MessageManager.h
        Messaging/MessageManager.cpp
        Notifications/Notification.h
        Notifications/Notification.cpp
        Notifications/NotificationManager.h
        Notifications/NotificationManager.cpp)

target_include_directories(ADS_Project PRIVATE
        App
        Users
        Posts
        Utils
        Messaging
        Notifications)
