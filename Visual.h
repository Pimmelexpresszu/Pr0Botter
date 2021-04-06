#pragma once



/***************************************************************************************************
* Dateiname:	Visual.h
* Erstellt:		02.04.2021
*
* File description:
* This Class handels the visual output to the user. 
*
****************************************************************************************************/

#ifndef VISUAL_H
#define VISUAL_H

#include "KeyMapping.h"
#include "FileHandling.h"
class Pr0botter_Visual
{
private:
	//Singleton
	
	Pr0botter_Visual(Pr0botter_Visual const&) = delete;
	Pr0botter_Visual(Pr0botter_Visual&&) = delete;
	~Pr0botter_Visual() = default;
	void operator=(Pr0botter_Visual const&) = delete;

	void setStartScreen();
	void printCurrentKeymapping();
	Pr0botter_KeyMapping* keyMapping;

	void HandleKeys();

public:
	Pr0botter_Visual();

	void Init();

	static Pr0botter_Visual& getInstance()
	{
		static Pr0botter_Visual instance;
		return instance;
	}

	void setNewKeymapping();

};


#endif /* VISUAL_H */