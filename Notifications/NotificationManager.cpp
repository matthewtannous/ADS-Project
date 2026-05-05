#include "NotificationManager.h"

#include <iostream>

void NotificationManager::addNotification(const string& receiverUsername,
                                          const string& message) {
    Notification notification(receiverUsername, message);
    notifications[receiverUsername].push(notification);
}

void NotificationManager::viewNotifications(const string& username) const {
    unordered_map<string, queue<Notification>>::const_iterator iter = notifications.find(username);

    if (iter == notifications.end() || iter->second.empty()) {
        cout << "No notifications for " << username << ".\n";
        return;
    }

    queue<Notification> notificationsCopy = iter->second;

    cout << "Notifications for " << username << ":\n";
    while (!notificationsCopy.empty()) {
        notificationsCopy.front().display();
        notificationsCopy.pop();
    }
}

void NotificationManager::popNotification(const string& username) {
    unordered_map<string, queue<Notification>>::iterator iter = notifications.find(username);

    if (iter == notifications.end() || iter->second.empty()) {
        cout << "No notifications to remove for " << username << ".\n";
        return;
    }

    iter->second.pop();
    cout << "Oldest notification removed for " << username << ".\n";
}

bool NotificationManager::hasNotifications(const string& username) const {
    unordered_map<string, queue<Notification>>::const_iterator iter = notifications.find(username);
    return iter != notifications.end() && !iter->second.empty();
}

int NotificationManager::countNotifications(const string& username) const {
    unordered_map<string, queue<Notification>>::const_iterator iter = notifications.find(username);

    if (iter == notifications.end()) {
        return 0;
    }

    return static_cast<int>(iter->second.size());
}
