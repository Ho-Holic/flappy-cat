#ifndef FLAPPY_CAT_FLAPPYCATTEXT_H
#define FLAPPY_CAT_FLAPPYCATTEXT_H

// game
#include "FlappyCatEntity.h"
#include "FlappyCatTextCharacter.h"

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


#endif //FLAPPY_CAT_FLAPPYCATTEXT_H
