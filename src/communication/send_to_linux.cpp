#include "Sender.h"
#include "ACSharedMemory.h"
#include "SharedInformation.h"


std::string ip = "172.17.129.240";
std::string port = "5005";

int main()
{
    Sender sender(ip, port);
    ACSharedMemory ac_shared_memory;
    SharedInformation shared_info;
    std::string debug;
    while (true)
    {
        ac_shared_memory.update();

        shared_info.speedKmh = ac_shared_memory.get_physics()->speedKmh;
        shared_info.heading = ac_shared_memory.get_physics()->heading;
        shared_info.steerAngle = ac_shared_memory.get_physics()->steerAngle;
        shared_info.coordinate_x = ac_shared_memory.get_graphics()->carCoordinates[2];
        shared_info.coordinate_y = ac_shared_memory.get_graphics()->carCoordinates[0];

        sender.send(shared_info.to_string());
    }
}
