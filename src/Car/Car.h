#ifndef _CAR_HPP_
#define _CAR_HPP_

#include "Point.h"

#include <vector>

class Car
{
    public:
        Car();
        Car(std::vector<point> waypoints, float wheelbase);
        void update(float velocity, float orientation, point position);

        const float& get_velocity();
        const float& get_orientation();
        const float& get_wheelbase();
        const point& get_position();
        const std::vector<point>& get_waypoints();

    private:
        float velocity;
        float orientation;
        float wheelbase;
        point position;
        std::vector<point> waypoints;
};

#endif // _CAR_HPP_