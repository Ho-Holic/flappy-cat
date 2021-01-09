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

  f32 windowHeight = static_cast<f32>(window().height());

  f32 cameraHeight = game.cameraSize().y();

  f32 scale = windowHeight / cameraHeight;

  window().view().setScale(Position(scale, scale));

  // game loop
  using std::chrono::duration_cast;
  constexpr FrameDuration TimePerFrame = FrameDuration(1);

  auto startTime = Clock::now();
  auto timeSinceLastUpdate = ClockDuration(0);
  auto measurement = 0.f;
  auto smoothing = 0.9f;

  while( ! isDestroyRequested()) {

    auto now = Clock::now();
    auto elapsedTime = now - startTime;

    // fps counter
    {
      measurement = (measurement * smoothing) + duration_cast<GameSecond>(elapsedTime).count() * (1.f - smoothing);
      game.setFpsCounter(static_cast<size_t>(1.f / measurement));
    }

    startTime = now;

    timeSinceLastUpdate += elapsedTime;

    while (timeSinceLastUpdate > TimePerFrame) {

      timeSinceLastUpdate = timeSinceLastUpdate - duration_cast<ClockDuration>(TimePerFrame);

      Event event;
      while (pollEvent(event)) {
        game.processEvent(event);
      }

      game.update(TimePerFrame);
    }

    if (!window().isReady()) {
      break; // pollEvent processed window termination event and window is not ready and invalid
    }

    game.render(window());
  }
}


