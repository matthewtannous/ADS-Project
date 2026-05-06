#include "Notification.h"

Notification::Notification(string username, string description) {
    this->username = username;
    this->description = description;
}

void Notification::markAsRead() {
    isRead = true;
}
