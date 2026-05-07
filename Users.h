/**
 * A class to store all users.
 * Uses std::unordered_map, which is a C++ hashmap implementation
 */

#ifndef ADS_PROJECT_USERS_H
#define ADS_PROJECT_USERS_H

#include <unordered_map>
#include <iostream>
#include <list>
#include <utility>

// #include "Message.h"
#include "User.h"
using namespace std;

// Stores all users
class Users {
private:
    // Conversation represents one converstation between 2 users
    class Conversation {
        public:
        // users in conversation
        string user1, user2;

        /* All messages in the conversation
         * pair<string, bool> combines two values in one struct
         * string is the message content
         * bool: true if user1 sent the message, false if user2 sent the message (bool uses less memory)
         */
        list<pair<string, bool>> messages;
        Conversation(string user1, string user2);
        void addMessage(string sender, string message);
        void showMessages();
    };
public:
    bool login(const string &username, const string &password);
    bool signup(const string &username, const string &password);
    bool userExists(const string& username) const;

    // For testing
    void printAllUsers();

    //adds and removes friends using a simple graph
    void addFriend(string a, string b);
    void removeFriend(string a, string b);
    void addCloseFriend(string a, string b);
    void removeCloseFriend(string a, string b);

private:
    // string is the username, User contains all information about the User
    unordered_map<string, User> users;
    list<Conversation> conversationsList;
};


#endif //ADS_PROJECT_USERS_H
