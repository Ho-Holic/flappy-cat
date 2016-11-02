#ifndef FLAPPY_CAT_FLATTRANSFROM_H
#define FLAPPY_CAT_FLATTRANSFROM_H

// self
#include <core/Transform.h>

class FlatTransform : public Transform {
public:
  FlatTransform(const Position& position);
public:
  virtual void setPosition(const Position& position) override;
  virtual const Position& getPosition() const override;
private:
  Position mPosition;
};


#endif //FLAPPY_CAT_FLATTRANSFROM_H
