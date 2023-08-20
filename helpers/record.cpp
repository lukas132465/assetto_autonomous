#include "Communicator.h"

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

const std::string file_path {"C:\\Users\\lukas\\Documents\\Projects\\assetto_autonomous\\Records\\test.txt"};

int main()
{
    ACSharedMemory shared_memory;
    
    std::ofstream Out_file(file_path);

    while (true)
    {
        shared_memory.update();
        Out_file << shared_memory.get_graphics()->carCoordinates[2] << " " << shared_memory.get_graphics()->carCoordinates[0] << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}