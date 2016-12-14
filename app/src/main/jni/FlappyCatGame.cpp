// self
#include "FlappyCatGame.h"

FlappyCatGame::FlappyCatGame()
  : mBlocks(
      {
        RectangleShape(Position(-150.f, 600.f), Position(400.f, 100.f)),
        RectangleShape(Position(-150.f, -1000.f), Position(400.f, 100.f))
      }
    )
  , mCircle(Position(0.f, 0.f), 50.f, 32u){
  //
}

void FlappyCatGame::processEvent(const AndroidEvent& event) {

  if (event.type() == TouchEventType) {

    mCircle.transformation().move(Position(0.f, 400.f));
  }
}

void FlappyCatGame::update(const FrameDuration& time) {

  mCircle.transformation().move(Position(0.f, -10.f));
}

void FlappyCatGame::render(const AndroidWindow& window) {

  window.clear(Color(255, 255, 255));

  for(const RectangleShape& block : mBlocks) {
    window.draw(block);
  }

  window.draw(mCircle);

  window.display();
}


