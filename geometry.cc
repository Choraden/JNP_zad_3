#include "geometry.h"
#include <iostream>
#include <cassert>


///< Abstract_point
Abstract_point::Abstract_point(int x, int y) : pos_x{x}, pos_y{y} {}

Abstract_point::Abstract_point(const Vector &v) : pos_x{v.x()}, pos_y{v.y()} {}

Abstract_point::Abstract_point(const Position &p) : pos_x{p.x()}, pos_y{p.y()} {}

int Abstract_point::x() const {
    return pos_x;
}

int Abstract_point::y() const {
    return pos_y;
}


///< Vector
Vector Vector::reflection() const {
    return {pos_y, pos_x};
}

bool Vector::operator==(const Vector &v) const {
    return pos_x == v.pos_x && pos_y == v.pos_y;
}

Vector &Vector::operator+=(const Vector &v) {
    pos_x += v.pos_x;
    pos_y += v.pos_y;
    return *this;
}

Vector operator+(Vector v1, const Vector &v2) {
    return v1 += v2;
}


///< Position
Position Position::reflection() const {
    return {pos_y, pos_x};
}

const Position &Position::origin() {
    static const Position origin_pos = Position(0, 0);
    return origin_pos;
}

bool Position::operator==(const Position &p) const {
    return pos_x == p.pos_x && pos_y == p.pos_y;
}

Position &Position::operator+=(const Vector &v) {
    pos_x += v.x();
    pos_y += v.y();
    return *this;
}

Position operator+(Position p, const Vector &v) {
    return p += v;
}

Position operator+(const Vector &v, Position p) {
    return p += v;
}


///<Rectangle
Rectangle::Rectangle(int width, int height, const Position &pos) : position{pos} {
    assert(height > 0 && width > 0);
    w = width;
    h = height;
}

int Rectangle::width() const {
    return w;
}

int Rectangle::height() const {
    return h;
}

Position Rectangle::pos() const {
    return position;
}

Rectangle Rectangle::reflection() const {
    return {h, w, position.reflection()};
}

long long Rectangle::area() const {
    return h * w;
}

bool Rectangle::operator==(const Rectangle &r) const {
    return h == r.h && w == r.w && position == r.position;
}

Rectangle &Rectangle::operator+=(const Vector &v) {
    position += v;
    return *this;
}

Rectangle operator+(Rectangle p, const Vector &v) {
    return p += v;
}

Rectangle operator+(const Vector &v, Rectangle p) {
    return p += v;
}


///<Rectangles
size_t Rectangles::size() const {
    if (!recs.empty()) {
        return recs.size();
    }
    return 0;
}

Rectangles &Rectangles::operator+=(const Vector &v) {
    for (auto &rec : recs) {
        rec += v;
    }
    return *this;
}

bool Rectangles::operator==(const Rectangles &r) const {
    if (recs.size() != r.size()) {
        return false;
    }
    for (size_t i = 0; i < r.size(); i++) {
        if (!(recs.at(i) == r.recs.at(i))) {
            return false;
        }
    }
    return true;
}

Rectangles operator+(const Rectangles &r, const Vector &v) {
    Rectangles result(r);
    result += v;
    return result;
}

Rectangles operator+(const Vector &v, const Rectangles &r) {
    return r + v;
}

Rectangles operator+(Rectangles &&r, const Vector &v) {
    Rectangles result(std::move(r));
    result += v;
    return result;
}

Rectangles operator+(const Vector &v, Rectangles &&r) {
    return std::move(r) + v;
}

Rectangle &Rectangles::operator[](const size_t i) {
    assert(i < recs.size());
    return recs[i];
}

const Rectangle &Rectangles::operator[](const size_t i) const {
    assert(i < recs.size());
    return recs[i];
}


///<merge
Rectangle merge_horizontally(const Rectangle &r1, const Rectangle &r2) {
    assert(r1.width() == r2.width() && r1.pos().x() == r2.pos().x() &&
           r1.pos().y() + r1.height() == r2.pos().y());
    return {r2.width(), r1.height() + r2.height(), r1.pos()};
}

Rectangle merge_vertically(const Rectangle &r1, const Rectangle &r2) {
    assert(r1.height() == r2.height() && r1.pos().y() == r2.pos().y() &&
           r1.pos().x() + r1.width() == r2.pos().x());
    return {r1.width() + r2.width(), r2.height(), r1.pos()};
}

static Rectangle merge_two(const Rectangle &r1, const Rectangle &r2) {
    if (r1.width() == r2.width() && r1.pos().x() == r2.pos().x() &&
        r1.pos().y() + r1.height() == r2.pos().y()) {
        return merge_horizontally(r1, r2);
    }
    return merge_vertically(r1, r2);
}

static Rectangle merge_all_rec(const Rectangles &r, int end) {
    if (end == 1) {
        return merge_two(r[end - 1], r[end]);
    }
    return merge_two(merge_all_rec(r, end - 1), r[end]);
}

Rectangle merge_all(const Rectangles &r) {
    assert(r.size() > 0);
    if (r.size() == 1) {
        return r[0];
    }
    return merge_all_rec(r, r.size() - 1);
}