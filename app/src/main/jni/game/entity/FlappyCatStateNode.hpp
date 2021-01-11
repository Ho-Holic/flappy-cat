#pragma once


#include "FlappyCatNode.hpp"

template <typename T>
class FlappyCatStateNode : public FlappyCatNode {
public:
  using shared = std::shared_ptr<T>;
  using children = std::vector<typename T::shared>;
  using entity_type = T;
  using reset_modifier_type = std::function<void(entity_type&)>;
  using update_modifier_type = std::function<void(entity_type&, const FrameDuration&)>;
  using draw_modifier_type = std::function<void(entity_type&, const Window&)>;
  using initialize_modifier_type = std::function<void(entity_type&)>;
public:
  FlappyCatStateNode();
public:
  void setResetModifier(reset_modifier_type modifier);
  void setUpdateModifier(update_modifier_type modifier);
  void setDrawModifier(draw_modifier_type modifier);
  void setInitializeModifier(initialize_modifier_type modifier);
public:
  virtual void initialize();
  virtual void reset();
  virtual void drawOn(const Window& window) const;
  virtual void update(const FrameDuration& frameDuration);
private:
  reset_modifier_type mResetModifier;
  update_modifier_type mUpdateModifier;
  initialize_modifier_type mInitializeModifier;
  draw_modifier_type mDrawModifier;
};

// implementation

template <typename T>
void FlappyCatStateNode<T>::initialize() {
  mInitializeModifier(*static_cast<entity_type*>(this));
}

template <typename T>
void FlappyCatStateNode<T>::reset() {
  mResetModifier(*static_cast<entity_type*>(this));
}

template <typename T>
void FlappyCatStateNode<T>::drawOn(const Window& window) const {
  mDrawModifier(*static_cast<entity_type*>(this), window);
  FlappyCatNode::drawOn(window);
}

template <typename T>
void FlappyCatStateNode<T>::update(const FrameDuration& frameDuration) {

  mUpdateModifier(*static_cast<entity_type*>(this), frameDuration);
  FlappyCatNode::update(frameDuration);
}

template <typename T>
FlappyCatStateNode<T>::FlappyCatStateNode()
: mResetModifier([](entity_type&){})
, mUpdateModifier([](entity_type&, const FrameDuration&){})
, mInitializeModifier([](entity_type&){})
, mDrawModifier([](entity_type&, const Window&){}) {
  //
}

template <typename T>
void FlappyCatStateNode<T>::setDrawModifier(draw_modifier_type modifier) {
  mDrawModifier = modifier;
}

template <typename T>
void FlappyCatStateNode<T>::setResetModifier(reset_modifier_type modifier) {
  mResetModifier = modifier;
}

template <typename T>
void FlappyCatStateNode<T>::setUpdateModifier(update_modifier_type modifier) {
  mUpdateModifier = modifier;
}

template <typename T>
void FlappyCatStateNode<T>::setInitializeModifier(initialize_modifier_type modifier) {
  mInitializeModifier = modifier;
}


