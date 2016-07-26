#ifndef FLAPPYCAT_LOG_H
#define FLAPPYCAT_LOG_H

// ndk
#include <android/log.h>

class Log {
public:
  template <typename... Args>
  static int v(const char* tag, Args... args) {
    return Log::android_log_print(ANDROID_LOG_VERBOSE, tag, args...);
  }

private:
  template <typename... Args>
  static int android_log_print(int priority, const char* tag, Args... args) {
    return __android_log_print(priority, tag, args...);
  }
};

#endif //FLAPPYCAT_LOG_H
