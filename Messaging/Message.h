#ifndef ADS_PROJECT_MESSAGE_H
#define ADS_PROJECT_MESSAGE_H

#include <iostream>
#include <string>
using namespace std;

class Message {
public:
    Message(const string& senderUsername,
            const string& receiverUsername,
            const string& content);

    int getMessageId() const;
    string getSenderUsername() const;
    string getReceiverUsername() const;
    string getContent() const;
    string getTimestamp() const;
    bool getIsRead() const;

    void markAsRead();
    void display() const;

private:
    static int ID_COUNTER;
    int messageId;
    string senderUsername;
    string receiverUsername;
    string content;
    string timestamp;
    bool isRead;
};

#endif //ADS_PROJECT_MESSAGE_H
