#include "WindowsCommunicator.h"

#include <tchar.h>
#include <iostream>
#include <fstream>


// ToDo: Check, if MAP_OBJECT_NAME also works as const string
const std::string WINDOWS_TO_LINUX_FILE {"C:\\Users\\lukas\\Documents\\Projects\\autonomous-racing\\DataTransfer\\SharedData\\shared_data_windows_to_linux.txt"};
const std::string LINUX_TO_WINDOWS_FILE {"C:\\Users\\lukas\\Documents\\Projects\\autonomous-racing\\DataTransfer\\SharedData\\shared_data_linux_to_windows.txt"};


int main()
{
	WindowsCommunicator wc(WINDOWS_TO_LINUX_FILE, LINUX_TO_WINDOWS_FILE);
	while (true)
	{
		wc.write_data();
		//ToDo: with multithreading, also read the control data with wc.read_data() and send controls to AssettoCorsa
	}
}


WindowsCommunicator::WindowsCommunicator(std::string_view windows_to_linux_file, std::string_view linux_to_windows_file)
{
    this->windows_to_linux_file = windows_to_linux_file;
    this->linux_to_windows_file = linux_to_windows_file;

    this->init_smelements();
}

void WindowsCommunicator::write_data()
{
    std::ofstream out_file(this->windows_to_linux_file);
    const SPageFilePhysics* fp = (SPageFilePhysics*)this->m_physics.mapFileBuffer;
    const SPageFileGraphic* fg = (SPageFileGraphic*)this->m_graphics.mapFileBuffer;
    const SPageFileStatic* fs = (SPageFileStatic*)this->m_static.mapFileBuffer;

    std::cout<<"heading: "<<fp->heading<<" coordinates: "<<fg->carCoordinates[0]<<" "<<fg->carCoordinates[2]<<std::endl;
    
    out_file << "gas" << " " << fp->gas << std::endl
        << "brake" << " " << fp->brake << std::endl
        << "fuel" << " " << fp->fuel << std::endl
        << "gear" << " " << fp->gear << std::endl
        << "rpms" << " " << fp->rpms << std::endl
        << "steerAngle" << " " << fp->steerAngle << std::endl
        << "speedKmh" << " " << fp->speedKmh << std::endl
		<< "velocity" << " " << fp->velocity[0]
            << " " << fp->velocity[1]
            << " " << fp->velocity[2] << std::endl
        << "accG" << " " << fp->accG[0]
            << " " << fp->accG[1]
            << " " << fp->accG[2] << std::endl
        << "wheelSlip" << " " << fp->wheelSlip[0]
            << " " << fp->wheelSlip[1]
            << " " << fp->wheelSlip[2]
            << " " << fp->wheelSlip[3] << std::endl
        << "tyreWear" << " " << fp->tyreWear[0]
            << " " << fp->tyreWear[1]
            << " " << fp->tyreWear[2]
            << " " << fp->tyreWear[3] << std::endl
        << "heading" << " " << fp->heading << std::endl
        << "pitch" << " " << fp->pitch << std::endl
        << "roll" << " " << fp->roll << std::endl
        << "cgHeight" << " " << fp->cgHeight << std::endl
        << "carDamage" << " " << fp->carDamage[0]
            << " " << fp->carDamage[1]
            << " " << fp->carDamage[2]
            << " " << fp->carDamage[3]
            << " " << fp->carDamage[4] << std::endl
        
        << "status" << " " << fg->status << std::endl
        << "session" << " " << fg->session << std::endl
        << "carCoordinates" << " " << fg->carCoordinates[0]
            << " " << fg->carCoordinates[1]
            << " " << fg->carCoordinates[2] << std::endl
        
        << "maxTorque" << " " << fs->maxTorque << std::endl
        << "maxPower" << " " << fs->maxPower << std::endl
        << "maxRpm" << " " << fs->maxRpm << std::endl;

        out_file.close();
}

std::map<std::string, double> WindowsCommunicator::read_data()
{
	std::map<std::string, double> umap;
	std::string key;
	double val;
	std::ifstream in_file(this->linux_to_windows_file);
	while (in_file >> key >> val)
	{
		umap[key] = val;
	}
	return umap;
}

void WindowsCommunicator::init_smelements()
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
