/**
 * Notification.h
 * A single alert addressed to a user (e.g., a like, comment, message, or
 * friend request). Users keep a stack of these and display them newest-first.
 */

#ifndef ADS_PROJECT_NOTIFICATION_H
#define ADS_PROJECT_NOTIFICATION_H
#include <queue>
#include <string>
using namespace std;

// One alert sent to a user (e.g., new like, comment, message, friend request)
class Notification {
public:
    // The user who triggered the notification
    string username;
    // Readable description shown to the recipient
    string description;
    // Tracked but not yet exposed in the UI; reserved for a future read-state feature
    bool isRead;
    Notification(string username, string description);
    void markAsRead();
};


#endif //ADS_PROJECT_NOTIFICATION_H
