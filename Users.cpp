#include "Users.h"

#include "Notification.h"
#include <utility>

bool Users::login(const string &username, const string &password) {
   // Search for username
   unordered_map<string, User>::iterator iter = users.find(username);
   if (iter == users.end()) { // User not found
      cout << "Username does not exist\n";
      return false;
   } else {
      if (iter->second.getPassword() == password) {
         cout << "Correct password. Logging in\n";
         return true;
      } else {
         cout << "Incorrect password.\n";
         return false;
      }
   }
}

bool Users::signup(const string &username, const string &password) {
   // Search for username
   unordered_map<string, User>::iterator iter = users.find(username);

   if (iter == users.end()) {
      users.insert({username, User(username, password)});
      return true;
   } else {
      cout << "Username already exists\n";
      return false;
   }
}

bool Users::userExists(const string& username) const {
   return users.find(username) != users.end();
}

void Users::printAllUsers() {
   // 'auto' automatically detects type
   for (auto element: users) {
      cout << element.first << ", " << element.second.getUsername() << ", " << element.second.getPassword() << "\n";
   }
}

//adds and removes friends using a simple graph
//uses friend function to access the private functions in user
void Users::addFriend(string a, string b) {
   users.at(a).addFriend(b);
   users.at(b).addFriend(a);
}

void Users::removeFriend(string a, string b) {
   users.at(a).removeFriend(b);
   users.at(b).removeFriend(a);
}

void Users::addCloseFriend(string a, string b) {
   users.at(a).addFriend(b);
   users.at(b).addFriend(a);
}

void Users::removeCloseFriend(string a, string b) {
   users.at(a).removeCloseFriend(b);
   users.at(b).removeCloseFriend(a);
}

// Code for Conversation
Users::Conversation::Conversation(string user1, string user2)
   : user1(user1), user2(user2) {}


// Insert message
void Users::Conversation::addMessage(string sender, string message) {
   // Add message at the beginning so users see newest messages first and for faster insertion
   messages.push_front({message, sender == user1});
}

// Displays all messages
void Users::Conversation::showMessages() {
   for (pair<string, bool> message : messages) {
      cout << (message.second ? user1 : user2) << ": " << message.first << "\n";
   }
}