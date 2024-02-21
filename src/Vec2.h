#ifndef VEC2_H
#define VEC2_H
class Vec2
{
public:
    float x;
    float y;
    Vec2() : x(0.0f), y(0.0f) {}
    Vec2(float x, float y) : x(x), y(y) {}

    Vec2 operator+(Vec2 &v)
    {
        return Vec2(x + v.x, y + v.y);
    }

    Vec2 operator*(float s)
    {
        return Vec2(x * s, y * s);
    }

    Vec2 operator*(Vec2 const &v)
    {
        return Vec2(x * v.x, y * v.y);
    }

    Vec2 &operator+=(Vec2 const &v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }
};

#endif