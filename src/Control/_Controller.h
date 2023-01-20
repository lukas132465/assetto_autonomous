#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

#include <vector>

struct point
{
    float x;
    float y;
};

class Controller
{
    public:
        Controller();
        Controller(std::vector<std::vector<float>> waypoints, point current_position);
    //protected:
        std::vector<point> waypoints;
        point position;
        float velocity;
        float orientation;
};

#endif // _CONTROLLER_HPP_