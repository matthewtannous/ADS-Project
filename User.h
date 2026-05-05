//
// Created by matthew on 5/5/26.
//

#ifndef ADS_PROJECT_USER_H
#define ADS_PROJECT_USER_H

#include <iostream>
using namespace std;

class User {
public:
    User(string username, string password) : username(username), password(password) {
    }

    string getUsername();
    string getPassword();


private:
    // string full_name;
    string username;
    string password;
};


#endif //ADS_PROJECT_USER_H
