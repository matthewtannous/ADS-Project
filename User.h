//
// Created by matthew on 5/5/26.
//

#ifndef ADS_PROJECT_USER_H
#define ADS_PROJECT_USER_H

#include <iostream>
#include <list>
using namespace std;

class User {
    //access the private add and remove functions
    friend class Users;

public:
    User(string username, string password) : username(username), password(password) {
    }

    string getUsername();
    string getPassword();
    string* getFriends();

private:
    //add and remove friends individually
    //control them from the users class
    void addFriend(const string& u);
    void removeFriend(const string& u);

private:
    string username;
    string password;
    list<string> friendsList;


};


#endif //ADS_PROJECT_USER_H
