#pragma once

/***************************************************************************************************
* Dateiname:	FileHandling.cpp
* Erstellt:		02.04.2021
*
*
****************************************************************************************************/

#define FILEHANDLING_SOURCE

#include "FileHandling.h"
#include <string>
#include "Windows.h"
#include "Fileapi.h"

/***************************************************************************************************
* PUBLIC FUNCTIONS
****************************************************************************************************/

Pr0botter_FileHandling::Pr0botter_FileHandling()
{
	
	openConfigurationRead();
	
	if (ReadConfigHandle.is_open())
	{
		isUserConfigAvailable = true;
	}
	else
	{
		isUserConfigAvailable = false;
	}
	closeConfigurationRead();
}

bool Pr0botter_FileHandling::GetIsUserConfigAvailable()
{
	return isUserConfigAvailable;
}


//Mapping has to be filled with any previous mapping (std mapping for example)
void Pr0botter_FileHandling::readConfiguration(std::vector<KeysAndTarget>* mapping)
{
	//Goto the beginning of the file
	closeConfigurationRead();
	openConfigurationRead();
	int elementIdentifier, vKey;

	//delete the current configuration
	if (mapping->size() != 0)
	{
		if (ReadConfigHandle.is_open())
		{
			while (ReadConfigHandle >> elementIdentifier >> vKey)
			{
				for (size_t i = 0; i < mapping->size(); i++)
				{
					if (elementIdentifier == static_cast<int>(mapping->at(i).element))
					{
						mapping->at(i).virtualSourceKeyValue = vKey;
						break;
					}
				}
			}
		}
	}
	closeConfigurationRead();
}

void Pr0botter_FileHandling::writeConfiguration(std::vector<KeysAndTarget> mapping)
{
	closeConfigurationRead();
	openConfigurationWrite();
	if (WriteConfigHandle.is_open())
	{
		for (size_t i = 0; i < mapping.size(); i++)
		{
			WriteConfigHandle << static_cast<int>(mapping[i].element) << " " << mapping[i].virtualSourceKeyValue << std::endl;
		}
	}

	closeConfigurationWrite();
}

/***************************************************************************************************
* PRIVATE FUNCTIONS
****************************************************************************************************/

void Pr0botter_FileHandling::openConfigurationRead() 
{
	ReadConfigHandle.open(getPathToConfig(), std::ifstream::in);
}

void Pr0botter_FileHandling::closeConfigurationRead()
{
	ReadConfigHandle.close();
}


void Pr0botter_FileHandling::openConfigurationWrite()
{
	WriteConfigHandle.open(getPathToConfig(), std::ofstream::out);
}

void Pr0botter_FileHandling::closeConfigurationWrite()
{
	WriteConfigHandle.close();
}

std::string Pr0botter_FileHandling::getPathToConfig()
{
	// Open the file. Check if the file is available
	//Get the path of the enviroment variable
	constexpr size_t maxLengthOfPath = 256;
	size_t requiredLengthOfPath;
	char Path[maxLengthOfPath];

	getenv_s(&requiredLengthOfPath, Path, maxLengthOfPath, "APPDATA");
	std::string Pr0botterDirectory = Path;



	Pr0botterDirectory += "\\Pr0botter\\";
	if (GetFileAttributesA(Pr0botterDirectory.c_str()) == INVALID_FILE_ATTRIBUTES) {
		CreateDirectoryA(Pr0botterDirectory.c_str(), NULL);
	}
	return Pr0botterDirectory + "pr0botter.cfg";
}