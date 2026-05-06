#ifndef ADS_PROJECT_USER_H
#define ADS_PROJECT_USER_H

#include <iostream>
#include <list>
#include <vector>

#include "Post.h"
using namespace std;

class User {
    //access the private add and remove functions
    friend class Users;

public:
    User(string username, string password) : username(username), password(password) {
    }

    string getUsername();
    string getPassword();
    string* getFriendsList();

    //posts are stored individually in each user
    void addPost(const Post& p);
    void removePost(const Post& p);
private:
    //add and remove friends individually
    //control them from the users class
    void addFriend(const string& u);
    void removeFriend(const string& u);

private:
    string username;
    string password;
    vector<string> friendsList;
    vector<Post> postsList;
};


#endif //ADS_PROJECT_USER_H
