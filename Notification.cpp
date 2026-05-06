//
// Created by User on 5/6/2026.
//

#include "Notification.h"

Notification::Notification(string username, string description) {
    this->username = username;
    this->description = description;
}

void Notification::markAsRead() {
    isRead = true;
}
