#include "Notification.h"

Notification::Notification(string username, string description) {
    this->username = username;
    this->description = description;
    this->isRead = false;
}

void Notification::markAsRead() {
    isRead = true;
}
