#include "Car.h"

#include <iostream>


Car::Car(std::vector<point> waypoints, float wheelbase, std::string sender_ip, std::string sender_port)
        : waypoints{waypoints}, wheelbase{wheelbase}, sender{sender_ip, sender_port}
{
    std::thread readerThread(&Reader::read, &reader);
    readerThread.detach();
}

void Car::update_info()
{
    info = reader.get_info();
}

float* Car::calculate_control(Controller* Con)
{
    return Con->calculate_values(waypoints, get_position(), get_velocity(), get_orientation(), get_wheelbase());
}


void Car::communicate_control(float acceleration, float steering)
{
    // Do not directly communicate the steering angle, instead check for the current angle and steer with {-1; 0; 1} as the game doesnt allow "instant" steering and instead slowly changes the steering value itself (probably depending on current speed?)

    if (get_steering_angle() < steering)
    {
        steering = 1.0f;
    }
    else if (get_steering_angle() > steering)
    {
        steering = -1.0f;
    }
    else
    {
        steering = 0.0f;
    }

    std::stringstream builder;
    builder << "{"
            << "\"acceleration\": " << acceleration << ", "
            << "\"steering\": " << steering
            << "}";

    sender.send(builder.str());
}

void Car::run_cycle()
{
    // ToDo: insert Control step
    update_info();
    communicate_control(0.5, 0.7);
}

float& Car::get_velocity()
{
    return info.speedKmh;
}

float& Car::get_orientation()
{
    return info.heading;
}

float& Car::get_wheelbase()
{
    return wheelbase;
}

point& Car::get_position()
{
    position.x = info.coordinate_x;
    position.y = info.coordinate_y;
    return position;
}

float& Car::get_steering_angle()
{
    return info.steerAngle;
}

std::vector<point>& Car::get_waypoints()
{
    return waypoints;
}
