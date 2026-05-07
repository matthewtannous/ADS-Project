#include "User.h"

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

void User::removePost(const Post p) {
    postsList.remove(p);
}

void User::addFriend(const string& u) {
    friendsList.push_back(u);
    closeFriendsList.remove(u);
    notificationsList.push(Notification(username, "New friend"));
}

void User::removeFriend(const string& u) {
    friendsList.remove(u);
}

void User::addCloseFriend(const string& u) {
    closeFriendsList.push_back(u);
    friendsList.remove(u);
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
            cout << "Incorrect password. Try again, or enter Q to stop.\n ";
            return false;
        }
    }

    return false;
}