#include "FlappyCatText.hpp"
#include <core/Log.hpp>

FlappyCatText::FlappyCatText(const FlappyCatGameConstants& gameConstants)
    : FlappyCatStateNode<FlappyCatText>(gameConstants)
    , m_text("")
    , m_textBody()
    , m_textColor()
{
    //
}

void FlappyCatText::setText(const std::string& text)
{
    m_text = text;
    syncChildren();
}

void FlappyCatText::syncChildren()
{
    m_textBody.clear();
    m_textBody.reserve(m_text.size());

    vec2 moveOffset(0.f, 0.f);

    enum {
        Spacing = 10
    };

    for (char character : m_text) {

        m_textBody.emplace_back(gameConstants());

        REQUIRE(TAG, !m_textBody.empty(), "Character must exist!");

        FlappyCatTextCharacter& characterBody = m_textBody.back();
        characterBody.setCharacter(character);
        characterBody.setColor(m_textColor);

        characterBody.moveBy(position() + vec2(moveOffset.x, 0.f));
        moveOffset = moveOffset + characterBody.size() + Spacing;
    }
}

void FlappyCatText::drawOn(const Window& window, const Transformation& transformation) const
{
    for (const FlappyCatTextCharacter& character : m_textBody) {
        character.drawOn(window, transformation);
    }
}

void FlappyCatText::setColor(const Color& textColor)
{
    m_textColor = textColor;

    for (FlappyCatTextCharacter& character : m_textBody) {
        character.setColor(textColor);
    }
}
