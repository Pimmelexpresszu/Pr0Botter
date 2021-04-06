#pragma once

/***************************************************************************************************
* Dateiname:	DataTypes.h
* Erstellt:		06.04.2021
*
* File description:
* Defines the needed datastructures
*
****************************************************************************************************/



#ifndef DATATYPES_H
#define DATATYPES_H

enum class ManipulatableElements {
	nextPost = 0xF0,
	lastPost = 0xF1,
	scrollUp = 0xF2,
	scrollDown = 0xF3,
	blussi = 0xF4,
	minus = 0xF5,
	favorit = 0xF6,
	muteUnmute = 0xF7,
	playPause = 0xF8
};


typedef struct {
	ManipulatableElements element;
	unsigned int virtualSourceKeyValue;
	unsigned int virtualTargetKeyValue;

}KeysAndTarget;




#endif /* DATATYPES_H */