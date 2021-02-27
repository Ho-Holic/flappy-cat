#pragma once

#include "FlappyCatEntity.hpp"

template <typename T>
class FlappyCatStateNode : public FlappyCatEntity {
public:
    using entity_type = T;
    using initialize_modifier_type = std::function<void(entity_type&)>;
    using reset_modifier_type = std::function<void(entity_type&)>;
    using update_modifier_type = std::function<void(entity_type&, const FrameDuration&)>;
    using draw_modifier_type = std::function<void(const entity_type&, const Window&)>;

public:
    FlappyCatStateNode(const FlappyCatGameConstants& gameConstants);

public:
    void setInitializeModifier(initialize_modifier_type modifier);
    void setResetModifier(reset_modifier_type modifier);
    void setUpdateModifier(update_modifier_type modifier);
    void setDrawModifier(draw_modifier_type modifier);

public:
    void initialize() override;
    void reset() override;
    void drawOn(const Window& window) const override;
    void update(const FrameDuration& frameDuration) override;

private:
    initialize_modifier_type mInitializeModifier;
    reset_modifier_type mResetModifier;
    update_modifier_type mUpdateModifier;
    draw_modifier_type mDrawModifier;
};

// implementation

template <typename T>
void FlappyCatStateNode<T>::initialize()
{
    FlappyCatEntity::initialize();
    mInitializeModifier(*static_cast<entity_type*>(this));
}

template <typename T>
void FlappyCatStateNode<T>::reset()
{
    FlappyCatEntity::reset();
    mResetModifier(*static_cast<entity_type*>(this));
}

template <typename T>
void FlappyCatStateNode<T>::update(const FrameDuration& frameDuration)
{
    FlappyCatEntity::update(frameDuration);
    mUpdateModifier(*static_cast<entity_type*>(this), frameDuration);
}

template <typename T>
void FlappyCatStateNode<T>::drawOn(const Window& window) const
{
    mDrawModifier(*static_cast<const entity_type*>(this), window);
}

template <typename T>
FlappyCatStateNode<T>::FlappyCatStateNode(const FlappyCatGameConstants& gameConstants)
    : FlappyCatEntity(gameConstants)
    , mInitializeModifier([](entity_type&) {})
    , mResetModifier([](entity_type&) {})
    , mUpdateModifier([](entity_type&, const FrameDuration&) {})
    , mDrawModifier([](const entity_type&, const Window&) {})
{
    //
}

template <typename T>
void FlappyCatStateNode<T>::setInitializeModifier(initialize_modifier_type modifier)
{
    mInitializeModifier = modifier;
}

template <typename T>
void FlappyCatStateNode<T>::setResetModifier(reset_modifier_type modifier)
{
    mResetModifier = modifier;
}

template <typename T>
void FlappyCatStateNode<T>::setUpdateModifier(update_modifier_type modifier)
{
    mUpdateModifier = modifier;
}

template <typename T>
void FlappyCatStateNode<T>::setDrawModifier(draw_modifier_type modifier)
{
    mDrawModifier = modifier;
}
