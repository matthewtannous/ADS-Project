#include "Message.h"

#include <ctime>

namespace {
    string getCurrentTimestamp() {
        time_t now = time(nullptr);
        tm* localTime = localtime(&now);
        char buffer[20];

        if (localTime != nullptr && strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime) > 0) {
            return string(buffer);
        }

        return "Unknown time";
    }
}

int Message::ID_COUNTER = 0;

Message::Message(const string& senderUsername,
                 const string& receiverUsername,
                 const string& content)
        : messageId(++ID_COUNTER),
          senderUsername(senderUsername),
          receiverUsername(receiverUsername),
          content(content),
          timestamp(getCurrentTimestamp()),
          isRead(false) {
}

int Message::getMessageId() const {
    return messageId;
}

string Message::getSenderUsername() const {
    return senderUsername;
}

string Message::getReceiverUsername() const {
    return receiverUsername;
}

string Message::getContent() const {
    return content;
}

string Message::getTimestamp() const {
    return timestamp;
}

bool Message::getIsRead() const {
    return isRead;
}

void Message::markAsRead() {
    isRead = true;
}

void Message::display() const {
    cout << "Message ID: " << messageId << "\n";
    cout << "From: " << senderUsername << "\n";
    cout << "To: " << receiverUsername << "\n";
    cout << "Time: " << timestamp << "\n";
    cout << "Status: " << (isRead ? "Read" : "Unread") << "\n";
    cout << "Content: " << content << "\n";
    cout << "------------------------\n";
}
