// self
#include "FlappyCatGame.h"

FlappyCatGame::FlappyCatGame()
    : mSaturation(0.f)
    , mBrightness(0.f)
    , mSizeFactor(0)
    , mRect(Position(0.f, 0.f), Position(0.5f, 0.5f))
    , mCircle(Position(0.f, 0.f), 0.25f, 4){
  //
}

void FlappyCatGame::processEvent(const AndroidEvent& event) {

  if (event.type() == MotionEventType) {

    float x = event.motionEvent().x;
    float y = event.motionEvent().y;

    //Log::i(TAG, "(x: %g, y: %g)", x, y);

    //mSaturation = x / window().width();
    //mBrightness = y / window().height();
  }
}

void FlappyCatGame::update(const FrameDuration& time) {

  float pos[9] = {-1.f, -0.75f, -0.5f, -0.25f, 0.f, 0.25f, 0.5f, 0.75f, 1.f};

  mRect.transformation().setPosition(Position(0.f, pos[mSizeFactor]));
  mCircle.transformation().setPosition(Position(pos[mSizeFactor], 0.f));

  mCircle.geometry().setResolution((mSizeFactor % 2 == 0) ? 4 : 8);

  mSizeFactor = (mSizeFactor + 1) % 9;
}

void FlappyCatGame::render(const AndroidWindow& window) {

  Color color(Color::random());

  Color gray(color.grayscale());
  color = gray + (color - gray) * (mSaturation / (1.f - mSaturation));
  color *= mBrightness;


  window.clear(color);

  Vertices v;
  v << Vertex(Position(0.0f,  0.5f),  Color::random())
  << Vertex(Position(-0.5f, -0.5f), Color::random())
  << Vertex(Position(0.5f, -0.5f),  Color::random());

  FlatTransformation flatTransformation;
  window.drawVertices(v, flatTransformation);

  window.draw(mRect);
  window.draw(mCircle);
  window.display();
}


