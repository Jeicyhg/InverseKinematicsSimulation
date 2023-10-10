#ifndef ARM_HPP
#define ARM_HPP

#include <vector>
#include "Math.hpp"
#include "Segment.hpp"

/*
 * Arm library
 */
struct Arm
{
    int initial_length;
    int num_segments = 4;
    Vector2f base;
    std::vector<Segment> segments;

    /// @brief initializes an arm with a set unmoving base point and n tentacles
    /// @param x unmovable X of base
    /// @param y unmovable Y of base
    /// @param length length of the lowest segment
    /// @param num_segments total number of segments
    Arm(float x, float y, int length, int num_segments_in = 4)
    {
        initial_length = length;
        num_segments = num_segments_in;
        base = Vector2f(x, y);

        // connected segments with decreasing stroke size
        segments.push_back(Segment(base.x, base.y, 0, initial_length, num_segments));
        for (int i = 1; i < num_segments; i++)
        {
            length-=10;
            segments.push_back(Segment(segments[i - 1], 0, length, num_segments - i));
        }
    }

    /// @brief updates the position of the arm's segments to target the input
    /// @param mouse_x mouse x coordinate to follow
    /// @param mouse_y mouse y coordinate to follow
    void update(float mouse_x, float mouse_y)
    {
        // Get the end segment and make it reach the target
        Segment& end = segments[num_segments - 1];
        end.follow(mouse_x, mouse_y);
        end.calculateB();

        // go from end to the base updating the segments in reverse to put them together
        for (int i = num_segments - 2; i >= 0; i--)
        {
            segments[i].follow_target(segments[i + 1]);
            segments[i].calculateB();
        }

        // reset the base to its origin then reconnect all other segments
        segments[0].SetA(base);
        
        for (int i = 1; i < num_segments; i++)
        {
            segments[i].SetA(segments[i - 1].b);
        }
    }
};
#endif
