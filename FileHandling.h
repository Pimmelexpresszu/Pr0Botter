#pragma once

/***************************************************************************************************
* Dateiname:	FileHandling.h
* Erstellt:		02.04.2021
*
* File description:
* The Keymapping is saved into a file. This class handles these safed files.
*
****************************************************************************************************/

#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include <iostream>
#include <fstream>
#include <vector>
#include "DataTypes.h"

class Pr0botter_FileHandling
{
private:
	//Singleton
	Pr0botter_FileHandling(Pr0botter_FileHandling const&) = delete;
	Pr0botter_FileHandling(Pr0botter_FileHandling&&) = delete;
	~Pr0botter_FileHandling() = default ;
	void operator=(Pr0botter_FileHandling const&) = delete;

	bool isUserConfigAvailable;
	std::ifstream ReadConfigHandle;
	std::ofstream WriteConfigHandle;

	void openConfigurationRead();
	void closeConfigurationRead();

	void openConfigurationWrite();
	void closeConfigurationWrite();

	std::string getPathToConfig();


public:
	Pr0botter_FileHandling();
	static Pr0botter_FileHandling& getInstance()
	{
		static Pr0botter_FileHandling instance;
		return instance;
	}

	bool GetIsUserConfigAvailable();
	void readConfiguration(std::vector<KeysAndTarget>* mapping);
	void writeConfiguration(std::vector<KeysAndTarget> mapping);

};


#endif /* FILEHANDLING_H */