#ifndef _CAR_HPP_
#define _CAR_HPP_

#include "Point.h"
#include "Controller.h"
#include "Communicator.h"

#include <vector>

class Car
{
    public:
        Car();
        Car(std::vector<point> waypoints, float wheelbase);
        void update(float velocity, float orientation, float steering_angle, point position);
        float* calculate_control(Controller* Con); // Caution: returns a dynamically allocated array
        void communicate_control(Communicator* Com, float* values);

        const float& get_velocity();
        const float& get_orientation();
        const float& get_wheelbase();
        const point& get_position();
        const float& get_steering_angle();
        const std::vector<point>& get_waypoints();

    private:
        float velocity;
        float orientation;
        float wheelbase;
        float steering_angle;
        point position;
        std::vector<point> waypoints;
};

#endif // _CAR_HPP_