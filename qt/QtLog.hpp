#pragma once

#include <string>

class QtLog {
public:
    template <typename... Args> static int v(const char* tag, Args... args);
    template <typename... Args> static int d(const char* tag, Args... args);
    template <typename... Args> static int i(const char* tag, Args... args);
    template <typename... Args> static int w(const char* tag, Args... args);
    template <typename... Args> static int e(const char* tag, Args... args);
    template <typename... Args> static int wtf(const char* tag, Args... args);
    template <typename... Args> static void assert_condition(bool cond, const char* condAsString, const char* tag, Args... args);
};

template <typename... Args>
int QtLog::v(const char* tag, Args... args) {

    return 0;
}

template <typename... Args>
int QtLog::d(const char* tag, Args... args) {

    return 0;
}

template <typename... Args>
int QtLog::i(const char* tag, Args... args) {

    return 0;
}

template <typename... Args>
int QtLog::w(const char* tag, Args... args) {

    return 0;
}

template <typename... Args>
int QtLog::e(const char* tag, Args... args) {

    return 0;
}

template <typename... Args>
int QtLog::wtf(const char* tag, Args... args) {

    return 0;
}

template<typename... Args>
void QtLog::assert_condition(bool cond, const char* condAsString, const char* tag, Args... args) {

    if (! cond) {
        //assert(false);
    }
}
