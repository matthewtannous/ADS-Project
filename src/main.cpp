/**
 * main.cpp
 * Program entry point and console UI loop. Shows the pre-login menu
 * (register/login/exit) and, once authenticated, the dashboard menu
 * for posts, friends, messages, and notifications.
 */

#include "Users.h"
#include "utils.h"
#include <array>
#include <iostream>

using namespace std;

// Runs the logged-in user dashboard until the user logs out
void run(array<string, 2> &userInfo, Users &users);

int main() {
  Users users; // List of all users
  int choice;
  array<string, 2> userInfo;

  do {
    cout << "Hello! What would you like to do?\n"
            "1. Register\n"
            "2. Login\n"
            "3. Exit\n"
            "4. Print all users (testing)\n";

    cin >> choice;

    switch (choice) {
    case 1:
      userInfo = getUserInfo();
      if (users.signup(userInfo[0], userInfo[1])) {
        run(userInfo, users);
      };
      break;
    case 2: {
      userInfo = getUserInfo();
      if (users.login(userInfo[0], userInfo[1])) {
        run(userInfo, users);
      }
      break;
    }
    case 4:
      users.printAllUsers();
      break;
    default:
      cout << "Exiting...\n";
    }
  } while (choice != 3);
}

void run(array<string, 2> &userInfo, Users &users) {
  const string currentUser = userInfo[0];
  User *me = users.getUser(currentUser);
  int loggedInChoice;
  do {
    cout << "\nWhat would you like to do?\n"
            "1.  Create a post\n"
            "2.  Remove a post\n"
            "3.  View my posts\n"
            "4.  View a friend's posts\n"
            "5.  Like a post\n"
            "6.  Comment on a post\n"
            "7.  Send a message\n"
            "8.  View a conversation\n"
            "9.  View notifications\n"
            "10. Add a friend\n"
            "11. Remove a friend\n"
            "12. Add a close friend\n"
            "13. Remove a close friend\n"
            "14. View friends list\n"
            "15. Change password\n"
            "16. Logout\n";
    cin >> loggedInChoice;

    switch (loggedInChoice) {
    case 1: {
      cout << "Enter post description: ";
      string description;
      cin >> ws;
      getline(cin, description);
      me->addPost(Post(currentUser, description));
      cout << "Post created.\n";
      break;
    }
    case 2: {
      me->displayPosts();
      cout << "Enter index of post to remove (-1 to cancel): ";
      int idx;
      cin >> idx;
      if (idx >= 0 && me->removePostAt(idx)) {
        cout << "Post removed.\n";
      } else {
        cout << "Cancelled or invalid index.\n";
      }
      break;
    }
    case 3: {
      me->displayPostsDetailed();
      cout << "Enter post index to see who liked and commented (-1 to skip): ";
      int idx;
      cin >> idx;
      if (idx >= 0) {
        Post *p = me->getPostAt(idx);
        if (p == nullptr) {
          cout << "Invalid post index.\n";
        } else {
          cout << "Liked by:\n";
          p->displayLikers();
          cout << "Comments (newest first):\n";
          p->displayComments();
        }
      }
      break;
    }
    case 4: {
      cout << "Enter friend's username: ";
      string other;
      cin >> other;
      if (!users.userExists(other)) {
        cout << "User does not exist.\n";
        break;
      }
      if (other != currentUser && !me->isFriend(other)) {
        cout << "Not your friend.\n";
        break;
      }
      cout << other << "'s posts:\n";
      users.getUser(other)->displayPostsDetailed();
      cout << "Enter post index to view comments (-1 to skip): ";
      int idx;
      cin >> idx;
      if (idx >= 0) {
        Post *p = users.getUser(other)->getPostAt(idx);
        if (p == nullptr) {
          cout << "Invalid post index.\n";
        } else {
          cout << "Comments (newest first):\n";
          p->displayComments();
        }
      }
      break;
    }
    case 5: {
      string owner;
      cout << "Whose post are you liking? (username): ";
      cin >> owner;
      if (!users.userExists(owner)) {
        cout << "User does not exist.\n";
        break;
      }
      users.getUser(owner)->displayPostsDetailed();
      cout << "Enter post index: ";
      int idx;
      cin >> idx;
      if (users.likePost(currentUser, owner, idx)) {
        cout << "Liked.\n";
      }
      break;
    }
    case 6: {
      string owner;
      cout << "Whose post are you commenting on? (username): ";
      cin >> owner;
      if (!users.userExists(owner)) {
        cout << "User does not exist.\n";
        break;
      }
      users.getUser(owner)->displayPostsDetailed();
      cout << "Enter post index: ";
      int idx;
      cin >> idx;
      Post *p = users.getUser(owner)->getPostAt(idx);
      if (p == nullptr) {
        cout << "Invalid post index.\n";
        break;
      }
      cout << "Existing comments (newest first):\n";
      p->displayComments();
      cout << "Reply to another comment? (y/n): ";
      string ans;
      cin >> ans;
      string replyToUser;
      if (ans == "y" || ans == "Y") {
        cout << "Reply to whose comment? (username): ";
        cin >> replyToUser;
      }
      cout << "Enter comment text: ";
      string text;
      cin >> ws;
      getline(cin, text);
      if (users.addCommentToPost(currentUser, owner, idx, text, replyToUser)) {
        cout << "Comment added.\n";
      }
      break;
    }
    case 7: {
      cout << "Send message to (username): ";
      string other;
      cin >> other;
      cout << "Enter message: ";
      string text;
      cin >> ws;
      getline(cin, text);
      if (users.sendMessage(currentUser, other, text)) {
        cout << "Message sent.\n";
      }
      break;
    }
    case 8: {
      cout << "Your conversations:\n";
      users.listConversationsFor(currentUser);
      cout << "Enter username to view conversation with (or - to cancel): ";
      string other;
      cin >> other;
      if (other == "-")
        break;
      if (!users.userExists(other)) {
        cout << "User does not exist.\n";
        break;
      }
      users.viewConversation(currentUser, other);
      break;
    }
    case 9:
      me->displayNotifications();
      break;
    case 10: {
      cout << "Enter username to add as friend: ";
      string other;
      cin >> other;
      if (other == currentUser) {
        cout << "Can't add yourself.\n";
      } else if (!users.userExists(other)) {
        cout << "User does not exist.\n";
      } else {
        users.addFriend(currentUser, other);
        cout << "Friend added.\n";
      }
      break;
    }
    case 11: {
      cout << "Enter username to remove from friends: ";
      string other;
      cin >> other;
      if (!users.userExists(other)) {
        cout << "User does not exist.\n";
      } else {
        users.removeFriend(currentUser, other);
        cout << "Friend removed.\n";
      }
      break;
    }
    case 12: {
      cout << "Enter username to add as close friend: ";
      string other;
      cin >> other;
      if (other == currentUser) {
        cout << "Can't add yourself.\n";
      } else if (!users.userExists(other)) {
        cout << "User does not exist.\n";
      } else {
        users.addCloseFriend(currentUser, other);
        cout << "Close friend added.\n";
      }
      break;
    }
    case 13: {
      cout << "Enter username to remove from close friends: ";
      string other;
      cin >> other;
      if (!users.userExists(other)) {
        cout << "User does not exist.\n";
      } else {
        users.removeCloseFriend(currentUser, other);
        cout << "Close friend removed.\n";
      }
      break;
    }
    case 14:
      me->displayFriends();
      break;
    case 15:
      me->setPassword();
      break;
    case 16:
      cout << "Logging out...\n";
      break;
    default:
      cout << "Invalid option.\n";
    }
  } while (loggedInChoice != 16);
}
