#ifndef _CAR_HPP_
#define _CAR_HPP_

#include "Point.h"

#include <vector>

class Car
{
    public:
        Car();
        Car(std::vector<Point> waypoints, float wheelbase);
        void update(float velocity, float orientation, Point position);
    private:
        float velocity;
        float orientation;
        float wheelbase;
        Point position;
        std::vector<Point> waypoints;
};

#endif // _CAR_HPP_