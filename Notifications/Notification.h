#ifndef ADS_PROJECT_NOTIFICATION_H
#define ADS_PROJECT_NOTIFICATION_H

#include <iostream>
#include <string>
using namespace std;

class Notification {
public:
    Notification(const string& receiverUsername,
                 const string& message);

    int getNotificationId() const;
    string getReceiverUsername() const;
    string getMessage() const;
    string getTimestamp() const;
    bool getIsRead() const;

    void markAsRead();
    void display() const;

private:
    static int ID_COUNTER;
    int notificationId;
    string receiverUsername;
    string message;
    string timestamp;
    bool isRead;
};

#endif //ADS_PROJECT_NOTIFICATION_H
