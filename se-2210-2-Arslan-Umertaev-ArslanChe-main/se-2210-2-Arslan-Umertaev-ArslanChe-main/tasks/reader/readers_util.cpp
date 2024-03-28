#include "readers_util.h"

LimitReader::LimitReader(std::unique_ptr<Reader> reader, size_t limit) : reader_(std::move(reader)), limit_(limit) {
}

HexDecodingReader::HexDecodingReader(std::unique_ptr<Reader> reader)
    : reader_(std::move(reader)), has_pending_byte_(false), pending_byte_(0) {
}

TeeReader::TeeReader(std::vector<std::unique_ptr<Reader>> readers) : readers_(std::move(readers)) {
}

size_t LimitReader::Read(char* buf, size_t len) {
    if (limit_ == 0) {
        return 0;
    }
    size_t bytes_read = reader_->Read(buf, std::min(len, limit_));
    limit_ -= bytes_read;

    return bytes_read;
}

size_t TeeReader::Read(char* buf, size_t len) {
    size_t total_bytes_read = 0;

    for (auto& reader : readers_) {
        size_t bytes_read = reader->Read(buf + total_bytes_read, len - total_bytes_read);
        total_bytes_read += bytes_read;
    }
    return total_bytes_read;
}

size_t HexDecodingReader::Read(char* buf, size_t len) {
    size_t total_bytes_read = 0;
    while (total_bytes_read < len) {
        if (!has_pending_byte_) {
            char dop1 = 0;
            char dop2 = 0;
            size_t bytes_read = reader_->Read(&dop1, 1);
            if (bytes_read == 0) {
                break;
            }

            bytes_read = reader_->Read(&dop2, 1);
            if (bytes_read == 0) {
                break;
            }

            pending_byte_ = DecodeHexChar(dop1) << 4 | DecodeHexChar(dop2);  // NOLINT
            has_pending_byte_ = true;
        }

        buf[total_bytes_read++] = pending_byte_;
        has_pending_byte_ = false;
    }

    return total_bytes_read;
}
