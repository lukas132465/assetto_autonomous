#include "Car.h"

#include <iostream>

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

void Car::update(float velocity, float orientation, float steering_angle, point position)
{
    this->velocity = velocity;
    this->orientation = orientation;
    this->steering_angle = steering_angle;
    this->position = position;
}

float* Car::calculate_control(Controller* Con)
{
    return Con->calculate_values(this->waypoints, this->position, this->velocity, this->orientation, this->wheelbase);
}

void Car::communicate_control(Communicator* Com, float* values)
{
    // Do not directly communicate the steering angle, instead check for the current angle and steer with {-1; 0; 1} as the game doesnt allow "instant" steering and changes the steering value (probably depending on current speed?)
    
    if (this->steering_angle < values[1])
    {
        values[1] = 1.0f;
    }
    else if (this->steering_angle > values[1])
    {
        values[1] = -1.0f;
    }
    else
    {
        values[1] = 0.0f;
    }
    Com->update_output_shared_memory(values);
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

const float& Car::get_steering_angle()
{
    return this->steering_angle; 
}

const std::vector<point>& Car::get_waypoints()
{
    return this->waypoints;
}
