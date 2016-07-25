// ndk
#include <android/native_activity.h>
#include <android/log.h>
#include <jni.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "FlappyCat", __VA_ARGS__))


void ANativeActivity_onCreate(ANativeActivity* activity,
                                void* savedState,
                                size_t savedStateSize) {
  //
}