/**
 * User.cpp
 * Implements the User class: post management, friend/close-friend
 * mutations, password change, and the notification stack.
 */

#include "User.h"

#include <algorithm>
#include "Notification.h"

string User::getPassword() {
    return password;
}

string User::getUsername() {
    return username;
}

string* User::getFriendsList() const{
    int size = friendsList.size();
    string* arr = new string[size];

    int i = 0;
    for (const string& f : friendsList) {
        arr[i++] = f;
    }
    return arr;
}

void User::addPost(Post p) {
    postsList.push_back(p);
}

void User::displayPosts() {
    if (postsList.empty()) {
        cout << "No posts yet.\n";
        return;
    }
    int i = 0;
    for (const Post& p : postsList) {
        cout << "[" << i++ << "] " << p.getDescription() << "\n";
    }
}

void User::displayPostsDetailed() const {
    if (postsList.empty()) {
        cout << "No posts yet.\n";
        return;
    }
    int i = 0;
    for (const Post& p : postsList) {
        cout << "[" << i++ << "] " << p.getDescription()
             << "  | likes: " << p.getLikesCount()
             << ", comments: " << p.getCommentCount()
             << "\n";
    }
}

bool User::removePostAt(int index) {
    if (index < 0 || static_cast<size_t>(index) >= postsList.size()) return false;
    auto it = postsList.begin();
    for (int i = 0; i < index; ++i) ++it;
    postsList.erase(it);
    return true;
}

Post* User::getPostAt(int index) {
    if (index < 0 || static_cast<size_t>(index) >= postsList.size()) return nullptr;
    auto it = postsList.begin();
    for (int i = 0; i < index; ++i) ++it;
    return &(*it);
}

void User::displayFriends() {
    if (friendsList.empty() && closeFriendsList.empty()) {
        cout << "No friends yet.\n";
        return;
    }
    if (!friendsList.empty()) {
        cout << "Friends:\n";
        for (const string& f : friendsList) cout << "  - " << f << "\n";
    }
    if (!closeFriendsList.empty()) {
        cout << "Close friends:\n";
        for (const string& f : closeFriendsList) cout << "  * " << f << "\n";
    }
}

bool User::isFriend(const string& other) const {
    return friendsList.count(other) > 0;
}

void User::receiveNotification(const Notification& n) {
    notificationsList.push(n);
}

void User::displayNotifications() const {
    if (notificationsList.empty()) {
        cout << "(no notifications)\n";
        return;
    }
    stack<Notification> tmp = notificationsList;
    int i = 0;
    while (!tmp.empty()) {
        const Notification& n = tmp.top();
        cout << "[" << i++ << "] " << n.description << "\n";
        tmp.pop();
    }
}

void User::addFriend(const string& u) {
    auto inserted = friendsList.insert(u); // returns pair<iterator, bool>
    if (!inserted.second) return; // already exists
    notificationsList.push(Notification(u, u + " added you as a friend"));
}

void User::removeFriend(const string& u) {
    friendsList.erase(u);          // removes if exists
    closeFriendsList.erase(u);     // must also remove from close friends
}

void User::addCloseFriend(const string& u) {
    auto inserted = closeFriendsList.insert(u);
    if (!inserted.second) return; // already exists
    // ensure it's also in friends
    friendsList.insert(u);
    notificationsList.push(Notification(u, u + " added you as a close friend"));
}

void User::removeCloseFriend(const string& u) {
    closeFriendsList.erase(u);
}

bool User::setPassword() {
    string inputPassword;
    while (true) {
        cout << "Enter your current password: ";
        cin >> inputPassword;

        if (inputPassword == password) {
            cout << "Enter your new password: ";
            cin >> password; // Can add checks for length, uppercase and lowercase...
            return true;
        } else if (inputPassword == "Q") {
            cout << "Stopped changing password\n";
            return false;
        } else {
            cout << "Incorrect password. Try again, or enter Q to stop.\n";
        }
    }

    return false;
}
