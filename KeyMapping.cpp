#pragma once

/***************************************************************************************************
* Dateiname:	KeyMapping.cpp
* Erstellt:		02.04.2021
*
*
****************************************************************************************************/

#define KEYMAPPING_SOURCE

#include "KeyMapping.h"
#include <Windows.h>
#include "WinUser.h"

/***************************************************************************************************
* PUBLIC FUNCTIONS
****************************************************************************************************/

void Pr0botter_KeyMapping::Init()
{
	KeyMapping.clear();
}

bool Pr0botter_KeyMapping::GetIsUserConfigAvailable()
{
	return fileHandling->GetIsUserConfigAvailable();
}

Pr0botter_KeyMapping::Pr0botter_KeyMapping()
{
	fileHandling = &Pr0botter_FileHandling::getInstance();
}

std::vector<KeysAndTarget> Pr0botter_KeyMapping::GetCurrentKeymapping()
{
	if (KeyMapping.size() == 0u)
	{
		setStandardKeyMapping();

		if (fileHandling->GetIsUserConfigAvailable())
		{
			fileHandling->readConfiguration(&KeyMapping);
		}
	}
	return KeyMapping;
}



//Lookuptable vor virtual key values to string
std::string Pr0botter_KeyMapping::getStringForKey(int VK_Number)
{
	switch (VK_Number)
	{
		case VK_NUMPAD0				:	return "NUMPAD0  "; break;
		case VK_NUMPAD1				:	return "NUMPAD1  "; break;
		case VK_NUMPAD2				:	return "NUMPAD2  "; break;
		case VK_NUMPAD3				:	return "NUMPAD3  "; break;
		case VK_NUMPAD4				:	return "NUMPAD4  "; break;
		case VK_NUMPAD5				:	return "NUMPAD5  "; break;
		case VK_NUMPAD6				:	return "NUMPAD6  "; break;
		case VK_NUMPAD7				:	return "NUMPAD7  "; break;
		case VK_NUMPAD8				:	return "NUMPAD8  "; break;
		case VK_NUMPAD9				:	return "NUMPAD9  "; break;
		case VK_MULTIPLY			:	return "MULTIPLY "; break;
		case VK_ADD					:	return "ADD      "; break;
		case VK_SEPARATOR			:	return "SEPARATOR"; break;
		case VK_SUBTRACT			:	return "SUBTRACT "; break;
		case VK_DECIMAL				:	return "DECIMAL  "; break;
		case VK_DIVIDE				:	return "DIVIDE   "; break;
		case VK_F1					:	return "F1       "; break;
		case VK_F2					:	return "F2       "; break;
		case VK_F3					:	return "F3       "; break;
		case VK_F4					:	return "F4       "; break;
		case VK_F5					:	return "F5       "; break;
		case VK_F6					:	return "F6       "; break;
		case VK_F7					:	return "F7       "; break;
		case VK_F8					:	return "F8       "; break;
		case VK_F9					:	return "F9       "; break;
		case VK_F10					:	return "F10      "; break;
		case VK_F11					:	return "F11      "; break;
		case VK_F12					:	return "F12      "; break;
		case VK_F13					:	return "F13      "; break;
		case VK_F14					:	return "F14      "; break;
		case VK_F15					:	return "F15      "; break;
		case VK_F16					:	return "F16      "; break;
		case VK_F17					:	return "F17      "; break;
		case VK_F18					:	return "F18      "; break;
		case VK_F19					:	return "F19      "; break;
		case VK_F20					:	return "F20      "; break;
		case VK_F21					:	return "F21      "; break;
		case VK_F22					:	return "F22      "; break;
		case VK_F23					:	return "F23      "; break;
		case VK_F24					:	return "F24      "; break;
		case VK_0_key				:	return "0_key"	;break;
		case VK_1_key				:	return "1_key"	;break;
		case VK_2_key				:	return "2_key"	;break;
		case VK_3_key				:	return "3_key"	;break;
		case VK_4_key				:	return "4_key"	;break;
		case VK_5_key				:	return "5_key"	;break;
		case VK_6_key				:	return "6_key"	;break;
		case VK_7_key				:	return "7_key"	;break;
		case VK_8_key				:	return "8_key"	;break;
		case VK_9_key				:	return "9_key"	;break;
		case VK_A_key				:	return "A_key"	;break;
		case VK_B_key				:	return "B_key"	;break;
		case VK_C_key				:	return "C_key"	;break;
		case VK_D_key				:	return "D_key"	;break;
		case VK_E_key				:	return "E_key"	;break;
		case VK_F_key				:	return "F_key"	;break;
		case VK_G_key				:	return "G_key"	;break;
		case VK_H_key				:	return "H_key"	;break;
		case VK_I_key				:	return "I_key"	;break;
		case VK_J_key				:	return "J_key"	;break;
		case VK_K_key				:	return "K_key"	;break;
		case VK_L_key				:	return "L_key"	;break;
		case VK_M_key				:	return "M_key"	;break;
		case VK_N_key				:	return "N_key"	;break;
		case VK_O_key				:	return "O_key"	;break;
		case VK_P_key				:	return "P_key"	;break;
		case VK_Q_key				:	return "Q_key"	;break;
		case VK_R_key				:	return "R_key"	;break;
		case VK_S_key				:	return "S_key"	;break;
		case VK_T_key				:	return "T_key"	;break;
		case VK_U_key				:	return "U_key"	;break;
		case VK_V_key				:	return "V_key"	;break;
		case VK_W_key				:	return "W_key"	;break;
		case VK_X_key				:	return "X_key"	;break;
		case VK_Y_key				:	return "Y_key"	;break;
		case VK_Z_key				:	return "Z_key"	;break;
		case VK_VOLUME_MUTE			:	return "VK_VOLUME_MUTE         "; break;
		case VK_VOLUME_DOWN			:	return "VK_VOLUME_DOWN         "; break;
		case VK_VOLUME_UP			:	return "VK_VOLUME_UP           "; break;
		case VK_MEDIA_NEXT_TRACK	:	return "VK_MEDIA_NEXT_TRACK    "; break;
		case VK_MEDIA_PREV_TRACK	:	return "VK_MEDIA_PREV_TRACK    "; break;
		case VK_MEDIA_STOP			:	return "VK_MEDIA_STOP          "; break;
		case VK_MEDIA_PLAY_PAUSE	:	return "VK_MEDIA_PLAY_PAUSE    "; break;
		case VK_LAUNCH_MAIL			:	return "VK_LAUNCH_MAIL         "; break;
		case VK_LAUNCH_MEDIA_SELECT	:	return "VK_LAUNCH_MEDIA_SELECT "; break;
		case VK_LAUNCH_APP1			:	return "VK_LAUNCH_APP1         "; break;
		case VK_LAUNCH_APP2			:	return "VK_LAUNCH_APP2         "; break;

		default: return "unknown key";
		break;
	}
}

