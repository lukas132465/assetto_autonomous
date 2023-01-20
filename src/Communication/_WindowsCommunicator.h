#ifndef _WINDOWS_COMMUNICATOR_HPP_
#define _WINDOWS_COMMUNICATOR_HPP_

#include "SharedMemory.h"

#include <string>
#include <map>
#include <windows.h>

class WindowsCommunicator
{
    public:
        WindowsCommunicator(std::string_view windows_to_linux_file, std::string_view linux_to_windows_file);
        void write_data();
        std::map<std::string, double> read_data();
    
    private:
        std::string windows_to_linux_file;
        std::string linux_to_windows_file;

        struct SMElement
        {
            HANDLE hMapFile;
            unsigned char* mapFileBuffer;
        };

        SMElement m_graphics;
        SMElement m_physics;
        SMElement m_static;

        void init_smelements();
};

#endif // _WINDOWS_COMMUNICATOR_HPP_