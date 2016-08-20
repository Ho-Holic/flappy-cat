// self
#include "FlappyCatApplication.h"
#include "Log.h"

FlappyCatApplication::FlappyCatApplication(ANativeActivity* activity,
                                           void* savedState,
                                           size_t savedStateSize)

: AndroidApplication(activity, savedState, savedStateSize) {
  //
}

void FlappyCatApplication::main() {

  // game loop
  loop() {

    AndroidEvent event;
    while (pollEvent(event)) {

      // Check if we are exiting
      //   - not written as `while( ! isDestroyRequested())`
      //     in a main loop because we don't need to check
      //     every iteration, only when some event arrived
      if (isDestroyRequested()) {
        return;
      }
    }
  }

}
