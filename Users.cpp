/**
 * Users.cpp
 * Implements account management (login/signup), the friendship graph,
 * cross-user actions (likes, comments, messages) with authorization and
 * notifications, and the Conversation inner class used for direct messages.
 */

#include "Users.h"

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

User* Users::getUser(const string& username) {
   auto iter = users.find(username);
   if (iter == users.end()) return nullptr;
   return &iter->second;
}

void Users::printAllUsers() {
   // 'auto' automatically detects type
   for (auto element: users) {
      cout << element.second.getUsername() << ", " << element.second.getPassword() << "\n";
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
   users.at(a).addCloseFriend(b);
   users.at(b).addCloseFriend(a);
}

void Users::removeCloseFriend(string a, string b) {
   users.at(a).removeCloseFriend(b);
   users.at(b).removeCloseFriend(a);
}

bool Users::likePost(const string& liker, const string& owner, int postIndex) {
   if (!userExists(liker) || !userExists(owner)) {
      cout << "User does not exist.\n";
      return false;
   }
   if (liker != owner && !users.at(owner).isFriend(liker)) {
      cout << "You can only like posts of your friends.\n";
      return false;
   }
   Post* p = users.at(owner).getPostAt(postIndex);
   if (p == nullptr) {
      cout << "Invalid post index.\n";
      return false;
   }
   p->like(liker);
   if (liker != owner) {
      users.at(owner).receiveNotification(
         Notification(liker, liker + " liked your post"));
   }
   return true;
}

bool Users::addCommentToPost(const string& commenter, const string& owner,
                             int postIndex, const string& text,
                             const string& replyToUser) {
   if (!userExists(commenter) || !userExists(owner)) {
      cout << "User does not exist.\n";
      return false;
   }
   if (commenter != owner && !users.at(owner).isFriend(commenter)) {
      cout << "You can only comment on posts of your friends.\n";
      return false;
   }
   Post* p = users.at(owner).getPostAt(postIndex);
   if (p == nullptr) {
      cout << "Invalid post index.\n";
      return false;
   }
   p->addComment(commenter, text, replyToUser);
   if (commenter != owner) {
      users.at(owner).receiveNotification(
         Notification(commenter, commenter + " commented on your post"));
   }
   return true;
}

bool Users::sendMessage(const string& sender, const string& recipient, const string& text) {
   if (!userExists(sender) || !userExists(recipient)) {
      cout << "User does not exist.\n";
      return false;
   }
   if (sender == recipient) {
      cout << "Can't message yourself.\n";
      return false;
   }
   if (!users.at(sender).isFriend(recipient)) {
      cout << "You can only message your friends.\n";
      return false;
   }
   Conversation* c = findOrCreateConversation(sender, recipient);
   c->addMessage(sender, text);
   users.at(recipient).receiveNotification(
      Notification(sender, sender + " sent you a message"));
   return true;
}

void Users::viewConversation(const string& a, const string& b) {
   Conversation* c = findConversation(a, b);
   if (c == nullptr) {
      cout << "(no messages yet)\n";
      return;
   }
   c->showMessages();
}

void Users::listConversationsFor(const string& user) {
   bool any = false;
   int i = 0;
   for (Conversation& c : conversationsList) {
      if (c.involves(user)) {
         cout << "[" << i++ << "] with " << c.other(user) << "\n";
         any = true;
      }
   }
   if (!any) cout << "(no conversations yet)\n";
}

Users::Conversation* Users::findConversation(const string& a, const string& b) {
   for (Conversation& c : conversationsList) {
      if (c.involves(a, b)) return &c;
   }
   return nullptr;
}

Users::Conversation* Users::findOrCreateConversation(const string& a, const string& b) {
   Conversation* c = findConversation(a, b);
   if (c != nullptr) return c;
   conversationsList.emplace_back(a, b);
   return &conversationsList.back();
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
   if (messages.empty()) {
      cout << "(no messages)\n";
      return;
   }
   for (pair<string, bool> message : messages) {
      cout << (message.second ? user1 : user2) << ": " << message.first << "\n";
   }
}

bool Users::Conversation::involves(const string& a, const string& b) const {
   return (user1 == a && user2 == b) || (user1 == b && user2 == a);
}

bool Users::Conversation::involves(const string& u) const {
   return user1 == u || user2 == u;
}

string Users::Conversation::other(const string& u) const {
   return user1 == u ? user2 : user1;
}
