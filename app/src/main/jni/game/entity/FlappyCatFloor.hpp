#pragma once

// game
#include "FlappyCatChain.hpp"
#include "FlappyCatEntity.hpp"
#include "FlappyCatSpike.hpp"

// engine
#include <prototype/RectangleShape.hpp>

class FlappyCatFloor : public FlappyCatEntity {
public:
    using entity_type = FlappyCatFloor;
    using modifier_type = std::function<void(entity_type&)>;
    using update_modifier_type = std::function<void(entity_type&, const FrameDuration& time)>;

public:
    FlappyCatFloor(const FlappyCatGameConstants& gameConstants);

public:
    const RectangleShape& boundingBox() const;

public:
    virtual void initialize() override;
    virtual void drawOn(const Window& window) const override;
    virtual void update(const FrameDuration& time) override;
    virtual void reset() override;

public:
    void setColor(const Color& floorColor, const Color& dirtColor);
    void setResetModifier(const modifier_type& modifier);
    void setUpdateModifier(const update_modifier_type& modifier);
    void setMovementDisplacement(const Position& movementDisplacement);
    void setDecorationSizes(const Position& surfaceSize, const Position& spikesSize);

private:
    virtual void syncChildren() override;

private:
    Position mOrganicSurfaceSize;
    Position mSpikesSize;
    RectangleShape mFloor;
    FlappyCatChain<FlappyCatSpike> mFloorSpikes;
    RectangleShape mBackgroundDirt;
    modifier_type mResetModifier;
    update_modifier_type mUpdateModifier;
};