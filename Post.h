#ifndef ADS_PROJECT_POST_H
#define ADS_PROJECT_POST_H

#include <string>
#include <list>
using namespace std;

class Post {

/*
 Use private class for comments instead of forest tree
 each comment points to the one it is replying to
 the comments replying to the post directly point to null
 this builds a tree indirectly and allows for more flexibility and easier scalability and traversal than a messy forest tree
 */
private:
    struct Comment {
        public:
        string commenterUsername;
        string description;
        Comment* parent = nullptr;
    };

public:
    Post(string username, string description);
    // make class abstract -> text, img, vid
    // void virtual display(); // COMMENTED OUT for compiling

    void addComment(Comment c);
    Comment* getCommentsList() const;

    bool operator==(const Post& other) const;

private:
    //unique id in order to distinguish posts
    static int ID_COUNTER;
    int postId;
    //post contents
    string username;
    string description;
    int likesCount = 0;
    //store all comments in a list. reconstruct later.
    list<Comment> commentsList;
};


#endif //ADS_PROJECT_POST_H
