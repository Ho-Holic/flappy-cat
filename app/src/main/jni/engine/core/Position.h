#ifndef FLAPPY_CAT_POSITION_H
#define FLAPPY_CAT_POSITION_H

class Position {
public:
  typedef float value_type;
public:
  Position();
  Position(value_type x, value_type y);
public:
  value_type x() const;
  value_type y() const;

private:
  value_type mX;
  value_type mY;

};

inline Position operator+ (const Position& left, const Position& right) {

  return Position(left.x() + right.x(),
                  left.y() + right.y());
}

inline Position operator- (const Position& left, const Position& right) {

  return Position(left.x() - right.x(),
                  left.y() - right.y());
}

inline Position operator* (const Position& left, Position::value_type scalar) {

  return Position(left.x() * scalar, left.y() * scalar);
}

inline Position operator* (Position::value_type scalar, const Position& right) {

  return Position(scalar * right.x(), scalar * right.y());
}

inline Position operator/ (const Position& left, Position::value_type scalar) {

  return Position(left.x() / scalar, left.y() / scalar);
}

inline Position operator/ (Position::value_type scalar, const Position& right) {

  return Position(scalar / right.x(), scalar / right.y());
}

inline Position operator+ (const Position& left, Position::value_type scalar) {

  return Position(left.x() + scalar, left.y() + scalar);
}

inline Position operator+ (Position::value_type scalar, const Position& right) {

  return Position(scalar + right.x(), scalar + right.y());
}

inline Position operator- (const Position& p) {
  return Position(-p.x(), -p.y());
}

// remove functions below, or make good design for this functions

// Normally no multiplication operator for vectors, but this is good for scaling
// other operators must be named e.g. dot_product and so on
inline Position operator* (const Position& left, const Position& right) {

  return Position(left.x() * right.x(),
                  left.y() * right.y());
}

inline Position operator/ (const Position& left, const Position& right) {
  return Position(left.x() / right.x(),
                  left.y() / right.y());
}

#endif //FLAPPY_CAT_POSITION_H
