#include <Car.h>

Car::Car()
{
}

Car::Car(std::vector<Point> waypoints, float wheelbase)
{
    this->waypoints = waypoints;
    this->wheelbase = wheelbase;
}

void Car::update(float velocity, float orientation, Point position)
{
    this->velocity = velocity;
    this->orientation = orientation;
    this->position = position;
}
