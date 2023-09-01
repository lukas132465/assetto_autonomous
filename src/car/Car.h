#ifndef _CAR_HPP_
#define _CAR_HPP_

#include "Point.h"
#include "Controller.h"
#include "Sender.h"
#include "Reader.h"

#include <vector>


// ToDo: Car needs controller and so on, should not get it in main file -> should go in constructor
class Car
{
    public:
        Car(std::vector<point> waypoints, float wheelbase, std::string sender_ip = "172.17.128.1", std::string sender_port = "5006");
        void update_info();
        float* calculate_control(Controller* Con); // Caution: returns a dynamically allocated array
        void communicate_control(float acceleration, float steering);
        void run_cycle();

        float& get_velocity();
        float& get_orientation();
        float& get_wheelbase();
        point& get_position();
        float& get_steering_angle();
        std::vector<point>& get_waypoints();

    private:
        Reader reader;
        Sender sender;
        float wheelbase;
        std::vector<point> waypoints;
        point position;
        SharedInformation info;
};

#endif // _CAR_HPP_
