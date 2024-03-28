#include "password.h"

bool ValidatePassword(const std::string& password) {
    int flag[4] = {0, 0, 0, 0};
    const int min_length = 8;
    const int max_length = 14;
    if (password.size() < min_length || password.size() > max_length) {
        return false;
    }
    const int min_char = 33;
    const int max_char = 126;

    for (auto letter : password) {
        if (letter < min_char || letter > max_char) {
            return false;
        }
        if (letter >= 'A' && letter <= 'Z') {
            flag[0] = 1;
        } else if (letter >= 'a' && letter <= 'z') {
            flag[1] = 1;
        } else if (letter >= '0' && letter <= '9') {
            flag[2] = 1;
        } else {
            flag[3] = 1;
        }
    }
    if (flag[0] + flag[1] + flag[2] + flag[3] < 3) {
        return false;
    }
    return true;
}
