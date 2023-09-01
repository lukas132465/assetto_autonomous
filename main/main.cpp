#include "Car.h"
#include "PurePursuit.h"

#include <iostream>
#include <fstream>

const float wheelbase {2.456}; // According to https://www.stuttcars.com/porsche-911-gt3-cup-991-2-2016-2020-specifications-performance/

float velocity;
float orientation;
point position;

std::vector<point> waypoints;

const std::string in_file_path {"C:\\Users\\lukas\\Documents\\Projects\\assetto_autonomous\\Records\\monza.txt"};

std::vector<point> read_file();

int main()
{
    waypoints = read_file();
    Car Car(waypoints, wheelbase);
    PurePursuit Con;

    while (true)
    {
        Car.run_cycle();

        std::cout << "steering angle: " << Car.get_steering_angle() << " velocity: " << Car.get_velocity() << " orientation: " << Car.get_orientation() << " pos_x: " << Car.get_position().x << " pos_y: " << Car.get_position().y << std::endl;
    }

    return 0;
}

// ToDo: put this in a separate file
std::vector<point> read_file()
{
    std::vector<point> result;
    std::ifstream In_file(in_file_path);
    std::string line;
    std::string temp;
    point p;
    size_t pos;
    while (getline(In_file, line))
    {
        pos = line.find(" ");
        temp = line.substr(0, pos);
        line.erase(0, pos+1);
        p.x = stof(temp);
        p.y = stof(line);
        result.push_back(p);
    }
    return result;
}
