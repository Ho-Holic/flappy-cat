// self
#include "FlappyCatTextCharacter.hpp"

// stl
#include <map>

// engine
#include <core/Log.hpp>

namespace {
/**
   * TODO: consider to implement visitor font
   *
   * https://www.myfonts.com/fonts/cheapprofonts/visitor-brk-ten-pro/
   *
   */
static std::map<char, std::vector<size_t>> g_characterTable = {
    { '0',
        {
            1,
            1,
            1,
            1,
            0,
            1,
            1,
            0,
            1,
            1,
            0,
            1,
            1,
            1,
            1,
        } },
    { '1',
        {
            0,
            1,
            1,
            0,
            0,
            1,
            0,
            0,
            1,
            0,
            0,
            1,
            0,
            0,
            1,
        } },
    { '2',
        {
            1,
            1,
            1,
            0,
            0,
            1,
            1,
            1,
            1,
            1,
            0,
            0,
            1,
            1,
            1,
        } },
    { '3',
        {
            1,
            1,
            1,
            0,
            0,
            1,
            0,
            1,
            1,
            0,
            0,
            1,
            1,
            1,
            1,
        } },
    { '4',
        {
            1,
            0,
            1,
            1,
            0,
            1,
            1,
            1,
            1,
            0,
            0,
            1,
            0,
            0,
            1,
        } },
    { '5',
        {
            1,
            1,
            1,
            1,
            0,
            0,
            1,
            1,
            1,
            0,
            0,
            1,
            1,
            1,
            1,
        } },
    { '6',
        {
            1,
            1,
            1,
            1,
            0,
            0,
            1,
            1,
            1,
            1,
            0,
            1,
            1,
            1,
            1,
        } },
    { '7',
        {
            1,
            1,
            1,
            0,
            0,
            1,
            0,
            0,
            1,
            0,
            0,
            1,
            0,
            0,
            1,
        } },
    { '8',
        {
            1,
            1,
            1,
            1,
            0,
            1,
            1,
            1,
            1,
            1,
            0,
            1,
            1,
            1,
            1,
        } },
    { '9',
        {
            1,
            1,
            1,
            1,
            0,
            1,
            1,
            1,
            1,
            0,
            0,
            1,
            0,
            0,
            1,
        } },
};
}

FlappyCatTextCharacter::FlappyCatTextCharacter(const FlappyCatGameConstants& gameConstants)
    : FlappyCatEntity(gameConstants)
    , mCharacter('\0')
    , mCharacterBody()
    , mSize(CharacterPartWidth * CharacterWidth,
          CharacterPartHeight * CharacterHeight)
{
    //
}

void FlappyCatTextCharacter::processCharacterWith(rearrange_modifier modifier)
{

    auto found = g_characterTable.find(mCharacter);

    REQUIRE(TAG, found != g_characterTable.end(), "Try to rearrange to non existing character");

    const CharacterParts& characterParts = (*found).second;

    for (size_t y = 0; y < CharacterHeight; ++y) {
        for (size_t x = 0; x < CharacterWidth; ++x) {

            size_t accessIndex = y * CharacterWidth + x;

            modifier(x, y, characterParts[accessIndex], mCharacterBody[accessIndex]);
        }
    }
}

void FlappyCatTextCharacter::processCharacterWith(const_rearrange_modifier modifier) const
{

    auto found = g_characterTable.find(mCharacter);

    REQUIRE(TAG, found != g_characterTable.end(), "Try to rearrange to non existing character");

    const CharacterParts& characterParts = (*found).second;

    for (size_t y = 0; y < CharacterHeight; ++y) {
        for (size_t x = 0; x < CharacterWidth; ++x) {

            size_t accessIndex = y * CharacterWidth + x;

            modifier(x, y, characterParts[accessIndex], mCharacterBody[accessIndex]);
        }
    }
}

void FlappyCatTextCharacter::setCharacter(char character)
{

    mCharacter = character;
    syncChildren();
}

void FlappyCatTextCharacter::syncChildren()
{

    processCharacterWith([this](size_t x, size_t y,
                             const CharacterData&,
                             RectangleShape& body) {
        body.transformation().setPosition(position() + Position((x * CharacterPartWidth), -static_cast<float>(y * CharacterPartHeight)));

        body.geometry().resize(Position(CharacterPartWidth, CharacterPartHeight));
    });
}

void FlappyCatTextCharacter::drawOn(const Window& window) const
{

    processCharacterWith([this, &window](size_t, size_t,
                             const CharacterData& characterData,
                             const RectangleShape& body) {
        if (characterData > 0) {
            window.draw(body);
        }
    });
}

const Position& FlappyCatTextCharacter::size() const
{

    return mSize;
}

void FlappyCatTextCharacter::setColor(const Color& textColor)
{

    for (RectangleShape& body : mCharacterBody) {
        body.setColor(textColor);
    }
}
