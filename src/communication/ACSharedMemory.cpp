#include "ACSharedMemory.h"

#include <tchar.h>
#include <iostream>
#include <fstream>
#include <boost/interprocess/mapped_region.hpp>


const char sm_out_name[] = "sm_control";

ACSharedMemory::ACSharedMemory()
{
    this->init_shared_memory_elements();
    this->init_shared_memory_out();
}

void ACSharedMemory::update()
{
    this->file_physics = (SPageFilePhysics*)this->m_physics.map_file_buffer;
    this->file_graphics = (SPageFileGraphic*)this->m_graphics.map_file_buffer;
    this->file_static = (SPageFileStatic*)this->m_static.map_file_buffer;
}

void ACSharedMemory::init_shared_memory_out()
{
    this->shmem = boost::interprocess::windows_shared_memory(boost::interprocess::create_only, sm_out_name, boost::interprocess::read_write, 2);
}

void ACSharedMemory::update_output_shared_memory(float* values)
{
    boost::interprocess::mapped_region region(this->shmem, boost::interprocess::read_write);

    std::memcpy(region.get_address(), values, 2*sizeof(float));
}

void ACSharedMemory::init_shared_memory_elements()
{
    auto init_element = [this](auto& element, LPCSTR name)
    {
        element.handle_map_file = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(decltype(element.map_file_buffer)), name);
        if (!element.handle_map_file)
        {
            MessageBoxA(GetActiveWindow(), "CreateFileMapping failed", "ACS", MB_OK);
        }

        element.map_file_buffer = (unsigned char*)MapViewOfFile(element.handle_map_file, FILE_MAP_READ, 0, 0, sizeof(decltype(element.map_file_buffer)));
        if (!element.map_file_buffer)
        {
            MessageBoxA(GetActiveWindow(), "MapViewOfFile failed", "ACS", MB_OK);
        }
    };

    init_element(this->m_physics, (LPCSTR)"Local\\acpmf_physics");
    init_element(this->m_graphics, (LPCSTR)"Local\\acpmf_graphics");
    init_element(this->m_static, (LPCSTR)"Local\\acpmf_static");
}

const SPageFileGraphic* ACSharedMemory::get_graphics()
{
    return this->file_graphics;
}

const SPageFilePhysics* ACSharedMemory::get_physics()
{
    return this->file_physics;
}

const SPageFileStatic* ACSharedMemory::get_static()
{
    return this->file_static;
}
