#pragma once

// engine
#include <android/AndroidApplication.hpp>
#include <prototype/CircleShape.hpp>
#include <prototype/RectangleShape.hpp>

// game
#include "FlappyCatClock.hpp"
#include "FlappyCatGame.hpp"

class FlappyCatApplication : public AndroidApplication {
public:
    FlappyCatApplication(ANativeActivity* activity,
        void* savedState,
        size_t savedStateSize);

private:
    virtual void main();
};
