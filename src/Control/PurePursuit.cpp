#include "PurePursuit.h"
#include "Controller.h"

#include <cmath>
#include <algorithm>
#include <iostream>


PurePursuit::PurePursuit()
{
    this->look_ahead_distance_base = 0.1;
    this->multiplier = 1;
}

PurePursuit::PurePursuit(float look_ahead_distance_base, float multiplier)
{
    this->look_ahead_distance_base = look_ahead_distance_base;
    this->multiplier = multiplier;
}

float* PurePursuit::calculate_values(std::vector<point> &waypoints, point &position, float &velocity, float &orientation, float &wheelbase)
{
    float* values = new float[2];
    values[0] = this->calculate_velocity(velocity);
    values[1] = this->calculate_steering_angle(waypoints, position, velocity, orientation, wheelbase);
    return values;
}

float PurePursuit::calculate_steering_angle(std::vector<point> &waypoints, point &position, float &velocity, float &orientation, float &wheelbase)
{
    // Steering angle can be calculated as arctan((2*L*sin(alpha)) / la_d) with
    // L: wheelbase
    // la_d: look-ahead-distance
    // alpha: arctan2(y_target_point,x_target_point), arctan2 is needed to keep a sense of direction

    const float pi {3.14159};

    la_point p = calculate_look_ahead_point(waypoints, position, velocity);

    float dx {p.la_x - position.x};
    float dy {p.la_y - position.y};

    // Rotate the point by orientation (degree in radians)
    // The default ingame zero orientation is along the positive x-axis
    // The default zero orientation with atan2() is along the positive x-axis
    // Therefore we can just rotate by orientation radians
    float rotated_x = position.x + dx * cos(orientation) - dy * sin(orientation);
    float rotated_y = position.y + dy * cos(orientation) + dx * sin(orientation);

    dx = {rotated_x - position.x};
    dy = {rotated_y - position.y};
    
    float alpha = atan2(dy, dx);
    float angle = -1 * atan((2 * wheelbase * sin(alpha)) / p.la_d) / (0.5 * pi);
    std::cout<<"angle: "<<angle<<" la_x: "<<p.la_x<<" la_y: "<<p.la_y<<" base: "<<p.base->x<<" "<<p.base->y<<" "
        <<"coord diff: "<<dx<<" "<<dy<<" ";

    // Scale angle with root - not anymore needed
    if (angle < 0)
    {
        //return -1 * sqrt(sqrt(abs(angle)));
        return angle;
    }
    else
    {
        //return sqrt(sqrt(angle));
        return angle;
    }
}

float PurePursuit::calculate_velocity(float &velocity)
{
    if (velocity < 50)
    {
        return 0.5f;
    }
    else
    {
        return 0.1f;
    }
}

la_point PurePursuit::calculate_look_ahead_point(std::vector<point> &waypoints, point &position, float &velocity)
{
    // 1. find point behind oneself and use it as base point
    //      a) Idea: calculate x and y distance between points, span a rectangle and check if point is in this rectangle
    //          Just taking the closest point wont work because points can be spreaded out differently, and also we might run into problems in close corners
    //          Idea for future: take the closest point and only check front and rear point with rectangle, less checks!
    //      b) ToDo: save base point as starting point for future search
    // 2. in the following points, find the one with distance closest to look_ahead_distance, two possibilities:
    //      a) calculate distance from each point to base point
    //      b) accumulate distance from each point -> otherwise corners might get cut

    point* base_point = calculate_base_point(waypoints, position);

    la_point p;

    p.base = base_point;
    
    // Find la_point
    // Idea: follow the waypoints vector in the right! direction after the base point
    //      Starting from the base point, add the distance after each waypoint until the next waypoint would be too far away (look_ahead_distance)
    //      Currently: Take the waypoint one further ahead
    //          Maybe for future: some kind of interpolation
    //      Return this look_ahead_point

    float la_d = calculate_look_ahead_distance(velocity);
    float accumulated_distance {0};
    point* next_point = base_point;
    if (next_point == &(waypoints.back()))
    {
        next_point = &(waypoints.front());
    }
    else
    {
        next_point++;
    }

    // Calculate distance between points and add to accumulated_distance
    do
    {
        accumulated_distance += sqrt(pow(next_point->x - base_point->x, 2) + pow(next_point->y - base_point->y, 2));

        if (base_point == &(waypoints.back()))
        {
            base_point = &(waypoints.front());
        }
        else
        {
            base_point++;
        }
        if (next_point == &(waypoints.back()))
        {
            next_point = &(waypoints.front());
        }
        else
        {
            next_point++;
        }
    }
    while (accumulated_distance < la_d);

    // Get the point before next_point, because next_point is one too far in the distance
    // In the while-loop above, base_point got changed to always be 1 less than next_point, so we can just use that
    /*if (base_point == &(this->waypoints.front()))
    {
        base_point = &(this->waypoints.back());
    }
    else{
        base_point--;
    }*/

    // Calculate the actual distance between la_point and vehicle position to use in PurePursuit algorithm   
    float actual_distance = sqrt(pow(base_point->x - position.x, 2) + pow(base_point->y - position.y, 2));

    p.la_x = base_point->x;
    p.la_y = base_point->y;
    p.la_d=actual_distance;
    return p;
}

