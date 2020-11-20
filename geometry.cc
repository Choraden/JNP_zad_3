#include "geometry.h"
#include <iostream>


///< Vector
int Vector::x() const {
    return coor_x;
}

int Vector::y() const {
    return coor_y;
}

Vector Vector::reflection() {
    return Vector(this->coor_y, this->coor_x);
}

bool Vector::operator==(const Vector& v) {
    return this->coor_x == v.coor_x && this->coor_y == v.coor_y;
}

Vector& Vector::operator+=(const Vector& v) {
    this->coor_x += v.coor_x;
    this->coor_y += v.coor_y;
    return *this;
}
///<-----------

///< Position
int Position::x() const {
    return pos_x;
}

int Position::y() const {
    return pos_y;
}

Position Position::reflection() {
    return Position(this->pos_y, this->pos_x);
}

const Position& Position::origin() {
    static const Position origin_pos = Position(0, 0);
    return origin_pos;
}

bool Position::operator==(const Position& p) {
    return this->pos_x == p.pos_x && this->pos_y == p.pos_y;
}

Position& Position::operator+=(const Vector& v) {
    this->pos_x += v.x();
    this->pos_y += v.y();
    return *this;
}
///<-----------



int main() {
    Vector v1(0, 0);
    Position p1(1, 1);
    p1 = v1;
}