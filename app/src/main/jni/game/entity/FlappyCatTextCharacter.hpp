#pragma once

#include "entity/FlappyCatStateNode.hpp"
#include <array>
#include <prototype/RectangleShape.hpp>

class FlappyCatTextCharacter : public FlappyCatStateNode<FlappyCatTextCharacter> {
public:
    FlappyCatTextCharacter(const FlappyCatGameConstants& gameConstants);

public:
    void drawOn(const Window& window) const override;
    const Position& size() const override;

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
    void syncChildren() override;

private:
    void processCharacterWith(rearrange_modifier modifier);
    void processCharacterWith(const_rearrange_modifier modifier) const;

private:
    char m_character;
    std::array<RectangleShape, CharacterWidth * CharacterHeight> m_characterBody;
    Position m_size;
};
