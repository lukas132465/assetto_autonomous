#include "Controller.h"

Controller::Controller()
{
}

Controller::Controller(std::vector<std::vector<float>> waypoints, point current_position)
{
    std::vector<point> result;
    
    for (auto& vec: waypoints)
    {
        point p;
        p.x = vec[0];
        p.y = vec[1];
        result.push_back(p);
    }

    this->waypoints = result;
    this->position = current_position;
    this->orientation = -0.25 * 3.14159;
    this->velocity = 50;
}
