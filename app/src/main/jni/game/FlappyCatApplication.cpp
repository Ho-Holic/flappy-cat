// game
#include "FlappyCatApplication.h"

FlappyCatApplication::FlappyCatApplication(ANativeActivity* activity,
                                           void* savedState,
                                           size_t savedStateSize)

: AndroidApplication(activity, savedState, savedStateSize) {
  //
}

void FlappyCatApplication::main() {

  // set apropriate view
  FlappyCatGame game;

  Position::value_type windowHeight = static_cast<Position::value_type>(window().height());

  Position::value_type cameraHeight = game.cameraSize().y();

  Position::value_type scale = windowHeight / cameraHeight;

  window().view().setScale(Position(scale, scale));

  // game loop
  constexpr FrameDuration TimePerFrame = FrameDuration(1);

  auto startTime = Clock::now();
  auto timeSinceLastUpdate = ClockDuration(0);

  while( ! isDestroyRequested()) {

    auto now = Clock::now();
    auto elapsedTime = now - startTime;
    startTime = now;

    timeSinceLastUpdate += elapsedTime;

    while (timeSinceLastUpdate > TimePerFrame) {

      using std::chrono::duration_cast;

      timeSinceLastUpdate = timeSinceLastUpdate - duration_cast<ClockDuration>(TimePerFrame);

      Event event;
      while (pollEvent(event)) {
        game.processEvent(event);
      }

      game.update(TimePerFrame);
    }
    game.render(window());
  }
}


