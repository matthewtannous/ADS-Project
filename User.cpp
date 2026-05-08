#include "User.h"

#include <algorithm>
#include "Notification.h"

string User::getPassword() {
    return password;
}

string User::getUsername() {
    return username;
}

string* User::getFriendsList() {
    int size = friendsList.size();
    string* arr = new string[size];

    int i = 0;
    for (const string& f : friendsList) {
        arr[i++] = f;
    }
    return arr;
}

void User::addPost(const Post p) {
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

bool User::removePostAt(int index) {
    if (index < 0 || static_cast<size_t>(index) >= postsList.size()) return false;
    auto it = postsList.begin();
    for (int i = 0; i < index; ++i) ++it;
    postsList.erase(it);
    return true;
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

void User::addFriend(const string& u) {
    if (find(friendsList.begin(), friendsList.end(), u) != friendsList.end()) return;
    friendsList.push_back(u);
    notificationsList.push(Notification(username, "New friend"));
}

void User::removeFriend(const string& u) {
    friendsList.remove(u);
    // can't be a close friend without being a friend
    closeFriendsList.remove(u);
}

void User::addCloseFriend(const string& u) {
    if (find(closeFriendsList.begin(), closeFriendsList.end(), u) != closeFriendsList.end()) return;
    closeFriendsList.push_back(u);
    // close friends are also friends
    if (find(friendsList.begin(), friendsList.end(), u) == friendsList.end()) {
        friendsList.push_back(u);
    }
    notificationsList.push(Notification(username, "New close friend"));
}

void User::removeCloseFriend(const string& u) {
    closeFriendsList.remove(u);
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