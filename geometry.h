#ifndef GEOMETRY_H
#define GEOMETRY_H

class Vector {
    int coor_x, coor_y;
public:
    Vector(int x, int y) : coor_x(x), coor_y(y) {}
    int x() const;
    int y() const;
    Vector reflection() const;
    bool operator==(const Vector&) const;
    Vector& operator+=(const Vector&);
};

class Position {
    int pos_x, pos_y;
public:
    Position(int x, int y) : pos_x(x), pos_y(y) {}
    int x() const;
    int y() const;
    Position reflection() const;
    static const Position& origin();
    bool operator==(const Position&) const;
    Position& operator+=(const  Vector&);
};

class Rectangle {
    int w, h;
    Position position;
public:
    Rectangle(int width, int height, const Position& pos = Position(0,0));
    Rectangle(const Rectangle& r) : w(r.w), h(r.h),position(r.position){}
    Rectangle(Rectangle&& r) : w(r.w), h(r.h),position(r.position){}
    int width() const;
    int height() const;
    Position pos() const;
    Rectangle reflection() const;
    int area() const;
    bool operator==(const Rectangle&) const;
    Rectangle& operator+=(const Vector&);
    Rectangle& operator=(const Rectangle&);
    Rectangle& operator=(Rectangle&&);


};

Rectangle merge_horizontally(Rectangle r1, Rectangle r2);
Rectangle merge_vertically(Rectangle r1, Rectangle r2);

#endif //GEOMETRY_H
