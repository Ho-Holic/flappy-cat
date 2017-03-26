// self
#include "FlappyCatApplication.h"
#include "FlappyCatClock.h"

FlappyCatApplication::FlappyCatApplication(ANativeActivity* activity,
                                           void* savedState,
                                           size_t savedStateSize)

: AndroidApplication(activity, savedState, savedStateSize) {
  //
}

void FlappyCatApplication::main() {

  // set apropriate view
  FlappyCatGame game;

  Position::value_type windowWidth = static_cast<Position::value_type>(window().width());

  Position::value_type cameraWidth = game.cameraSize().x();

  Position::value_type scale = windowWidth / cameraWidth;

  window().view().setScale(Position(scale, scale));

  // run loop

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

      Event event;
      while (pollEvent(event)) {
        game.processEvent(event);
      }

      game.update(TimePerFrame);
    }
    game.render(window());
  }
}


