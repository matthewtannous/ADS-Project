#include "MessageManager.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include "Users.h"

bool MessageManager::sendMessage(const string& senderUsername,
                                 const string& receiverUsername,
                                 const string& content,
                                 const Users& users) {
    if (!users.userExists(senderUsername)) {
        cout << "Cannot send message: sender username does not exist.\n";
        return false;
    }

    if (!users.userExists(receiverUsername)) {
        cout << "Cannot send message: receiver username does not exist.\n";
        return false;
    }

    if (senderUsername == receiverUsername) {
        cout << "Cannot send message: sender and receiver cannot be the same user.\n";
        return false;
    }

    if (content.empty()) {
        cout << "Cannot send message: message content cannot be empty.\n";
        return false;
    }

    Message message(senderUsername, receiverUsername, content);
    inboxes[receiverUsername].push_back(message);
    sentMessages[senderUsername].push_back(message);

    cout << "Message sent successfully from " << senderUsername << " to " << receiverUsername << ".\n";
    return true;
}

void MessageManager::viewInbox(const string& username) const {
    unordered_map<string, list<Message>>::const_iterator iter = inboxes.find(username);

    if (iter == inboxes.end() || iter->second.empty()) {
        cout << "Inbox is empty for " << username << ".\n";
        return;
    }

    cout << "Inbox for " << username << ":\n";
    for (const Message& message : iter->second) {
        message.display();
    }
}

void MessageManager::viewSentMessages(const string& username) const {
    unordered_map<string, list<Message>>::const_iterator iter = sentMessages.find(username);

    if (iter == sentMessages.end() || iter->second.empty()) {
        cout << "No sent messages for " << username << ".\n";
        return;
    }

    cout << "Sent messages for " << username << ":\n";
    for (const Message& message : iter->second) {
        message.display();
    }
}

void MessageManager::viewConversation(const string& userA,
                                      const string& userB) const {
    vector<Message> conversation;

    unordered_map<string, list<Message>>::const_iterator sentFromA = sentMessages.find(userA);
    if (sentFromA != sentMessages.end()) {
        for (const Message& message : sentFromA->second) {
            if (message.getReceiverUsername() == userB) {
                conversation.push_back(message);
            }
        }
    }

    unordered_map<string, list<Message>>::const_iterator sentFromB = sentMessages.find(userB);
    if (sentFromB != sentMessages.end()) {
        for (const Message& message : sentFromB->second) {
            if (message.getReceiverUsername() == userA) {
                conversation.push_back(message);
            }
        }
    }

    if (conversation.empty()) {
        cout << "No conversation found between " << userA << " and " << userB << ".\n";
        return;
    }

    sort(conversation.begin(), conversation.end(), [](const Message& left, const Message& right) {
        return left.getMessageId() < right.getMessageId();
    });

    cout << "Conversation between " << userA << " and " << userB << ":\n";
    for (const Message& message : conversation) {
        message.display();
    }
}

bool MessageManager::markMessageAsRead(const string& username,
                                       int messageId) {
    unordered_map<string, list<Message>>::iterator iter = inboxes.find(username);

    if (iter == inboxes.end()) {
        cout << "Message not found in inbox for " << username << ".\n";
        return false;
    }

    for (Message& message : iter->second) {
        if (message.getMessageId() == messageId) {
            message.markAsRead();
            cout << "Message marked as read.\n";
            return true;
        }
    }

    cout << "Message not found in inbox for " << username << ".\n";
    return false;
}

bool MessageManager::hasUnreadMessages(const string& username) const {
    unordered_map<string, list<Message>>::const_iterator iter = inboxes.find(username);

    if (iter == inboxes.end()) {
        return false;
    }

    for (const Message& message : iter->second) {
        if (!message.getIsRead()) {
            return true;
        }
    }

    return false;
}

int MessageManager::countUnreadMessages(const string& username) const {
    unordered_map<string, list<Message>>::const_iterator iter = inboxes.find(username);

    if (iter == inboxes.end()) {
        return 0;
    }

    int count = 0;
    for (const Message& message : iter->second) {
        if (!message.getIsRead()) {
            count++;
        }
    }

    return count;
}
