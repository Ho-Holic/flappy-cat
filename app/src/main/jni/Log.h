#ifndef FLAPPY_CAT_LOG_H
#define FLAPPY_CAT_LOG_H

// ndk
#include <android/log.h>

// std
#include <string>

class Log {
public:
  template <typename... Args> static int v(const char* tag, Args... args);
  template <typename... Args> static int d(const char* tag, Args... args);
  template <typename... Args> static int i(const char* tag, Args... args);
  template <typename... Args> static int w(const char* tag, Args... args);
  template <typename... Args> static int e(const char* tag, Args... args);
  template <typename... Args> static int wtf(const char* tag, Args... args);
  template <typename... Args> static void assert(bool cond, const char* condAsString,
                                                 const char* tag, Args... args);
};

// implementation

namespace {

  // make this functions `free` to avoid complex template specialization for variadic templates

  template<typename... Args>
  inline int android_log_print(int priority,
                               const char *tag, Args... args) {

    return __android_log_print(priority, tag, args...);
  }

  inline int android_log_print(int priority, const char* tag, const std::string &message) {

    return android_log_print(priority, tag, "%s", message.data());
  }

}

template <typename... Args>
int Log::v(const char* tag, Args... args) {

  return android_log_print(ANDROID_LOG_VERBOSE, tag, args...);
}

template <typename... Args>
int Log::d(const char* tag, Args... args) {

  return android_log_print(ANDROID_LOG_DEBUG, tag, args...);
}

template <typename... Args>
int Log::i(const char* tag, Args... args) {

  return android_log_print(ANDROID_LOG_INFO, tag, args...);
}

template <typename... Args>
int Log::w(const char* tag, Args... args) {

  return android_log_print(ANDROID_LOG_WARN, tag, args...);
}

template <typename... Args>
int Log::e(const char* tag, Args... args) {

  return android_log_print(ANDROID_LOG_ERROR, tag, args...);
}

template <typename... Args>
int Log::wtf(const char* tag, Args... args) {

  return android_log_print(ANDROID_LOG_FATAL, tag, args...);
}

template<typename... Args>
void Log::assert(bool cond, const char* condAsString, const char* tag, Args... args) {

  if (! cond) {
    __android_log_assert(condAsString, tag, args...);
  }
}

#endif //FLAPPY_CAT_LOG_H


