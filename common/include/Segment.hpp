#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include <cmath> // for sqrt
#include <cassert>
#include "Math.hpp"
using namespace std;

/*
 * Segment library
 */
struct Segment
{
    int stroke;
    float angle, length;
    Vector2f a, b;

    /// Initializes a new segment with a specified starting coordinates
    Segment(float x, float y, float initial_angle, float segment_length, int segment_stroke)
    {
        a = Vector2f(x, y);
        angle = initial_angle;
        length = segment_length;
        stroke = segment_stroke;
        calculateB();
    }

    /// Initializes a vector a->b with a having the same coordinates as
    /// the parent's b so we can have continuity in the segments
    Segment(Segment parent, float initial_angle, float segment_length, int segment_stroke)
    {
        a = Vector2f(parent.b.x, parent.b.x);
        angle = initial_angle;
        length = segment_length;
        stroke = segment_stroke;
        calculateB();
    }

    /// @brief Makes the segment follow and try to reach the target
    /// @param tx target's x coordinate
    /// @param ty target's y coordinate
    void follow(float tx, float ty)
    {
        // define the target and direction we're heading in
        float dir_x = tx - a.x;
        float dir_y = ty - a.y;
        Vector2f dir = Vector2f(dir_x, dir_y);

        // Calculate the angle of the segment based on the direction
        angle = atan2(dir_y, dir_x);
        
        float currentMag = dir.Magnitude();
        // adjust the x and y coordinates proportionally to the length
        if (currentMag != 0){
            float scale = length / currentMag;
            dir_x *= scale;
            dir_y *= scale;
        }

        // update a's coordinates according to the new direction from the target
        a = Vector2f(tx - dir_x, ty - dir_y);
    }

    /// @brief Calls the follow function with provided segment's a coordinates
    /// @param target segment our b is connected to, we'll need to follow its a
    void follow_target(Segment target)
    {
        float tx = target.a.x;
        float ty = target.a.y;
        follow(tx, ty);
    }

    /// @brief Reset the segment's a position to make sure the base is stationary
    /// when trying to reach a target
    /// @param pos mandatory position of a
    void SetA(Vector2f pos)
    {
        a = Vector2f(pos.x, pos.y);
        calculateB();
    }

    /// @brief calculates the coordinates of B based on a, angle, and length
    void calculateB()
    {   
        float dx = length * cos(angle);
        float dy = length * sin(angle);
        b = Vector2f(a.x + dx, a.y + dy);
    }
};

#endif
