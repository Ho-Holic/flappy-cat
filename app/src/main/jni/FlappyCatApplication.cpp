// self
#include "FlappyCatApplication.h"
#include "core/Clock.h"
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


  constexpr FrameDuration TimePerFrame = FrameDuration(1);

  auto startTime = Clock::now();
  auto timeSinceLastUpdate = ClockDuration(0);

  // game loop
  while( ! isDestroyRequested()) {

    auto now = Clock::now();
    auto elapsedTime = now - startTime;
    startTime = now;

    timeSinceLastUpdate += elapsedTime;

    while (timeSinceLastUpdate > TimePerFrame) {

      using std::chrono::duration_cast;
      timeSinceLastUpdate = timeSinceLastUpdate - duration_cast<ClockDuration>(TimePerFrame);

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

  Color color(Color::random());

  Color gray(color.grayscale());
  color = gray + (color - gray) * (mSaturation / (1.f - mSaturation));
  color *= mBrightness;


  window().clear(color);

  Vertices v;

//  v << Vertex(AndroidPosition(0.0f,  0.5f),  Color(255, 0, 0))
//    << Vertex(AndroidPosition(-0.5f, -0.5f), Color(0, 255, 0))
//    << Vertex(AndroidPosition(0.5f, -0.5f),  Color(0, 0, 255));

  v << Vertex(Position(0.0f,  0.5f),  Color::random())
    << Vertex(Position(-0.5f, -0.5f), Color::random())
    << Vertex(Position(0.5f, -0.5f),  Color::random());

  window().drawVertices(v);
  window().display();
}
