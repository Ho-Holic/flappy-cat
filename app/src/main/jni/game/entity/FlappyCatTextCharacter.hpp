#pragma once


// game
#include "FlappyCatEntity.hpp"

// engine
#include <prototype/RectangleShape.hpp>

// stl
#include <array>

class FlappyCatTextCharacter : public FlappyCatEntity {
public:
  FlappyCatTextCharacter(const FlappyCatGameConstants& gameConstants);
public:
  virtual void drawOn(const Window& window) const override;
  virtual const Position& size() const override;

public:
  void setCharacter(char character);
  void setColor(const Color& textColor);

private:
  enum {
    // grid size
    CharacterWidth = 3,
    CharacterHeight = 5,

    // individual size
    CharacterPartWidth = 10,
    CharacterPartHeight = 10,
  };
  using CharacterData = size_t;
  using CharacterParts = std::vector<CharacterData>;

  // -------------------------------------->      x       y
  using rearrange_modifier = std::function<void(size_t, size_t,
                                                const CharacterData&,
                                                RectangleShape&)>;

  // -------------------------------------------->      x       y
  using const_rearrange_modifier = std::function<void(size_t, size_t,
                                                      const CharacterData&,
                                                      const RectangleShape&)>;
private:
  virtual void syncChildren() override;

private:
  void processCharacterWith(rearrange_modifier modifier);
  void processCharacterWith(const_rearrange_modifier modifier) const;

private:
  char mCharacter;
  std::array<RectangleShape, CharacterWidth * CharacterHeight> mCharacterBody;
  Position mSize;
};



