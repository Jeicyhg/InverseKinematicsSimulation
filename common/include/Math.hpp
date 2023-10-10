/// CREDIT: this struct code was provided by Professor Michael Shah https://github.com/MikeShah
/// during the CS 5350 Applied Geometric Representation and Computation course.
#ifndef MATH_HPP

#define MATH_HPP

#include <cmath> // for sqrt
#include <cassert>

/*
 * Provided math library
 */
struct Vector2f
{
    float x, y;

    /// Default constructor
    /// Initializes vector values to 0.0f by default.
    Vector2f()
    {
        x = 0.0f;
        y = 0.0f;
    }

    /// Two argument constructor
    Vector2f(float _x, float _y) : x(_x), y(_y)
    {
    }

    /// Copy Constructor
    /// Not truly needed, but in general I like to implement
    /// so I can debug when copies are made
    /// i.e. Add a 'print message' (or better yet -- see in the debugger)
    ///      when this is being called.
    Vector2f(const Vector2f &rhs)
    {
        x = rhs.x;
        y = rhs.y;
    }

    /// Copy assignment operator
    Vector2f &operator=(const Vector2f &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        x = rhs.x;
        y = rhs.y;
        return *this;
    }

    /// Urnary Negation operator flips sign of vector.
    /// This produces a new vector.
    Vector2f operator-() const
    {
        return Vector2f(-x, -y);
    }

    // Subtraction
    Vector2f operator-(const Vector2f &rhs) const
    {
        return Vector2f(x - rhs.x, y - rhs.y);
    }

    // Addition
    Vector2f operator+(const Vector2f &rhs) const
    {
        return Vector2f(x + rhs.x, y + rhs.y);
    }

    // Subtract a vector from this one
    Vector2f &operator-=(const Vector2f &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    // Normalize
    Vector2f &Normalize()
    {
        float len = Magnitude();
        
        assert(len != 0.0f && "We actually found a float that is 0 (or maybe close), uh oh!");
        x = x / len;
        y = y / len;

        // Return a reference so we can chain together calls
        return *this;
    }

    // Magnitude or "Length"
    float Magnitude()
    {
        return sqrt(x * x + y * y);
    }
};

/// Produce a new normalized vector
/// NOTE: Since this produces a new vector,
///       the naming is 'NormalizedRetrieve'.
Vector2f NormalizedRetrieve(Vector2f in)
{
    float len = in.Magnitude();
    in.x = in.x / len;
    in.y = in.y / len;

    return Vector2f(in.x, in.y);
}

/// Dot product of two Vector2's
float Dot(const Vector2f &a, const Vector2f &b)
{
    return (a.x * b.x) + (a.y * b.y);
}

/// 2D cross product (wedge product/bivector)
/// If you are in a left-handed or right-handed
/// the resulting 'float' (being positive or negative) changes!
float Cross(const Vector2f &a, const Vector2f &b)
{
    float result = (a.x * b.y) - (a.y * b.x);
    return result;
}

/// Create a new midpoint from two vectors
Vector2f CreateMidpoint(const Vector2f &a, const Vector2f &b)
{
    return Vector2f((a.x + b.x) / 2, (a.y + b.y) / 2);
}

/// Compute if a point 'p2' is to the left of the segment
/// formed by a and b
int isLeft(const Vector2f &a, const Vector2f &b, const Vector2f &P2)
{
    return ((b.x - a.x) * (P2.y - a.y) - (P2.x - a.x) * (b.y - a.y));
}

/// Point in Triangle another strategy
bool PointInTriangle2(const Vector2f &v, const Vector2f &a, const Vector2f &b, const Vector2f &c)
{
    int first = isLeft(a, b, v);
    int second = isLeft(b, c, v);
    int third = isLeft(c, a, v);

    return (first > 0 && second > 0 && third > 0);
}

/// Point in Triangle
bool PointInTriangle(const Vector2f &v, const Vector2f &a, const Vector2f &b, const Vector2f &c)
{

    return true;
}

#endif
