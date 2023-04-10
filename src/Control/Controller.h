#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

#include "Point.h"

#include <vector>


class Controller
{
    public:
        virtual float* calculate_values(std::vector<point> &waypoints, point &position, float &velocity, float &orientation, float &wheelbase) = 0;
};

#endif // _CONTROLLER_HPP_