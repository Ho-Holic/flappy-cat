#ifndef FLAPPY_CAT_VIEW_H
#define FLAPPY_CAT_VIEW_H

// self
#include <core/Transformation.h>
#include <core/Signal.h>

class View : public Transformation {
public:
  View();
  virtual ~View() = default;

public:
  virtual void setOrigin(const Position& origin) override;
  virtual const Position& origin() const override;
  virtual void setPosition(const Position& position) override;
  virtual const Position& position() const override;
  virtual void setScale(const Position& factor) override;
  virtual const Position& scale() const override;
public:
  Position mOrigin;
  Position mSize;
  Position mScale;
};


#endif //FLAPPY_CAT_VIEW_H
