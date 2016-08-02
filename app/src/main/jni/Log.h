#ifndef FLAPPY_CAT_LOG_H
#define FLAPPY_CAT_LOG_H

// ndk
#include <android/log.h>

class Log {
public:
  template <typename... Args> static int v(const char* tag, Args... args);
  template <typename... Args> static int d(const char* tag, Args... args);
  template <typename... Args> static int i(const char* tag, Args... args);
  template <typename... Args> static int w(const char* tag, Args... args);
  template <typename... Args> static int e(const char* tag, Args... args);
  template <typename... Args> static int wtf(const char* tag, Args... args);

  //static int v(std::string& )

private:
  template <typename... Args> static int android_log_print(int priority,
                                                           const char* tag, Args... args);

  static int android_log_print(int priority, const char* tag, const std::string& message);
};

// implementation

template <typename... Args>
int Log::v(const char* tag, Args... args) {
  return Log::android_log_print(ANDROID_LOG_VERBOSE, tag, args...);
}

template <typename... Args>
int Log::d(const char* tag, Args... args) {
  return Log::android_log_print(ANDROID_LOG_DEBUG, tag, args...);
}

template <typename... Args>
int Log::i(const char* tag, Args... args) {
  return Log::android_log_print(ANDROID_LOG_INFO, tag, args...);
}

template <typename... Args>
int Log::w(const char* tag, Args... args) {
  return Log::android_log_print(ANDROID_LOG_WARN, tag, args...);
}

template <typename... Args>
int Log::e(const char* tag, Args... args) {
  return Log::android_log_print(ANDROID_LOG_ERROR, tag, args...);
}

template <typename... Args>
int Log::wtf(const char* tag, Args... args) {
  return Log::android_log_print(ANDROID_LOG_FATAL, tag, args...);
}

template <typename... Args>
int Log::android_log_print(int priority, const char* tag, Args... args) {
  return __android_log_print(priority, tag, args...);
}

int Log::android_log_print(int priority, const char* tag, const std::string& message) {
  return android_log_print(priority, tag, "%s", message.data());
}

#endif //FLAPPY_CAT_LOG_H


