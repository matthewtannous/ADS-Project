#include "Post.h"
#include "Users.h"

bool operator==(Post& other) const{
    return postId == other.postId;
}

void Post::addComment(string comment) {
    commentsList.push_back(comment);
}

string* Post::getCommnetsList() {
    int size = commentsList.size();
    string* arr = new string[size];

    int i = 0;
    for (const string &str : commentsList) {
        arr[i++] = str;
    }
    return arr;
}