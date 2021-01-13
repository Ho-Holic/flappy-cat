#pragma once

// ndk
#include <android/log.h>

// std
#include <string>

class AndroidLog {
public:
    template <typename... Args>
    static int v(const char* tag, Args... args);
    template <typename... Args>
    static int d(const char* tag, Args... args);
    template <typename... Args>
    static int i(const char* tag, Args... args);
    template <typename... Args>
    static int w(const char* tag, Args... args);
    template <typename... Args>
    static int e(const char* tag, Args... args);
    template <typename... Args>
    static int wtf(const char* tag, Args... args);
    template <typename... Args>
    static void assert_condition(bool cond, const char* condAsString,
        const char* tag, Args... args);
};

// implementation

namespace {

// make this functions 'free' to avoid complex template specialization for variadic templates

template <typename... Args>
inline int android_log_print(int priority,
    const char* tag, Args... args)
{

    return __android_log_print(priority, tag, args...);
}

inline int android_log_print(int priority, const char* tag, const std::string& message)
{

    return android_log_print(priority, tag, "%s", message.data());
}

template <typename... Args>
inline void android_log_assert(const char* cond, const char* tag, Args... args)
{
    __android_log_assert(cond, tag, args...);
}

inline void android_log_assert(const char* cond, const char* tag, const std::string& message)
{

    __android_log_assert(cond, tag, "%s", message.data());
}
}

template <typename... Args>
int AndroidLog::v(const char* tag, Args... args)
{

    return android_log_print(ANDROID_LOG_VERBOSE, tag, args...);
}

template <typename... Args>
int AndroidLog::d(const char* tag, Args... args)
{

    return android_log_print(ANDROID_LOG_DEBUG, tag, args...);
}

template <typename... Args>
int AndroidLog::i(const char* tag, Args... args)
{

    return android_log_print(ANDROID_LOG_INFO, tag, args...);
}

template <typename... Args>
int AndroidLog::w(const char* tag, Args... args)
{

    return android_log_print(ANDROID_LOG_WARN, tag, args...);
}

template <typename... Args>
int AndroidLog::e(const char* tag, Args... args)
{

    return android_log_print(ANDROID_LOG_ERROR, tag, args...);
}

template <typename... Args>
int AndroidLog::wtf(const char* tag, Args... args)
{

    return android_log_print(ANDROID_LOG_FATAL, tag, args...);
}

template <typename... Args>
void AndroidLog::assert_condition(bool cond, const char* condAsString, const char* tag, Args... args)
{

    if (!cond) {
        android_log_assert(condAsString, tag, args...);
    }
}
