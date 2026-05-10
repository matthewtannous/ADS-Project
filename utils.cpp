/**
 * utils.cpp
 * Implements console-input helpers. getUserInfo prompts for a username
 * and password and returns them as a 2-element array.
 */

#include "utils.h"

#include <array>
using namespace std;

std::array<string, 2> getUserInfo() {
    std::array<string, 2> s;

    cout << "Enter username: ";
    cin >> s[0];

    cout << "Enter password: ";
    cin >> s[1];

    return s;
}
