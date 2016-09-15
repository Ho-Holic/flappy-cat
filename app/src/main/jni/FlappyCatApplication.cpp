// self
#include "FlappyCatApplication.h"
#include "AndroidClock.h"
#include "Log.h"

// tmp
#include <random>

// opengl
#include <GLES2/gl2.h>



FlappyCatApplication::FlappyCatApplication(ANativeActivity* activity,
                                           void* savedState,
                                           size_t savedStateSize)

: AndroidApplication(activity, savedState, savedStateSize)
, mSaturation(0.f)
, mBrightness(0.f) {
  //
}

void FlappyCatApplication::main() {


  constexpr AndroidFrameTime TimePerFrame = AndroidFrameTime(1);

  auto startTime = AndroidClock::now();
  auto timeSinceLastUpdate = AndroidClockDuration(0);

  // game loop
  while( ! isDestroyRequested()) {

    auto now = AndroidClock::now();
    auto elapsedTime = now - startTime;
    startTime = now;

    timeSinceLastUpdate += elapsedTime;

    while (timeSinceLastUpdate > TimePerFrame) {

      using std::chrono::duration_cast;
      timeSinceLastUpdate = timeSinceLastUpdate - duration_cast<AndroidClockDuration>(TimePerFrame);

      processEvents();
      //update(TimePerFrame);
    }
    render();
  }

}

void FlappyCatApplication::processEvents() {

  AndroidEvent event;
  while (pollEvent(event)) {

    if (event.type() == MotionEventType) {

      float x = event.motionEvent().x;
      float y = event.motionEvent().y;

      //Log::i(TAG, "(x: %g, y: %g)", x, y);

      mSaturation = x / window().width();
      mBrightness = y / window().height();
    }

  }
}

void FlappyCatApplication::render() {

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 255);

  GLclampf r = static_cast<GLclampf>(dis(gen)) / 255.f;
  GLclampf g = static_cast<GLclampf>(dis(gen)) / 255.f;
  GLclampf b = static_cast<GLclampf>(dis(gen)) / 255.f;

  GLclampf mid = (r + g + b) / 3.f;

  // set saturation
  r = mid + (r - mid) * (mSaturation / (1.f - mSaturation));
  g = mid + (g - mid) * (mSaturation / (1.f - mSaturation));
  b = mid + (b - mid) * (mSaturation / (1.f - mSaturation));

  // set brightness
  r *= mBrightness;
  g *= mBrightness;
  b *= mBrightness;

  // Just fill the screen with a color.
  glClearColor(r, g, b, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  window().display();
}
