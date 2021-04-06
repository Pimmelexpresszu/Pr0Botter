#pragma once


/***************************************************************************************************
* Dateiname:	KeyMapping.h
* Erstellt:		02.04.2021
*
* File description:
* This class handels all mapped keys.
*
****************************************************************************************************/

#ifndef KEYMAPPING_H
#define KEYMAPPING_H

#include <vector>
#include <string>
#include "FileHandling.h"
#include "DataTypes.h"




#define VK_0_key			0x30
#define VK_1_key			0x31
#define VK_2_key			0x32
#define VK_3_key			0x33
#define VK_4_key			0x34
#define VK_5_key			0x35
#define VK_6_key			0x36
#define VK_7_key			0x37
#define VK_8_key			0x38
#define VK_9_key			0x39
#define VK_A_key			0x41
#define VK_B_key			0x42
#define VK_C_key			0x43
#define VK_D_key			0x44
#define VK_E_key			0x45
#define VK_F_key			0x46
#define VK_G_key			0x47
#define VK_H_key			0x48
#define VK_I_key			0x49
#define VK_J_key			0x4A
#define VK_K_key			0x4B
#define VK_L_key			0x4C
#define VK_M_key			0x4D
#define VK_N_key			0x4E
#define VK_O_key			0x4F
#define VK_P_key			0x50
#define VK_Q_key			0x51
#define VK_R_key			0x52
#define VK_S_key			0x53
#define VK_T_key			0x54
#define VK_U_key			0x55
#define VK_V_key			0x56
#define VK_W_key			0x57
#define VK_X_key			0x58
#define VK_Y_key			0x59
#define VK_Z_key			0x5A

class Pr0botter_KeyMapping
{
private:
	//Singleton
	Pr0botter_KeyMapping(Pr0botter_KeyMapping const&) = delete;
	Pr0botter_KeyMapping(Pr0botter_KeyMapping&&) = delete;
	~Pr0botter_KeyMapping() = default;
	void operator=(Pr0botter_KeyMapping const&) = delete;

	//Functions
	void setStandardKeyMapping();

	//Variables
	Pr0botter_FileHandling* fileHandling;
	std::vector<KeysAndTarget> KeyMapping;

	
public:
	Pr0botter_KeyMapping();

	void Init();

	static Pr0botter_KeyMapping& getInstance()
	{
		static Pr0botter_KeyMapping instance;
		return instance;
	}

	bool GetIsUserConfigAvailable();

	std::vector<KeysAndTarget> GetCurrentKeymapping();
	void SetNewKeymapping(std::vector<KeysAndTarget> newMapping);

	std::string getStringForKey(int VK_Number);
	std::string getStringForFunction(ManipulatableElements Element);
};


#endif /* KEYMAPPING_H */