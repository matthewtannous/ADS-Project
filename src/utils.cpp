//
// Created by matthew on 5/5/26.
//

#include "../Utils/utils.h"

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
