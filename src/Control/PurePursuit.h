#ifndef _PURE_PURSUIT_HPP_
#define _PURE_PURSUIT_HPP_

#include "Controller.h"

struct linear_equation
{
    float slope;
    float intercept;
};

struct la_point
{
    float la_x;
    float la_y;
    float la_d;
    point* base;
};

class PurePursuit : public Controller
{
    public:
        PurePursuit();
        PurePursuit(std::vector<std::vector<float>> waypoints, point current_position, float look_ahead_distance_base);
        PurePursuit(std::vector<std::vector<float>> waypoints, point current_position, float look_ahead_distance_base, float multiplier, float wheelbase);
        float calculate_steering_angle();
        la_point calculate_look_ahead_point();
        float calculate_look_ahead_distance();
        void update(point position, float velocity, float orientation);
    protected:
        float look_ahead_distance_base;
        float multiplier;
        float wheelbase;
};

#endif // _PURE_PURSUIT_HPP_