point* PurePursuit::calculate_base_point(std::vector<point> &waypoints, point &position)
{
    /* Take the closest point only!
    // Get the base point in waypoints: the first point of two, between which the vechile position is
    for (auto wp = this->waypoints.begin(); wp+1 != this->waypoints.end(); wp++)
    {
        float dx = (wp+1)->x - wp->x;
        float dy = (wp+1)->y - wp->y;

        // Create all 4 rectangle points
        // It is important that points 1+3 and 2+4 are not next to each other
        // Create an array with the points sorted in a way that the first point is the highest
        // If two points have the same y-value, it doesnt matter which one is first
        // ToDo: Adapt the width of the rectangle according to track width (or any other useful width)
        point p1 = {wp->x + dy, wp->y - dx};
        point p2 = {wp->x - dy, wp->y + dx};
        point p3 = {(wp+1)->x - dy, (wp+1)->y + dx};
        point p4 = {(wp+1)->x + dy, (wp+1)->y - dx};

        std::vector<point*> points {&p1, &p2, &p3, &p4};

        // Find highest y value
        point* p_max = *std::max_element(points.begin(), points.end(), [](point* p1, point* p2){return p1->y < p2->y;});

        // Sort vector so the first point is the highest regarding the y-value
        while (p_max != points.front())
        {
            points.push_back(points[0]);
            points.erase(points.begin());
        }

        // Create equations for each vertice of the rectangle
        // The first and last equations are the top ones (upper limit)
        std::vector<linear_equation> vertices;
        for (point** p1 = &points.front(); p1 <= &points.back(); p1++)
        {
            linear_equation vertice;
            point** p2;
            
            if (p1 == &points.back())
            {
                p2 = &points.front();
            }
            else
            {
                p2 = p1 + 1;
            }

            // ToDo: This will fail if the vertice is close to or vertical!!! fix with try block or change the coordinates of some points...
            vertice.slope = ((*p2)->y - (*p1)->y) / ((*p2)->x - (*p1)->x);
            vertice.intercept = (*p1)->y - vertice.slope * (*p1)->x;

            vertices.push_back(vertice);
        }

        // Check if vehicle position is in rectangle
        // Position should be lower than equation 1+4 and higher than equation 2+3
        auto calc_equation = [&](linear_equation& eq) -> float
        {
            return eq.slope * this->position.x + eq.intercept;
        };
        if (this->position.y < calc_equation(vertices[0]) && 
            this->position.y > calc_equation(vertices[1]) &&
            this->position.y > calc_equation(vertices[2]) &&
            this->position.y < calc_equation(vertices[3]))
            {
                base_point = &(*wp);
                break;
            }
    }
    */


    point* base_point;
    base_point = &(waypoints.front());
        float d_base = pow(position.x - base_point->x, 2) + pow(position.y - base_point->y, 2);

        for (point* wp = &(waypoints.front()) + 1; wp <= &(waypoints.back()); wp++)
        {
            if ((pow(position.x - wp->x, 2) + pow(position.y - wp->y, 2)) < d_base)
            {
                base_point = wp;
                d_base = (pow(position.x - wp->x, 2) + pow(position.y - wp->y, 2));
            }
        }
    return base_point;
}

// ToDo: adapt for higher driving speed
float PurePursuit::calculate_look_ahead_distance(float &velocity)
{
    return std::max(this->look_ahead_distance_base * velocity, 5.0f);
}
