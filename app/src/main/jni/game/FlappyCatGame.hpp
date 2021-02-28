#pragma once

#include "FlappyCatGameConstants.hpp"
#include "entity/FlappyCatBackground.hpp"
#include "entity/FlappyCatChain.hpp"
#include "entity/FlappyCatCloud.hpp"
#include "entity/FlappyCatEntity.hpp"
#include "entity/FlappyCatFloor.hpp"
#include "entity/FlappyCatHero.hpp"
#include "entity/FlappyCatSpike.hpp"
#include "entity/FlappyCatText.hpp"
#include "entity/FlappyCatViewLimit.hpp"
#include "entity/FlappyCatWall.hpp"
#include <cmath>
#include <core/Clock.hpp>
#include <core/Event.hpp>
#include <core/Window.hpp>
#include <memory>
#include <prototype/RectangleShape.hpp>
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

private:
    FlappyCatGameConstants m_gameConstants;
    GameState m_gameState;

    // elements
    FlappyCatBackground m_background;
    FlappyCatFloor m_floor;
    FlappyCatChain<FlappyCatWall> m_barricade;
    FlappyCatChain<FlappyCatSpike> m_backgroundCity;
    FlappyCatCloud m_backgroundSky;
    FlappyCatHero m_hero;
    FlappyCatViewLimit m_limit;

    // score element
    FlappyCatText m_score;
    size_t m_scoreCounter;

    // fps element
    FlappyCatText m_fps;
    size_t m_fpsCounter;
};

enum FlappyCatGame::GameState : int32_t {
    PressButtonState,
    PlayState,
    LoseState,
    OnTheFloorState
};
