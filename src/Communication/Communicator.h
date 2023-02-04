#ifndef _WINDOWS_COMMUNICATOR_HPP_
#define _WINDOWS_COMMUNICATOR_HPP_

#include "SharedMemory.h"

#include <string>
#include <map>
#include <windows.h>
#include <boost/interprocess/windows_shared_memory.hpp>

struct SMElement
{
    HANDLE hMapFile;
    unsigned char* mapFileBuffer;
};

class Communicator
{
    public:
        Communicator();
        void update_input_shared_memory();
        void update_output_shared_memory(float* values);
        void init_shared_memory_out();

        const SPageFileGraphic*& get_graphics();
        const SPageFilePhysics*& get_physics();
        const SPageFileStatic*& get_static();
    
    private:
        SMElement m_graphics;
        SMElement m_physics;
        SMElement m_static;

        const SPageFilePhysics* file_physics;
        const SPageFileGraphic* file_graphics;
        const SPageFileStatic* file_static;

        boost::interprocess::windows_shared_memory shmem;

        void init_smelements();
};

#endif // _WINDOWS_COMMUNICATOR_HPP_