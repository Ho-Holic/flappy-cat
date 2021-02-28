#pragma once

// ndk
#include <android/configuration.h>
#include <android/native_activity.h>

// std
#include <condition_variable>
#include <mutex>
#include <queue>

// style
#include <style/Guidelines.hpp>

// engine
#include "AndroidConfiguration.hpp"
#include "AndroidLooper.hpp"
#include "AndroidWindow.hpp"

class AndroidApplication {

private:
    enum ActivityState : int8_t;
    enum Focus : int;

private:
    AndroidApplication(const AndroidApplication&) = delete;
    AndroidApplication& operator=(const AndroidApplication&) = delete;

public:
    AndroidApplication(ANativeActivity* activity,
        void* savedState,
        size_t savedStateSize);
    virtual ~AndroidApplication();

public:
    bool isRunning() const;
    bool isDestroyed() const;
    bool isDestroyRequested() const;
    ActivityState activityState() const;
    void exec();
    bool pollEvent(AndroidEvent& event);
    void postEvent(const AndroidEvent& event);
    const AndroidWindow& window() const;
    AndroidWindow& window();

private:
    void initialize();
    void terminate();
    void processEvent(const AndroidEvent& event);
    void setActivityState(ActivityState activityState);
    void resizeNativeWindow(const AndroidEvent& event);
    void initializeNativeWindow(const AndroidEvent& event);
    void terminateNativeWindow(const AndroidEvent& event);
    void setInputQueue(const AndroidEvent& event);
    void setEventLoopState(const AndroidEvent& event);

private:
    virtual void main() = 0; // private because launched from 'AndroidApplication::exec()'

    //
    // code called from main thread
    //
private:
    static void onDestroy(ANativeActivity* activity);
    static void onStart(ANativeActivity* activity);
    static void onResume(ANativeActivity* activity);
    static void* onSaveInstanceState(ANativeActivity* activity, size_t* outLen);
    static void onPause(ANativeActivity* activity);
    static void onStop(ANativeActivity* activity);
    static void onConfigurationChanged(ANativeActivity* activity);
    static void onLowMemory(ANativeActivity* activity);
    static void onWindowFocusChanged(ANativeActivity* activity, int hasFocus);
    static void onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window);
    static void onNativeWindowResized(ANativeActivity* activity, ANativeWindow* window);
    static void onNativeWindowRedrawNeeded(ANativeActivity* activity, ANativeWindow* window);
    static void onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window);
    static void onInputQueueCreated(ANativeActivity* activity, AInputQueue* queue);
    static void onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue);
    static void onContentRectChanged(ANativeActivity* activity, const ARect* rect);

public:
    void waitForStarted(); // temporary in public due to sketch design of 'main' function

private:
    void waitForDestruction();
    void changeActivityStateTo(ActivityState activityState);
    void changeNativeWindow(ANativeWindow* window);
    void changeInputQueue(AInputQueue* queue);
    void changeNativeWindowSize();
    void changeFocus(Focus focus);
    void reloadConfiguration();

private:
    ANativeActivity* m_activity;
    ActivityState m_activityState;
    std::mutex m_mutex;
    std::condition_variable m_conditionVariable;
    bool m_isRunning;
    bool m_isDestroyed;
    bool m_isDestroyRequested;
    AndroidConfiguration m_configuration;
    AndroidLooper m_looper;
    AndroidWindow m_window;
    std::queue<AndroidEvent> m_events; // TODO: add thread safe queue
};

// enums

enum AndroidApplication::ActivityState : int8_t {
    InitializationActivityState,
    StartActivityState,
    ResumeActivityState,
    PauseActivityState,
    StopActivityState,
};

enum AndroidApplication::Focus : int {
    GainFocus,
    LostFocus,
};
