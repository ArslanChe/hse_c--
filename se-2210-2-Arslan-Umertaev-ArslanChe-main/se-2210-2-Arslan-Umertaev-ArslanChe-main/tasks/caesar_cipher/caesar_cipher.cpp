#include "caesar_cipher.h"

std::string Decipher(const std::string& cipher, size_t shift) {
    std::string origin_text;

    for (size_t i = 0; i < cipher.size(); ++i) {
        origin_text += cipher[i] - shift >= 'A'
                           ? static_cast<char>(cipher[i] - static_cast<int>(shift))
                           : static_cast<char>(cipher[i] + 'Z' - 'A' - static_cast<int>(shift) + 1);
    }
    return origin_text;
}
