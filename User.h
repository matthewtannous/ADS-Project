#ifndef ADS_PROJECT_USER_H
#define ADS_PROJECT_USER_H

#include <iostream>
#include <list>
#include <vector>
#include <stack>

#include "Notification.h"
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

    bool setPassword();

    //posts are stored individually in each user
    void addPost(const Post p);
    void removePost(const Post p);
private:
    //add and remove friends individually
    //control them from the users class
    void addFriend(const string& u);
    void removeFriend(const string& u);
    void addCloseFriend(const string& u);
    void removeCloseFriend(const string& u);

private:
    string username;
    string password;
    //uses adjacency lists to  keep track of friends and close friends
    //the username can be direcly used in the hashmap later on to get to the user -> no need for pointers
    list<string> friendsList;
    list<string> closeFriendsList;
    //stores all posts in a linked list
    list<Post> postsList;
    //stores all notifications
    stack<Notification> notificationsList;
};


#endif //ADS_PROJECT_USER_H

