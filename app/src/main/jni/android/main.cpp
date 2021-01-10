// ndk
#include <android/native_activity.h>

// game
#include "android/FlappyCatApplication.hpp"

// engine
#include <core/Log.hpp>

// stl
#include <thread>

//  Hello! This is a list of some conventions and decisions made for this project:
//
//    1. Namespaces not used - project too small. One can easily auto-replace 'FlappyCat' prefix
//       with 'flp::' namespace
//
//    2. Java   'Log::i(TAG, "Creating: %p\n", activity);' was prefered to
//       C++ish 'log_i(TAG) << "Creating: " << activity << "\n";' because of confusion
//       more simple implementation
//
//    3. Macro 'DISABLE_COPY' prefered to manual '= delete' because of direct intent to disable copy
//
//    4. Initialize smart pointers  'shared_ptr(nullptr)' instead of 'shared_ptr()'
//       for readability and back compatibility with raw pointers
//
//    5. Use of UNUSED macro for every case, even if I can omit it in well
//       known places like 'std::lock_guard'
//

//  Known errors, glitches and strange behaviour
//
//    1. Linker error 'unused DT entry: type blahhh arg blabla'
//       http://stackoverflow.com/questions/33206409/unused-dt-entry-type-0x1d-arg
//
//    2. In 'app/build.gradle' link against 'atomic'
//       https://code.google.com/p/android/issues/detail?id=68779
//
//    3. If Java can't find 'ANativeActivity_onCreate', read article 'Make sure glue isn't stripped'
//       http://blog.beuc.net/posts/Make_sure_glue_isn__39__t_stripped/

extern "C" {

  void ANativeActivity_onCreate(ANativeActivity* activity,
                                void* savedState,
                                size_t savedStateSize) {

    Log::i(TAG, "Creating: %p\n", activity);

    FlappyCatApplication* application = new FlappyCatApplication(activity,
                                                                 savedState, savedStateSize);
    // Create 'event handler' thread
    //   - don't capture 'application' pointer, this would produce less readable code
    auto eventLoopWorker = [](FlappyCatApplication* app) -> void {
      app->exec();
    };

    std::thread eventLoopThread(std::ref(eventLoopWorker), std::ref(application));
    eventLoopThread.detach();

    // Wait until 'eventLoopWorker' properly lunch the event loop
    application->waitForStarted();
  }
}

