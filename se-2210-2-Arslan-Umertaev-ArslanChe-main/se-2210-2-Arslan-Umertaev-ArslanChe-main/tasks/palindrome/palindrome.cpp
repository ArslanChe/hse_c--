#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    int left_index = 0;
    int right_index = static_cast<int>(str.length()) - 1;
    while (left_index < right_index) {
        if (str[left_index] == ' ') {
            ++left_index;
            continue;
        }
        if (str[right_index] == ' ') {
            --right_index;
            continue;
        }
        if (str[left_index] != str[right_index]) {
            return false;
        }
        --right_index;
        ++left_index;
    }
    return true;
}
