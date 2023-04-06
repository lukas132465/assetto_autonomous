#include "Car.h"
#include "PurePursuit.h"

#include <iostream>

std::vector<point> waypoints;
point position;
float velocity;
float la_d_base;
la_point result;
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
    
    position.x = 2.00003;
    position.y = 3.99967;
    velocity = 120.0f;
    la_d_base = 0.1f;

    // Closest point in waypoints is 2, 4
    // Look_ahead_distance with given velocity is 0.1*120 = 12
    // Expected la_point is 4.0, 16.0 with a distance of 12.171831367

    PurePursuit Pps(la_d_base, 1);
    result = Pps.calculate_look_ahead_point(waypoints, position, velocity);

    if (abs(result.la_x - 4.0f) < epsilon && abs(result.la_y - 16.0f) < epsilon)
    {
        return 0;
    }

    std::cout<<result.la_x<<" "<<result.la_y<<" "<<result.la_d<<std::endl;

    return 1;
}
