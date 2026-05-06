#ifndef ADS_PROJECT_POST_H
#define ADS_PROJECT_POST_H

#include <string>
#include <list>
using namespace std;

class Post {
public:
    Post(string username, string description);

    //make class abstract -> text, img, vid
    void virtual display();

    void addComment(string comment);

    string *getCommentsList();

    bool operator==(Post &other) const;

private:
    //unique id in order to distinguish posts
    static int ID_COUNTER;
    int postId;
    //post contents
    string username;
    string description;
    int likesCount = 0;
    list<string> commentsList;
};

#endif //ADS_PROJECT_POST_H
