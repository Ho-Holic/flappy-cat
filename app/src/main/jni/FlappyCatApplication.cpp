// self
#include "FlappyCatApplication.h"
#include "AndroidClock.h"
#include "Log.h"

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

  AndroidColor color(AndroidColor::random());

  AndroidColor gray(color.grayscale());
  color = gray + (color - gray) * (mSaturation / (1.f - mSaturation));
  color *= mBrightness;


  window().clear(color);
  window().drawVertices(AndroidVertices());
  window().display();
}
