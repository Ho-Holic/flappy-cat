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
  forever() {

    AndroidEvent event;
    while (looper().pollEvent(event)) {

      // check if we exiting
      // TODO: replace `forever` loop with `while( ! isDestroyRequested())`
      if (isDestroyRequested()) {
        return;
      }
    }
  }

}
