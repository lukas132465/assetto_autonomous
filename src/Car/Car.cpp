#include <Car.h>

Car::Car()
{
}

Car::Car(std::vector<point> waypoints, float wheelbase)
{
    this->velocity = 0.0;
    this->orientation = 0.0;
    this->position = {0.0, 0.0};

    this->waypoints = waypoints;
    this->wheelbase = wheelbase;
}

void Car::update(float velocity, float orientation, point position)
{
    this->velocity = velocity;
    this->orientation = orientation;
    this->position = position;
}

const float& Car::get_velocity()
{
    return this->velocity;
}

const float& Car::get_orientation()
{
    return this->orientation;
}
const float& Car::get_wheelbase()
{
    return this->wheelbase; 
}

const point& Car::get_position()
{
    return this->position; 
}

const std::vector<point>& Car::get_waypoints()
{
    return this->waypoints;
}
