#include "Communicator.h"
#include "Car.h"

#include <iostream>

const float WHEELBASE {3.0};

float velocity;
float orientation;
point position;

int main()
{
    Communicator com;
    Car car;

    while (true)
    {
        com.update_input_shared_memory();

        float velocity = com.get_physics()->speedKmh;
        float orientation = com.get_physics()->heading;
        position.x = com.get_graphics()->carCoordinates[0];
        position.y = com.get_graphics()->carCoordinates[2];

        car.update(velocity, orientation, position);

        std::cout<<"velocity: "<<car.get_velocity()<<" orientation: "<<car.get_orientation()<<" pos_x: "<<car.get_position().x<<" pos_y: "<<car.get_position().y<<std::endl;
    }

    return 0;
}