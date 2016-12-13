// self
#include "FlappyCatGame.h"

FlappyCatGame::FlappyCatGame()
    : mSaturation(0.f)
    , mBrightness(0.f)
    , mSizeFactor(0)
    , mRect(Position(0, 0), Position(100.f, 100.f))
    , mCircle(Position(0.f, 0.f), 0.25f, 4){
  //
}

void FlappyCatGame::processEvent(const AndroidEvent& event) {

  if (event.type() == TouchEventType) {

    float x = event.touchEvent().x;
    float y = event.touchEvent().y;

    mRect.transformation().setPosition(mRect.transformation().position() + Position(0.f, 200.f));

    //Log::i(TAG, "(x: %g, y: %g)", x, y);

    //mSaturation = x / window().width();
    //mBrightness = y / window().height();
  }
}

void FlappyCatGame::update(const FrameDuration& time) {

  mRect.transformation().setPosition(mRect.transformation().position() + Position(0.f, -10.f));

  mSizeFactor = (mSizeFactor + 1) % 9;
}

void FlappyCatGame::render(const AndroidWindow& window) {

  //Color color(Color::random());

  //Color gray(color.grayscale());
  //color = gray + (color - gray) * (mSaturation / (1.f - mSaturation));
  //color *= mBrightness;


  //window.clear(color);
  window.clear(0xffffffff);

  //Vertices v;
  //v << Vertex(Position(0.0f,  0.5f),  Color::random())
  //<< Vertex(Position(-0.5f, -0.5f), Color::random())
  //<< Vertex(Position(0.5f, -0.5f),  Color::random());

  //FlatTransformation flatTransformation;
  //window.drawVertices(v, flatTransformation);

  window.draw(mRect);
  //window.draw(mCircle);
  window.display();
}


