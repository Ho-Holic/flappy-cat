#ifndef FLAPPY_CAT_VIEW_H
#define FLAPPY_CAT_VIEW_H

// self
#include <core/Transformation.h>

class View : public Transformation {
public:
  View();
  virtual ~View() = default;

public:
  virtual void setOrigin(const Position& origin);
  virtual const Position& origin() const;
  virtual void setPosition(const Position& position);
  virtual const Position& getPosition() const;
public:
  Position mOrigin;
  Position mSize;
};


#endif //FLAPPY_CAT_VIEW_H
