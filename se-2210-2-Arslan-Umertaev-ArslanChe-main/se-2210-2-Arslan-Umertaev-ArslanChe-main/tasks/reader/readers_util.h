#pragma once

#include <memory>
#include <vector>

#include "reader.h"

class LimitReader : public Reader {
public:
    LimitReader(std::unique_ptr<Reader> reader, size_t limit);

    size_t Read(char* buf, size_t len) override;

private:
    std::unique_ptr<Reader> reader_;
    size_t limit_;
};

class TeeReader : public Reader {
public:
    explicit TeeReader(std::vector<std::unique_ptr<Reader>> readers);

    size_t Read(char* buf, size_t len) override;

private:
    std::vector<std::unique_ptr<Reader>> readers_;
};

class HexDecodingReader : public Reader {
public:
    explicit HexDecodingReader(std::unique_ptr<Reader> reader);

    size_t Read(char* buf, size_t len) override;
    static char DecodeHexChar(char tmp) {
        const int ten = 10;
        if (tmp >= '0' && tmp <= '9') {
            return tmp - '0';  // NOLINT
        } else if (tmp >= 'a' && tmp <= 'f') {
            return tmp - 'a' + ten;  // NOLINT
        } else if (tmp >= 'A' && tmp <= 'F') {
            return tmp - 'A' + ten;  // NOLINT
        }
        return 0;
    }

private:
    std::unique_ptr<Reader> reader_;
    bool has_pending_byte_;
    char pending_byte_;
};
