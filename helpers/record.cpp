#include "Communicator.h"

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

const std::string file_path {"C:\\Users\\lukas\\Documents\\Projects\\assetto_autonomous\\Records\\test.txt"};

int main()
{
    Communicator Com;
    
    std::ofstream Out_file(file_path);

    while (true)
    {
        Com.update_input_shared_memory();
        Out_file << Com.get_graphics()->carCoordinates[2] << " " << Com.get_graphics()->carCoordinates[0] << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}
