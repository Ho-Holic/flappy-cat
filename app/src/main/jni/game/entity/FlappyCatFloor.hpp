#pragma once

#include "FlappyCatChain.hpp"
#include "FlappyCatSpike.hpp"
#include "FlappyCatStateNode.hpp"
#include <prototype/RectangleShape.hpp>

class FlappyCatFloor : public FlappyCatStateNode<FlappyCatFloor> {
public:
    FlappyCatFloor(const FlappyCatGameConstants& gameConstants);

public:
    const RectangleShape& boundingBox() const;

public:
    void initialize() override;
    void drawOn(const Window& window, const Transformation& transformation) const override;
    void update(const FrameDuration& time) override;
    void reset() override;

public:
    void setColor(const Color& floorColor, const Color& dirtColor);
    void setMovementDisplacement(const vec2& movementDisplacement);
    void setDecorationSizes(const vec2& surfaceSize, const vec2& spikesSize);

private:
    void syncChildren() override;

private:
    vec2 m_organicSurfaceSize;
    vec2 m_spikesSize;
    RectangleShape m_floor;
    FlappyCatChain<FlappyCatSpike> m_floorSpikes;
    RectangleShape m_backgroundDirt;
};
