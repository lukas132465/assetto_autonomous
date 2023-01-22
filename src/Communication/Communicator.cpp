#include "Communicator.h"

#include <tchar.h>
#include <iostream>
#include <fstream>

#include <boost/interprocess/mapped_region.hpp>


const char sm_out_name[] = "sm_control";

Communicator::Communicator()
{
    this->init_smelements();
    this->init_shared_memory_out();
}

void Communicator::update_input_shared_memory()
{
    this->file_physics = (SPageFilePhysics*)this->m_physics.mapFileBuffer;
    this->file_graphic = (SPageFileGraphic*)this->m_graphics.mapFileBuffer;
    this->file_static = (SPageFileStatic*)this->m_static.mapFileBuffer;

    std::cout<<"heading: "<<this->file_physics->heading<<" coordinates: "<<this->file_graphic->carCoordinates[0]<<" "<<this->file_graphic->carCoordinates[2]<<std::endl;
    
}

void Communicator::init_shared_memory_out()
{
    this->shmem = boost::interprocess::windows_shared_memory(boost::interprocess::create_only, sm_out_name, boost::interprocess::read_write, 2);
}

void Communicator::update_output_shared_memory(float arr[2])
{
    boost::interprocess::mapped_region region(this->shmem, boost::interprocess::read_write);

    std::memcpy(region.get_address(), arr, 2*sizeof(float));
}

void Communicator::init_smelements()
{
    TCHAR fpName[] = TEXT("Local\\acpmf_physics");
	this->m_physics.hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(SPageFilePhysics), fpName);
	if (!this->m_physics.hMapFile)
	{
		MessageBoxA(GetActiveWindow(), "CreateFileMapping failed", "ACS", MB_OK);
	}
	this->m_physics.mapFileBuffer = (unsigned char*)MapViewOfFile(this->m_physics.hMapFile, FILE_MAP_READ, 0, 0, sizeof(SPageFilePhysics));
	if (!this->m_physics.mapFileBuffer)
	{
		MessageBoxA(GetActiveWindow(), "MapViewOfFile failed", "ACS", MB_OK);
	}

    TCHAR fgName[] = TEXT("Local\\acpmf_graphics");
	this->m_graphics.hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(SPageFileGraphic), fgName);
	if (!this->m_graphics.hMapFile)
	{
		MessageBoxA(GetActiveWindow(), "CreateFileMapping failed", "ACS", MB_OK);
	}
	this->m_graphics.mapFileBuffer = (unsigned char*)MapViewOfFile(this->m_graphics.hMapFile, FILE_MAP_READ, 0, 0, sizeof(SPageFileGraphic));
	if (!this->m_graphics.mapFileBuffer)
	{
		MessageBoxA(GetActiveWindow(), "MapViewOfFile failed", "ACS", MB_OK);
	}

    TCHAR fsName[] = TEXT("Local\\acpmf_static");
	this->m_static.hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(SPageFileStatic), fsName);
	if (!this->m_static.hMapFile)
	{
		MessageBoxA(GetActiveWindow(), "CreateFileMapping failed", "ACS", MB_OK);
	}
	this->m_static.mapFileBuffer = (unsigned char*)MapViewOfFile(this->m_static.hMapFile, FILE_MAP_READ, 0, 0, sizeof(SPageFileStatic));
	if (!this->m_static.mapFileBuffer)
	{
		MessageBoxA(GetActiveWindow(), "MapViewOfFile failed", "ACS", MB_OK);
	}
}
