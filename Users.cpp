#include "Users.h"

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