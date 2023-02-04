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
        PurePursuit(float look_ahead_distance_base, float multiplier);
        float* calculate_values(std::vector<point> &waypoints, point &position, float &velocity, float &orientation, float &wheelbase);
        float calculate_steering_angle(std::vector<point> &waypoints, point &position, float &velocity, float &orientation, float &wheelbase);
        float calculate_velocity(float &velocity);
        la_point calculate_look_ahead_point(std::vector<point> &waypoints, point &position, float &velocity);
        float calculate_look_ahead_distance(float &velocity);
        point* calculate_base_point(std::vector<point> &waypoints, point &position);
    protected:
        float look_ahead_distance_base;
        float multiplier;
};

#endif // _PURE_PURSUIT_HPP_
