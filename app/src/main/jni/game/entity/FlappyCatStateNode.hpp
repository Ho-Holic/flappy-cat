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
    void update(const FrameDuration& frameDuration) override;
    void drawOn(const Window& window, const RenderContext& renderContext) const override;

private:
    initialize_modifier_type m_initializeModifier;
    reset_modifier_type m_resetModifier;
    update_modifier_type m_updateModifier;
    draw_modifier_type m_drawModifier;
};

// implementation

template <typename T>
void FlappyCatStateNode<T>::initialize()
{
    m_initializeModifier(*static_cast<entity_type*>(this));
}

template <typename T>
void FlappyCatStateNode<T>::reset()
{
    m_resetModifier(*static_cast<entity_type*>(this));
}

template <typename T>
void FlappyCatStateNode<T>::update(const FrameDuration& frameDuration)
{
    m_updateModifier(*static_cast<entity_type*>(this), frameDuration);
}

template <typename T>
void FlappyCatStateNode<T>::drawOn(const Window& window, const RenderContext& renderContext) const
{
    m_drawModifier(*static_cast<const entity_type*>(this), window);
}

template <typename T>
FlappyCatStateNode<T>::FlappyCatStateNode(const FlappyCatGameConstants& gameConstants)
    : FlappyCatEntity(gameConstants)
    , m_initializeModifier([](entity_type&) {})
    , m_resetModifier([](entity_type&) {})
    , m_updateModifier([](entity_type&, const FrameDuration&) {})
    , m_drawModifier([](const entity_type&, const Window&) {})
{
    //
}

template <typename T>
void FlappyCatStateNode<T>::setInitializeModifier(initialize_modifier_type modifier)
{
    m_initializeModifier = modifier;
}

template <typename T>
void FlappyCatStateNode<T>::setResetModifier(reset_modifier_type modifier)
{
    m_resetModifier = modifier;
}

template <typename T>
void FlappyCatStateNode<T>::setUpdateModifier(update_modifier_type modifier)
{
    m_updateModifier = modifier;
}

template <typename T>
void FlappyCatStateNode<T>::setDrawModifier(draw_modifier_type modifier)
{
    m_drawModifier = modifier;
}
