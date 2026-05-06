#include "User.h"

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

void User::addPost(const Post& p) {
    postsList.push_back(&p);
}

void User::removePost(Post& p) {
    postsList.remove(&p);
}

void User::addFriend(const string& u) {
    friendsList.push_back(u);
}

void User::removeFriend(const string& u) {
    friendsList.remove(u);
}
