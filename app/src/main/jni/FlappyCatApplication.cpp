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
  while( ! isDestroyRequested()) {

    AndroidEvent event;
    while (pollEvent(event)) {
      // process me
    }

    // update
    window().draw();
  }

}
