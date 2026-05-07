#ifndef ADS_PROJECT_NOTIFICATION_H
#define ADS_PROJECT_NOTIFICATION_H
#include <queue>
#include <string>
using namespace std;

class Notification {
public:
    string username;
    string description;
    bool isRead;
    Notification(string username, string description);
    void markAsRead();
};


#endif //ADS_PROJECT_NOTIFICATION_H