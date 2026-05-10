/**
 * Users.h
 * Stores every account in the system and orchestrates cross-user actions
 * (friendships, likes, comments, messages, notifications).
 */

#ifndef ADS_PROJECT_USERS_H
#define ADS_PROJECT_USERS_H

#include <unordered_map>
#include <iostream>
#include <list>
#include <utility>

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
        // Insert a message at the front so newest appears first
        void addMessage(string sender, string message);
        // Print messages from newest to oldest
        void showMessages();
        // True if this conversation is exactly between users a and b
        bool involves(const string& a, const string& b) const;
        // True if user u is one of the two participants
        bool involves(const string& u) const;
        // Return the other participant given one user
        string other(const string& u) const;
    };
public:
    bool login(const string &username, const string &password);
    bool signup(const string &username, const string &password);
    bool userExists(const string& username) const;
    User* getUser(const string& username);

    // For testing
    void printAllUsers();

    //adds and removes friends using a simple graph
    void addFriend(string a, string b);
    void removeFriend(string a, string b);
    void addCloseFriend(string a, string b);
    void removeCloseFriend(string a, string b);

    // Cross-user actions: enforce authorization (self or friend) and emit notifications
    // Like another user's post; notifies the owner
    bool likePost(const string& liker, const string& owner, int postIndex);
    // Comment on another user's post; replyToUser links to that user's most
    // recent comment as the parent (empty string = top-level)
    bool addCommentToPost(const string& commenter, const string& owner,
                          int postIndex, const string& text,
                          const string& replyToUser);
    // Send a private message; notifies the recipient
    bool sendMessage(const string& sender, const string& recipient, const string& text);
    // Print the conversation between two users (newest first)
    void viewConversation(const string& a, const string& b);
    // List all conversations a user is part of (shows the other party)
    void listConversationsFor(const string& user);

private:
    // Look up an existing conversation between two users; nullptr if none
    Conversation* findConversation(const string& a, const string& b);
    // Same as findConversation but creates and returns a new one if missing
    Conversation* findOrCreateConversation(const string& a, const string& b);

    // string is the username, User contains all information about the User
    unordered_map<string, User> users;
    list<Conversation> conversationsList;
};


#endif //ADS_PROJECT_USERS_H
