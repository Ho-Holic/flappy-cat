// self
#include "FlappyCatApplication.h"
#include "Log.h"

// tmp
#include <random>

// opengl
#include <GLES2/gl2.h>

FlappyCatApplication::FlappyCatApplication(ANativeActivity* activity,
                                           void* savedState,
                                           size_t savedStateSize)

: AndroidApplication(activity, savedState, savedStateSize) {
  //
}

void FlappyCatApplication::main() {

  float saturation = 0.f;
  float brightness = 0.f;

  // game loop
  while( ! isDestroyRequested()) {

    AndroidEvent event;
    while (pollEvent(event)) {

      if (event.type() == MotionEventType) {

        float x = event.motionEvent().x;
        float y = event.motionEvent().y;

        //Log::i(TAG, "(x: %g, y: %g)", x, y);

        saturation = x / window().width();
        brightness = y / window().height();
      }

    }

    // update

    // draw some stuff
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);

    GLclampf r = static_cast<GLclampf>(dis(gen)) / 255.f;
    GLclampf g = static_cast<GLclampf>(dis(gen)) / 255.f;
    GLclampf b = static_cast<GLclampf>(dis(gen)) / 255.f;

    GLclampf mid = (r + g + b) / 3.f;

    // set saturation
    r = mid + (r - mid) * (saturation / (1.f - saturation));
    g = mid + (g - mid) * (saturation / (1.f - saturation));
    b = mid + (b - mid) * (saturation / (1.f - saturation));

    // set brightness
    r *= brightness;
    g *= brightness;
    b *= brightness;

    // Just fill the screen with a color.
    glClearColor(r, g, b, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    window().display();
  }

}
