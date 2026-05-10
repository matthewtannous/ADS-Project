/**
 * Post.cpp
 * Implements the Post class: unique-ID assignment, likes, 
 * and comments with optional reply-to parent linking.
 */

#include "Post.h"

#include <iostream>

// Static variable must be initialized before incrementing it
int Post::ID_COUNTER = 0;

Post::Post(string username, string description) : username(username), description(description) {
    postId = ++ID_COUNTER;
}


bool Post::operator==(const Post &other) const {
    return postId == other.postId;
}

void Post::addComment(const string& commenter, const string& text, const string& replyToUser) {
    Comment c;
    c.commenterUsername = commenter;
    c.description = text;
    c.parent = nullptr;

    if (!replyToUser.empty()) {
        // Link to the most recent comment by replyToUser (newest = back of list)
        for (auto it = commentsList.rbegin(); it != commentsList.rend(); ++it) {
            if (it->commenterUsername == replyToUser) {
                c.parent = &(*it);
                break;
            }
        }
    }
    commentsList.push_back(c);
}

void Post::displayComments() const {
    if (commentsList.empty()) {
        cout << "(no comments)\n";
        return;
    }
    // newest first
    for (auto it = commentsList.rbegin(); it != commentsList.rend(); ++it) {
        cout << "  - " << it->commenterUsername << ": " << it->description;
        if (it->parent != nullptr) {
            cout << "  (reply to " << it->parent->commenterUsername << ")";
        }
        cout << "\n";
    }
}

string Post::getDescription() const {
    return description;
}

int Post::getPostId() const {
    return postId;
}

string Post::getUsername() const {
    return username;
}

int Post::getLikesCount() const {
    return static_cast<int>(likedBy.size());
}

int Post::getCommentCount() const {
    return static_cast<int>(commentsList.size());
}

void Post::like(const string& liker) {
    likedBy.insert(liker);
}

void Post::displayLikers() const {
    if (likedBy.empty()) {
        cout << "(no likes)\n";
        return;
    }
    for (const string& u : likedBy) {
        cout << "  - " << u << "\n";
    }
}
