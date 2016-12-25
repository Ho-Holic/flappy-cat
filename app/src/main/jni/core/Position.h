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

inline Position operator+ (const Position& left, const Position& right) {

  return Position(left.x() + right.x(),
                  left.y() + right.y());
}

inline Position operator- (const Position& left, const Position& right) {

  return Position(left.x() - right.x(),
                  left.y() - right.y());
}

inline Position operator* (const Position& left, Position::position_type scalar) {

  return Position(left.x() * scalar, left.y() * scalar);
}

inline Position operator* (Position::position_type scalar, const Position& right) {

  return Position(scalar * right.x(), scalar * right.y());
}


#endif //FLAPPY_CAT_POSITION_H
