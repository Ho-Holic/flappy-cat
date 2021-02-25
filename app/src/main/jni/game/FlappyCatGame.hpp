#pragma once

// engine
#include <core/Clock.hpp>
#include <core/Event.hpp>
#include <core/Window.hpp>
#include <prototype/RectangleShape.hpp>

// game
#include "FlappyCatGameConstants.hpp"
#include "entity/FlappyCatBackground.hpp"
#include "entity/FlappyCatChain.hpp"
#include "entity/FlappyCatCloud.hpp"
#include "entity/FlappyCatFloor.hpp"
#include "entity/FlappyCatHero.hpp"
#include "entity/FlappyCatNode.hpp"
#include "entity/FlappyCatSpike.hpp"
#include "entity/FlappyCatText.hpp"
#include "entity/FlappyCatViewLimit.hpp"
#include "entity/FlappyCatWall.hpp"

// stl
#include <cmath>
#include <memory>
#include <vector>

class FlappyCatGame {
public:
    FlappyCatGame();

public:
    void processEvent(const Event& event);
    void update(const FrameDuration& time);
    void render(const Window&) const;
    Position cameraSize() const;
    void setFpsCounter(size_t fpsCount);

private:
    enum GameState : int32_t;

private:
    void initialize();
    void reset();
    void incrementScore();
    void resetScore();

private:
    FlappyCatGameConstants mGameConstants;
    GameState mGameState;

    // elements
    FlappyCatBackground mBackground;
    FlappyCatFloor mFloor;
    FlappyCatChain<FlappyCatWall> mBarricade;
    FlappyCatChain<FlappyCatSpike> mBackgroundCity;
    FlappyCatCloud mBackgroundSky;
    FlappyCatHero mHero;
    FlappyCatViewLimit mLimit;

    // score element
    FlappyCatText mScore;
    size_t mScoreCounter;

    // fps element
    FlappyCatText mFps;
    size_t mFpsCounter;
};

enum FlappyCatGame::GameState : int32_t {
    PressButtonState,
    PlayState,
    LoseState,
    OnTheFloorState
};
