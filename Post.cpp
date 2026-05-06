#include "Post.h"
// #include "Users.h"

// Static variable must be initialized before incrementing it
int Post::ID_COUNTER = 0; 

Post::Post(string username, string description) : username(username), description(description) {
    postId = ++ID_COUNTER;
}


bool Post::operator==(const Post &other) const {
    return postId == other.postId;
}

void Post::addComment(string comment) {
    commentsList.push_back(comment);
}

string *Post::getCommentsList() {
    int size = commentsList.size();
    string *arr = new string[size];

    int i = 0;
    for (const string &str: commentsList) {
        arr[i++] = str;
    }
    return arr;
}
