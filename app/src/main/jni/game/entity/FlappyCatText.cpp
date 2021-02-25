#include "FlappyCatText.hpp"
#include <core/Log.hpp>

FlappyCatText::FlappyCatText(const FlappyCatGameConstants& gameConstants)
    : FlappyCatStateNode<FlappyCatText>(gameConstants)
    , mText("")
    , mTextBody()
    , mTextColor()
{
    //
}

void FlappyCatText::setText(const std::string& text)
{
    mText = text;
    syncChildren();
}

void FlappyCatText::syncChildren()
{
    mTextBody.clear();
    mTextBody.reserve(mText.size());

    Position moveOffset(0.f, 0.f);

    enum {
        Spacing = 10
    };

    for (char character : mText) {

        mTextBody.emplace_back(gameConstants());

        REQUIRE(TAG, !mTextBody.empty(), "Character must exist!");

        FlappyCatTextCharacter& characterBody = mTextBody.back();
        characterBody.setCharacter(character);
        characterBody.setColor(mTextColor);

        characterBody.moveBy(position() + Position(moveOffset.x(), 0.f));
        moveOffset = moveOffset + characterBody.size() + Spacing;
    }
}

void FlappyCatText::drawOn(const Window& window) const
{
    for (const FlappyCatTextCharacter& character : mTextBody) {
        character.drawOn(window);
    }
}

void FlappyCatText::setColor(const Color& textColor)
{
    mTextColor = textColor;

    for (FlappyCatTextCharacter& character : mTextBody) {
        character.setColor(textColor);
    }
}
