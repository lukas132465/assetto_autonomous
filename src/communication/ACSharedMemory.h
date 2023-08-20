#ifndef _ACSharedMemory_HPP_
#define _ACSharedMemory_HPP_

#include "SharedMemory.h"

#include <string>
#include <map>
#include <boost/interprocess/windows_shared_memory.hpp>
#include <windows.h>

struct SMElement
{
    HANDLE handle_map_file;
    unsigned char* map_file_buffer;
};

class ACSharedMemory
{
    public:
        ACSharedMemory();
        void update();
        void update_output_shared_memory(float* values);
        void init_shared_memory_out();

        const SPageFileGraphic* get_graphics();
        const SPageFilePhysics* get_physics();
        const SPageFileStatic* get_static();
    
    private:
        SMElement m_graphics;
        SMElement m_physics;
        SMElement m_static;

        const SPageFilePhysics* file_physics;
        const SPageFileGraphic* file_graphics;
        const SPageFileStatic* file_static;

        boost::interprocess::windows_shared_memory shmem;

        void init_shared_memory_elements();
};

#endif // _ACSharedMemory_HPP_
