#include "Car.h"
#include "PurePursuit.h"

#include <iostream>

std::vector<point> waypoints;
point position;
float velocity;
float la_d_base;
point result;
const float epsilon {0.0001};

int main()
{
    // Initialize waypoints
    for (float i = 1.0f; i < 100; i+= 0.1)
    {
        point* temp = new point;
        temp->x = i;
        temp->y = i*i;
        waypoints.push_back(*temp);
    }
    
    position.x = 2.10003;
    position.y = 3.89967;
    velocity = 120.0f;
    la_d_base = 0.1f;

    // Expected closest point in waypoints is 2, 4

    PurePursuit Pps(la_d_base, 1);
    result = *Pps.calculate_base_point(waypoints, position);

    if (abs(result.x - 2.0f) < epsilon && abs(result.y - 4.0f) < epsilon)
    {
        return 0;
    }

    std::cout<<result.x<<" "<<result.y<<std::endl;
    std::cout<<"diff: "<<result.x-2.0f<<" "<<result.y-4.0f<<std::endl;

    return 1;
}
