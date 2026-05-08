#include <array>
#include <iostream>
#include "Users.h"
#include "utils.h"

using namespace std;

void run(array<string, 2> &userInfo, Users &users);

int main() {
    Users users; // List of all users
    // cout << users.users.size();
    int choice;
    array<string, 2> userInfo;

    do {
        cout << "Hello! What would you like to do?\n"
                "1. Register\n"
                "2. Login\n"
                "3. Exit\n"
                "4. Print all users (testing)\n"; // Add other options later

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

void run(array<string, 2>& userInfo, Users &users) {
    const string currentUser = userInfo[0];
    User* me = users.getUser(currentUser);
    int loggedInChoice;
    do {
        cout << "\nWhat would you like to do?\n"
                "1. Create a post\n"
                "2. Remove a post\n"
                "3. Add a friend\n"
                "4. Remove a friend\n"
                "5. Add a close friend\n"
                "6. Remove a close friend\n"
                "7. Change password\n"
                "8. View friends list\n"
                "9. View my posts\n"
                "10. Logout\n";
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
            case 4: {
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
            case 5: {
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
            case 6: {
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
            case 7:
                me->setPassword();
                break;
            case 8:
                me->displayFriends();
                break;
            case 9:
                me->displayPosts();
                break;
            case 10:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid option.\n";
        }
    } while (loggedInChoice != 10);

}