std::string Pr0botter_KeyMapping::getStringForFunction(ManipulatableElements Element)
{
	switch (Element)
	{
	
		case	ManipulatableElements::nextPost		: return  "Naechster Post       ";
		case	ManipulatableElements::lastPost		: return  "Vorangegangener Post ";
		case	ManipulatableElements::scrollUp		: return  "Hoch scrollen        ";
		case	ManipulatableElements::scrollDown	: return  "Runter scrollen      ";
		case	ManipulatableElements::blussi		: return  "Blussi               ";
		case	ManipulatableElements::minus		: return  "Immer han i di pech  ";
		case	ManipulatableElements::favorit		: return  "Favorisieren         ";
		case	ManipulatableElements::muteUnmute	: return  "Mute oder Unmute     ";
		case	ManipulatableElements::playPause	: return  "Play oder Pause      ";
		default: return "Unknown function";

	}
}

void Pr0botter_KeyMapping::SetNewKeymapping(std::vector<KeysAndTarget> newMapping)
{
	KeyMapping = newMapping;
	fileHandling->writeConfiguration(KeyMapping);
}

/***************************************************************************************************
* PRIVATE FUNCTIONS
****************************************************************************************************/

void Pr0botter_KeyMapping::setStandardKeyMapping() 
{
	if (KeyMapping.size() != 0)
	{
		KeyMapping.clear();
	}

	KeyMapping.push_back({ ManipulatableElements::nextPost,		VK_NUMPAD6	, VK_RIGHT		});
	KeyMapping.push_back({ ManipulatableElements::lastPost,		VK_NUMPAD4	, VK_LEFT		});
	KeyMapping.push_back({ ManipulatableElements::scrollUp,		VK_NUMPAD8	, VK_UP			});
	KeyMapping.push_back({ ManipulatableElements::scrollDown,	VK_NUMPAD5	, VK_DOWN		});
	KeyMapping.push_back({ ManipulatableElements::blussi,		VK_ADD		, VK_ADD		});
	KeyMapping.push_back({ ManipulatableElements::minus,		VK_SUBTRACT , VK_SUBTRACT	});
	KeyMapping.push_back({ ManipulatableElements::favorit,		VK_NUMPAD1	, VK_F_key		});
	KeyMapping.push_back({ ManipulatableElements::muteUnmute,	VK_NUMPAD7	, VK_Q_key		});
	KeyMapping.push_back({ ManipulatableElements::playPause,	VK_NUMPAD9	, VK_P_key		});

}
