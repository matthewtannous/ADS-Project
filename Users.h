/**
 * A class to store all users.
 * Uses std::unordered_map, which is a C++ hashmap implementation
 */

#ifndef ADS_PROJECT_USERS_H
#define ADS_PROJECT_USERS_H

#include <unordered_map>
#include <iostream>

#include "User.h"
using namespace std;

// Stores all users
class Users {
public:
    bool login(const string &username, const string &password);
    bool signup(const string &username, const string &password);

    // For testing
    void printAllUsers();

    //adds and removes friends using a simple graph
    void addFriend(string a, string b);
    void removeFriend(string a, string b);

public:
    // string is the username, User contains all information about the User
    unordered_map<string, User> users;

};


#endif //ADS_PROJECT_USERS_H
