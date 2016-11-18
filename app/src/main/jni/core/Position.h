#ifndef FLAPPY_CAT_POSITION_H
#define FLAPPY_CAT_POSITION_H

// self

class Position {
public:
  typedef float position_type;
public:
  Position(position_type x, position_type y);
public:
  position_type x() const;
  position_type y() const;

private:
  position_type mX;
  position_type mY;

};

inline Position operator +(const Position& left, const Position& right) {

  return Position(left.x() + right.x(),
                  left.y() + right.y());
}


#endif //FLAPPY_CAT_POSITION_H
