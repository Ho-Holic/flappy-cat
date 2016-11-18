// self
#include "FlappyCatApplication.h"

FlappyCatApplication::FlappyCatApplication(ANativeActivity* activity,
                                           void* savedState,
                                           size_t savedStateSize)

: AndroidApplication(activity, savedState, savedStateSize)
, mSaturation(0.f)
, mBrightness(0.f)
, mSizeFactor(0)
, mRect(Position(0.f, 0.f), Position(-0.5, -0.5))
, mCircle(Position(0.f, -1.f), 0.5f, 4) {
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

void FlappyCatApplication::update(const FrameDuration &time) {
  mSizeFactor = (mSizeFactor + 1) % 8;

  std::size_t x2 = ((mSizeFactor % 2) != 0) ? 1 : 2;

  mRect.geometry().resize(Position(-0.5 * x2, -0.5 * x2));
  mCircle.geometry().setRadius(0.5 / x2);

  size_t res = 4;

  for(size_t i = 0; i < mSizeFactor; ++i) {
    res *= 2;
  }

  mCircle.geometry().setResolution(res);

}


void FlappyCatApplication::render() {

  Color color(Color::random());

  Color gray(color.grayscale());
  color = gray + (color - gray) * (mSaturation / (1.f - mSaturation));
  color *= mBrightness;


  window().clear(color);

  Vertices v;
  v << Vertex(Position(0.0f,  0.5f),  Color::random())
    << Vertex(Position(-0.5f, -0.5f), Color::random())
    << Vertex(Position(0.5f, -0.5f),  Color::random());

  FlatTransformation flatTransformation;
  window().drawVertices(v, flatTransformation);

  window().draw(mRect);
  window().draw(mCircle);
  window().display();
}


