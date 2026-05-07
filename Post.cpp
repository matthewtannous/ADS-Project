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

void Post::addComment(Comment c) {
    commentsList.push_back(c);
}

Post::Comment *Post::getCommentsList() const {
    int size = commentsList.size();
    Comment *arr = new Comment[size];

    int i = 0;
    for (const Comment &c: commentsList) {
        arr[i++] = c;
    }
    return arr;
}

string Post::getDescription() const {
    return description;
}
