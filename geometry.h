#ifndef GEOMETRY_H
#define GEOMETRY_H

class Vector {
    int coor_x, coor_y;
public:
    Vector(int x, int y) : coor_x(x), coor_y(y) {}
    int x() const;
    int y() const;
    Vector reflection();
    bool operator==(const Vector&);
    Vector& operator+=(const Vector&);
};

class Position {
    int pos_x, pos_y;
public:
    Position(int x, int y) : pos_x(x), pos_y(y) {}
    int x() const;
    int y() const;
    Position reflection();
    static const Position& origin();
    bool operator==(const Position&);
    Position& operator+=(const  Vector&);
};

#endif //GEOMETRY_H
