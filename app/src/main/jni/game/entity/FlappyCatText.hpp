#pragma once

// game
#include "FlappyCatEntity.hpp"
#include "FlappyCatTextCharacter.hpp"

class FlappyCatText : public FlappyCatEntity {
public:
    FlappyCatText(const FlappyCatGameConstants& gameConstants);

public:
    virtual void drawOn(const Window& window) const override;

public:
    void setText(const std::string& text);
    void setColor(const Color& textColor);

private:
    virtual void syncChildren() override;

private:
    std::string mText;
    std::vector<FlappyCatTextCharacter> mTextBody;
    Color mTextColor;
};
