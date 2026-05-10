#ifndef ADS_PROJECT_POST_H
#define ADS_PROJECT_POST_H

#include <string>
#include <list>
#include <set>
using namespace std;

// A single user post: text, likes, and comments
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
        // null for top-level comments; otherwise points to the parent comment
        Comment* parent = nullptr;
    };

public:
    Post(string username, string description);

    // Add a comment to the post. If replyToUser is non-empty, link this
    // comment as a reply to the most recent comment by that user.
    void addComment(const string& commenter, const string& text, const string& replyToUser = "");
    // Print all comments newest-first, marking replies by parent username
    void displayComments() const;
    // Print all users who liked the post
    void displayLikers() const;
    string getDescription() const;
    int getPostId() const;
    string getUsername() const;
    int getLikesCount() const;
    int getCommentCount() const;

    // Record a like; the set ensures each user can only like once
    void like(const string& liker);

    // Two posts are equal iff they share the same unique post ID
    bool operator==(const Post& other) const;

private:
    //unique id in order to distinguish posts
    static int ID_COUNTER;
    int postId;
    //post contents
    string username;
    string description;
    //store who liked this post; set keeps likes unique per user
    set<string> likedBy;
    //comments stored in insertion order; replies link to a parent comment
    list<Comment> commentsList;
};


#endif //ADS_PROJECT_POST_H
