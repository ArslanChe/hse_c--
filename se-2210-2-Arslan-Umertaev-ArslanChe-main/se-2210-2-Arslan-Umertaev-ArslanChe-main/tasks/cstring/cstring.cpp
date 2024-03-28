#include "cstring.h"

size_t Strlen(const char* str) {
    const char* ptr = str;
    while (*ptr) {
        ++ptr;
    }
    return ptr - str;
}

int Strcmp(const char* first, const char* second) {
    while (*first && (*first == *second)) {
        first++;
        second++;
    }
    return *first - *second;
}

int Strncmp(const char* first, const char* second, size_t count) {
    while (*first && (*first == *second) && count) {
        first++;
        second++;
        count--;
    }
    return count == 0 ? 0 : *first - *second;
}

const char* Strchr(const char* str, char symbol) {
    while (*str) {
        if (*str == symbol) {
            return str;
        }
        ++str;
    }
    return symbol == '\0' ? str : nullptr;
}

char* Strcat(char* dest, const char* src) {
    char* ans = dest;
    while (*dest) {
        dest++;
    }
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
    return ans;
}

char* Strcpy(char* dest, const char* src) {
    char* ans = dest;
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
    return ans;
}

char* Strncpy(char* dest, const char* src, size_t count) {
    char* ans = dest;
    while (count && *src) {
        *dest++ = *src++;
        count--;
    }
    while (count) {
        *dest++ = '\0';
        count--;
    }
    return ans;
}

char* Strncat(char* dest, const char* src, size_t count) {
    char* ans = dest;
    while (*dest) {
        dest++;
    }
    while (*src && count) {
        *dest++ = *src++;
        count--;
    }
    *dest = '\0';
    return ans;
}

const char* Strrchr(const char* str, char symbol) {
    const char* ans = str + Strlen(str);
    while (ans >= str) {
        if (*ans == symbol) {
            return ans;
        }
        ans--;
    }
    return nullptr;
}

size_t Strspn(const char* dest, const char* src) {
    size_t count = 0;
    while (*dest && Strchr(src, *dest)) {
        count++;
        dest++;
    }
    return count;
}

size_t Strcspn(const char* dest, const char* src) {
    size_t count = 0;
    while (*dest && !Strchr(src, *dest)) {
        count++;
        dest++;
    }
    return count;
}

const char* Strpbrk(const char* dest, const char* breakset) {
    while (*dest) {
        if (Strchr(breakset, *dest)) {
            return dest;
        }
        ++dest;
    }
    return nullptr;
}

const char* Strstr(const char* str, const char* pattern) {
    if (!Strlen(pattern)) {
        return str;
    }
    while (*str) {
        if (!Strncmp(str, pattern, Strlen(pattern))) {
            return str;
        }
        ++str;
    }
    return nullptr;
}
