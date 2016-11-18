#ifndef FLAPPY_CAT_FLATTRANSFROM_H
#define FLAPPY_CAT_FLATTRANSFROM_H

// self
#include <core/Transformation.h>

class FlatTransformation : public Transformation {
public:
  FlatTransformation(const Position& position);
  FlatTransformation();
public:
  virtual void setPosition(const Position& position) override;
  virtual const Position& getPosition() const override;
private:
  Position mPosition;
};


#endif //FLAPPY_CAT_FLATTRANSFROM_H
