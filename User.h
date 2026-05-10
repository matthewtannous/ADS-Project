/**
 * User.h
 * One user account: stores credentials, friend/close-friend lists (sets of
 * usernames), the user's posts (linked list), and a stack of notifications.
 * The Users class is declared a friend so it can mutate friend lists from
 * the central manager.
 */

#ifndef ADS_PROJECT_USER_H
#define ADS_PROJECT_USER_H

#include <iostream>
#include <list>
#include <stack>
#include <set>

#include "Notification.h"
#include "Post.h"
using namespace std;

// A single user account: credentials, friends, posts, and notifications
class User {
    //access the private add and remove functions
    friend class Users;

public:
    User(string username, string password) : username(username), password(password) {
    }

    string getUsername();
    string getPassword();
    string* getFriendsList() const;

    bool setPassword();

    //posts are stored individually in each user
    void addPost(Post p);
    // Print summary list of posts (description only)
    void displayPosts();
    // Print posts with like and comment counts
    void displayPostsDetailed() const;
    bool removePostAt(int index);
    // Return a pointer to the post at the given index, or nullptr if out of range
    Post* getPostAt(int index);
    void displayFriends();

    // True if `other` is in this user's friends list
    bool isFriend(const string& other) const;

    // Push a notification onto this user's stack
    void receiveNotification(const Notification& n);
    // Print notifications newest-first without consuming the stack
    void displayNotifications() const;
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
    //adjacency-list neighbors stored as sets of usernames; the username
    //can be used directly in the Users hashmap to reach the other user
    set<string> friendsList;
    set<string> closeFriendsList;
    //stores all posts in a linked list
    list<Post> postsList;
    //stack of notifications, newest on top (LIFO)
    stack<Notification> notificationsList;
};


#endif //ADS_PROJECT_USER_H
