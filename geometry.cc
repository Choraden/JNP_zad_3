#include "geometry.h"
#include <iostream>
#include <cassert>

///< Vector
int Vector::x() const {
    return coor_x;
}

int Vector::y() const {
    return coor_y;
}

Vector Vector::reflection() const {
    return {this->coor_y, this->coor_x};
}

bool Vector::operator==(const Vector &v) const {
    return this->coor_x == v.coor_x && this->coor_y == v.coor_y;
}

Vector &Vector::operator+=(const Vector &v) {
    this->coor_x += v.coor_x;
    this->coor_y += v.coor_y;
    return *this;
}

Vector operator+(Vector v1, const Vector &v2) {
    return v1 += v2;
}
///<-----------

///< Position
int Position::x() const {
    return pos_x;
}

int Position::y() const {
    return pos_y;
}

Position Position::reflection() const {
    return {this->pos_y, this->pos_x};
}

const Position &Position::origin() {
    static const Position origin_pos = Position(0, 0);
    return origin_pos;
}

bool Position::operator==(const Position &p) const {
    return this->pos_x == p.pos_x && this->pos_y == p.pos_y;
}

Position &Position::operator+=(const Vector &v) {
    this->pos_x += v.x();
    this->pos_y += v.y();
    return *this;
}

Position operator+(Position p, const Vector &v) {
    return p += v;
}

Position operator+(const Vector &v, Position p) {
    return p += v;
}
///<-----------


///<Rectangle
Rectangle::Rectangle(int width, int height, const Position &pos) : position(pos) {
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
    return {this->h, this->w, this->position.reflection()};
}

int Rectangle::area() const {
    return h * w;
}

bool Rectangle::operator==(const Rectangle &r) const {
    return this->h == r.h && this->w == r.w && this->position == r.position;
}

Rectangle &Rectangle::operator+=(const Vector &v) {
    this->position += v;
    return *this;
}

/*Rectangle& Rectangle::operator=(const Rectangle& r) {
    if(this == &r) {
        return *this;
    }
    this->position = r.position;
    this->w = r.w;
    this->h = r.h;
    return *this;
}

Rectangle& Rectangle::operator=(Rectangle&& r) {
    if(this == &r) {
        return *this;
    }
    this->w = std::move(r.w);
    this->h = std::move(r.h);
    this->position = std::move(r.position);
    return *this;
}*/

///<Rectangles
int Rectangles::size() const {
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
    for (int i = 0; i < r.size(); i++) {
        if (!(recs.at(i) == r.recs.at(i))) {
            return false;
        }
    }
    return true;
}

Rectangles operator+(Rectangles r, const Vector &v) {
    return r += v;
}

Rectangles operator+(const Vector &v, Rectangles r) {
    return r += v;
}

///<-----------

Rectangle merge_horizontally(const Rectangle &r1, const Rectangle &r2) {
    assert(r1.width() == r2.width() && r1.pos().x() == r2.pos().x() &&
           r2.pos().y() + r2.height() == r1.pos().y());
        return {r2.width(), r1.height() + r2.height(), r2.pos()};

}

Rectangle merge_vertically(const Rectangle &r1, const Rectangle &r2) {
    assert(r1.height() == r2.height());
    assert (r1.pos().y() == r2.pos().y());
    assert(r1.pos().x() + r1.width() == r2.pos().x());
    return {r1.width() + r2.width(), r2.height(), r1.pos()};
}

static Rectangle merge_two(const Rectangle &r1, const Rectangle &r2){
    if(r1.width() == r2.width() && r1.pos().x() == r2.pos().x() &&
       r2.pos().y() + r2.height() == r1.pos().y()){
        return merge_horizontally(r1, r2);
    }
    return merge_vertically(r1, r2);
}

static Rectangle merge_all_rec(const Rectangles &r, int end) {
    if (end == 1) {
        return merge_two(r.recs[end-1], r.recs[end]);
    }
    return merge_two(merge_all_rec(r, end - 1), r.recs[end]);
}

Rectangle merge_all(const Rectangles &r) {
    if(r.size() == 1){
        return r.recs[0];
    }
    return merge_all_rec(r, r.size() - 1);
}

int main() {
    /* Vector v1(3, 4);
     Position p1(1, 2);
     Rectangle r1(10,10, p1);
     r1 += v1;
     std::cout << r1.reflection().pos().x() << " " << r1.reflection().pos().y() << "\n";
     Rectangle r2(10,20);
     std::cout << r2.reflection().pos().x() << " " << r2.reflection().pos().y() << "\n";
     p1 = p1 + v1;
     v1 = v1 + v1;
     Position p2 = v1 + p1;
     std::cout << p1.x() << " " << p1.y() << " " << p2.x() << " " << p2.y() << "\n";*/

    Rectangles k{Rectangle(2,2), Rectangle(2,2,Position(2,0)),
               Rectangle(2,2,Position(4,0))};
    Rectangles k2{Rectangle(2,2), Rectangle(2,2,Position(2,0)),
                 Rectangle(4,2,Position(0,-2))};

    Rectangle r = merge_all(k);
    std::cout<<r.width()<<" "<<r.height()<<" "<<r.pos().x()<<" ";

    Rectangle r2 = merge_all(k2);
    std::cout<<r2.width()<<" "<<r2.height();
}

