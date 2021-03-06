#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <cassert>

class Vector;

class Position;

class Abstract_point {
protected:
    int pos_x, pos_y;
public:
    Abstract_point(int x, int y);

    explicit Abstract_point(const Vector &);

    explicit Abstract_point(const Position &);

    int x() const;

    int y() const;
};

class Vector : public Abstract_point {
public:
    Vector(int x, int y) : Abstract_point{x, y} {}

    explicit Vector(const Position &p) : Abstract_point{p} {}

    Vector reflection() const;

    bool operator==(const Vector &) const;

    Vector &operator+=(const Vector &);
};

Vector operator+(Vector, const Vector &);

class Position : public Abstract_point {
public:
    Position(int x, int y) : Abstract_point{x, y} {}

    explicit Position(const Vector &v) : Abstract_point{v} {}

    Position reflection() const;

    static const Position &origin();

    bool operator==(const Position &) const;

    Position &operator+=(const Vector &);

};

Position operator+(Position, const Vector &);

Position operator+(const Vector &, Position);

class Rectangle {
    int w, h;
    Position position;
public:
    Rectangle(int width, int height, const Position &pos = Position(0, 0));

    int width() const;

    int height() const;

    Position pos() const;

    Rectangle reflection() const;

    long long area() const;

    bool operator==(const Rectangle &) const;

    Rectangle &operator+=(const Vector &);
};

Rectangle operator+(Rectangle, const Vector &);

Rectangle operator+(const Vector &, Rectangle);


class Rectangles {
    std::vector <Rectangle> recs;
public:
    Rectangles() = default;

    Rectangles(std::initializer_list <Rectangle> r) : recs{r} {}

    Rectangles(const Rectangles &) = default;

    Rectangles(Rectangles &&) noexcept = default;

    size_t size() const;

    Rectangles &operator=(const Rectangles &) = default;

    Rectangles &operator=(Rectangles &&) noexcept = default;

    Rectangles &operator+=(const Vector &);

    bool operator==(const Rectangles &) const;

    Rectangle &operator[](const size_t i);

    const Rectangle &operator[](const size_t i) const;
};

Rectangles operator+(const Rectangles &, const Vector &);

Rectangles operator+(const Vector &, const Rectangles &);

Rectangles operator+(Rectangles &&, const Vector &);

Rectangles operator+(const Vector &, Rectangles &&);

Rectangle merge_horizontally(const Rectangle &r1, const Rectangle &r2);

Rectangle merge_vertically(const Rectangle &r1, const Rectangle &r2);

Rectangle merge_all(const Rectangles &r);

#endif //GEOMETRY_H