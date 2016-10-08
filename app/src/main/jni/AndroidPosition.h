#ifndef FLAPPY_CAT_ANDROIDPOSITION_H
#define FLAPPY_CAT_ANDROIDPOSITION_H

// self

class AndroidPosition {
public:
  typedef float position_type;
public:
  AndroidPosition(position_type x, position_type y);
public:
  position_type x() const;
  position_type y() const;

private:
  position_type mX;
  position_type mY;

};


#endif //FLAPPY_CAT_ANDROIDPOSITION_H
