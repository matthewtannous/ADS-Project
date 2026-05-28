/**
 * Notification.cpp
 * Implements the Notification class: a small value type carrying the
 * sender, the message text, and a read flag.
 */

#include "Notification.h"

Notification::Notification(string username, string description) {
  this->username = username;
  this->description = description;
  this->isRead = false;
}

void Notification::markAsRead() { isRead = true; }
