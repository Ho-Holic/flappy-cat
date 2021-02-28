#pragma once

#include "FlappyCatTextCharacter.hpp"
#include "entity/FlappyCatStateNode.hpp"

class FlappyCatText : public FlappyCatStateNode<FlappyCatText> {
public:
    FlappyCatText(const FlappyCatGameConstants& gameConstants);

public:
    void drawOn(const Window& window) const override;

public:
    void setText(const std::string& text);
    void setColor(const Color& textColor);

private:
    void syncChildren() override;

private:
    std::string m_text;
    std::vector<FlappyCatTextCharacter> m_textBody;
    Color m_textColor;
};
