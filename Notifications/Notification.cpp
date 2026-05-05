#include "Notification.h"

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

int Notification::ID_COUNTER = 0;

Notification::Notification(const string& receiverUsername,
                           const string& message)
        : notificationId(++ID_COUNTER),
          receiverUsername(receiverUsername),
          message(message),
          timestamp(getCurrentTimestamp()),
          isRead(false) {
}

int Notification::getNotificationId() const {
    return notificationId;
}

string Notification::getReceiverUsername() const {
    return receiverUsername;
}

string Notification::getMessage() const {
    return message;
}

string Notification::getTimestamp() const {
    return timestamp;
}

bool Notification::getIsRead() const {
    return isRead;
}

void Notification::markAsRead() {
    isRead = true;
}

void Notification::display() const {
    cout << "Notification ID: " << notificationId << "\n";
    cout << "For: " << receiverUsername << "\n";
    cout << "Time: " << timestamp << "\n";
    cout << "Status: " << (isRead ? "Read" : "Unread") << "\n";
    cout << "Message: " << message << "\n";
    cout << "------------------------\n";
}
