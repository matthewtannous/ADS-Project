#ifndef ADS_PROJECT_MESSAGE_MANAGER_H
#define ADS_PROJECT_MESSAGE_MANAGER_H

#include <list>
#include <string>
#include <unordered_map>

#include "Message.h"
using namespace std;

class Users;

class MessageManager {
public:
    bool sendMessage(const string& senderUsername,
                     const string& receiverUsername,
                     const string& content,
                     const Users& users);

    void viewInbox(const string& username) const;
    void viewSentMessages(const string& username) const;
    void viewConversation(const string& userA,
                          const string& userB) const;
    bool markMessageAsRead(const string& username,
                           int messageId);
    bool hasUnreadMessages(const string& username) const;
    int countUnreadMessages(const string& username) const;

private:
    unordered_map<string, list<Message>> inboxes;
    unordered_map<string, list<Message>> sentMessages;
};

#endif //ADS_PROJECT_MESSAGE_MANAGER_H
