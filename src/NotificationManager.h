#ifndef ADS_PROJECT_NOTIFICATION_MANAGER_H
#define ADS_PROJECT_NOTIFICATION_MANAGER_H

#include <queue>
#include <string>
#include <unordered_map>

#include "Notification.h"
using namespace std;

class NotificationManager {
public:
    void addNotification(const string& receiverUsername,
                         const string& message);

    void viewNotifications(const string& username) const;
    void popNotification(const string& username);
    bool hasNotifications(const string& username) const;
    int countNotifications(const string& username) const;

private:
    unordered_map<string, queue<Notification>> notifications;
};

#endif //ADS_PROJECT_NOTIFICATION_MANAGER_H
