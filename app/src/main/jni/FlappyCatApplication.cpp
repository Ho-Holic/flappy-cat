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

//  std::random_device rd;
//  std::mt19937 gen(rd());
//  //-------------------------------   0    2^24
//  std::uniform_int_distribution<> dis(0, 16777215);
//
//  int fullColor = dis(gen);
//
//  int mask = 0x0000ff;
//  int splitR = ((fullColor >> 24) & mask);
//  int splitG = ((fullColor >> 16 ) & mask);
//  int splitB = ((fullColor >> 8 ) & mask);
//
//
//  GLclampf r = static_cast<GLclampf>(splitR) / 255.f;
//  GLclampf g = static_cast<GLclampf>(splitG) / 255.f;
//  GLclampf b = static_cast<GLclampf>(splitB) / 255.f;
//
//  GLclampf mid = (r + g + b) / 3.f;
//
//  // set saturation
//  r = mid + (r - mid) * (mSaturation / (1.f - mSaturation));
//  g = mid + (g - mid) * (mSaturation / (1.f - mSaturation));
//  b = mid + (b - mid) * (mSaturation / (1.f - mSaturation));
//
//  // set brightness
//  r *= mBrightness;
//  g *= mBrightness;
//  b *= mBrightness;
//
//  // Just fill the screen with a color.
//  glClearColor(r, g, b, 1);
//  glClear(GL_COLOR_BUFFER_BIT);


  // clear screen

  window().clear(0xffffffff);

//  glViewport(0, 0, window().width(), window().height());
//
//  glClearColor(1.f, 1.f, 1.f, 1);
//  glClear(GL_COLOR_BUFFER_BIT);
//
//  // draw some rect
//
//  GLuint positionBufferObject;
//
//  const float vertexPositions[] = {
//    0.75f, 0.75f, 0.0f, 1.0f,
//    0.75f, -0.75f, 0.0f, 1.0f,
//    -0.75f, -0.75f, 0.0f, 1.0f,
//  };
//
//  // allocate space
//  glGenBuffers(1, &positionBufferObject);
//
//  glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
//  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
//  glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//  // draw triangle
//  glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
//  glEnableVertexAttribArray(0);
//  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
//  glDrawArrays(GL_TRIANGLES, 0, 3);
//  glDisableVertexAttribArray(0);

  // display
  window().display();
}
