
/***************************************************************************************************
* Dateiname:	Visual.h
* Erstellt:		02.04.2021
*
*
****************************************************************************************************/

#define VISUAL_SOURCE

#include "Visual.h"
#include <iostream>

//Includes for command handling
#include "windows.h"
#include <thread>
#include <chrono>
#include "winuser.h"
/***************************************************************************************************
* GLOBAL DATA
****************************************************************************************************/
HHOOK KeyboardHook;

volatile bool	globLeaveLoopFlag = false;
volatile int	globNextVk = 0u;

static BOOL CALLBACK enumWindowCallback(HWND hWnd, LPARAM lparam) {
	int length = GetWindowTextLength(hWnd);
	WCHAR buffer[600];
	GetWindowText(hWnd, buffer, 600);
	std::wstring windowTitle(buffer);
	bool isChrome = false;

	if (windowTitle.find(L"pr0gramm") != std::wstring::npos)
	{
		HWND currentWindow = GetForegroundWindow();

		//Since Chrome does not react on sent keystrokes if the browser is inactive
		//we sent the window in foreground, set the keystroke and maximize the last maximized window
		if (windowTitle.find(L"Chrome") != std::wstring::npos)
		{
			isChrome = true;
			SetForegroundWindow(hWnd);
		}

		//wait until chrome is in foreground
		if (isChrome)
		{
			std::this_thread::sleep_for((std::chrono::milliseconds)10);
		}


		int ret = PostMessage(hWnd, WM_KEYDOWN, (int)lparam, NULL);

		//restore the window
		if (isChrome)
		{
			std::this_thread::sleep_for((std::chrono::milliseconds)500);
			SetForegroundWindow(currentWindow);
		}

		//std::wcout << L"Found Window: " << windowTitle << std::endl;

	}

	return true;
}

void sendMessageToWindow(int key)
{
	//get the current mapping
	auto currentMapping = Pr0botter_KeyMapping::getInstance().GetCurrentKeymapping();

	//iterate through the elements
	for (size_t i = 0; i < currentMapping.size(); i++)
	{
		//If the pushed button is found send the corresponding key.
		if (currentMapping[i].virtualSourceKeyValue == key)
		{
			EnumWindows(enumWindowCallback, currentMapping[i].virtualTargetKeyValue);
			break;
		}
	}

	
}

LRESULT CALLBACK HookProcedureSendKeys(int nCode, WPARAM wParam, LPARAM lParam)
{

	if (nCode == HC_ACTION)
	{
		KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;

		if (wParam == WM_KEYDOWN)
		{
			if (p->vkCode == VK_F12)
			{
				globLeaveLoopFlag = true;
			}
			else
			{
				sendMessageToWindow(p->vkCode);
			}
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT CALLBACK HookProcedureGetVKCode(int nCode, WPARAM wParam, LPARAM lParam)
{
	

	if (nCode == HC_ACTION)
	{
		KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;

		if (wParam == WM_KEYDOWN)
		{
			globNextVk = p->vkCode;
		}
	}
	return false;
}

/***************************************************************************************************
* PUBLIC FUNCTIONS
****************************************************************************************************/


Pr0botter_Visual::Pr0botter_Visual()
{
	keyMapping = &Pr0botter_KeyMapping::getInstance();
	setStartScreen();
}

void Pr0botter_Visual::Init()
{

	
}

void Pr0botter_Visual::setNewKeymapping()
{

	auto mapping = keyMapping->GetCurrentKeymapping();
	MSG Msg;

	//Remove the listening to the current keys
	UnhookWindowsHookEx(
		KeyboardHook
	);

	//Clear the console
	system("cls");

	

	// print all elements
	for (size_t i = 0; i < mapping.size(); i++)
	{
		//setup Keyboard listener for one key
		KeyboardHook = SetWindowsHookEx(
			WH_KEYBOARD_LL, // low-level keyboard input events
			HookProcedureGetVKCode, // pointer to the hook procedure
			GetModuleHandle(NULL), // A handle to the DLL containing the hook procedure 
			NULL //Give pointer to current mapping to hook function
		);

		std::cout << "Function: " << keyMapping->getStringForFunction(mapping[i].element) << "\t->\t";    std::cout.flush();
	
		//wait for the pressed key
		while (globNextVk == 0u)
		{
			PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE);
		}

		//Set the pressed vkcode in the mapping
		mapping[i].virtualSourceKeyValue = globNextVk;

		std::cout << keyMapping->getStringForKey(mapping[i].virtualSourceKeyValue) << std::endl;

		//reset nextVk_Code
		globNextVk = 0u;
	}

	//Set new keymapping active
	keyMapping->SetNewKeymapping(mapping);

	//set looop variable to stay in loop
	globLeaveLoopFlag = false;

	//Go back to handle keys
	setStartScreen();
}


/***************************************************************************************************
* PRIVATE FUNCTIONS
****************************************************************************************************/

void Pr0botter_Visual::setStartScreen()
{
	//Clear the console
	system("cls");
	std::cout << "Pr0Botter  -  Control your Pr0gram    " << std::endl;
	std::cout << "   Der Pr0botter erlaubt es dir Tasteneingaben an deinen Browser zu senden, " << std::endl;
	std::cout << "   Auch wenn dieser gerade im Hintergrund läuft und du beispielsweise ein " << std::endl;
	std::cout << "   Spiel im Vollbildmodus geöffnet hast " << std::endl;
	std::cout << "   Solange in diesem im geöffneten Tab Pr0gramm.com geoeffnet ist " << std::endl;
	std::cout << "   Der Browser muss sichtbar geöffnet sein (2. Bildschirm) " << std::endl;
	std::cout << "   Achtung: Firefox funktioniert perfekt. Für chrome muss das spiel ganz kurz minimiert werden. " << std::endl;
	std::cout << "   Dies macht aber ebenfalls dieses program für dich. Nicht schoen aber geht nicht anders. " << std::endl;

	if (keyMapping->GetIsUserConfigAvailable())
	{
		std::cout << "   Folgende Nutzerkonfiguration geladen: " << std::endl;
	}
	else
	{
		std::cout << "\n\n   Keine Nutzerkonfiguration geladen. \n   Standard Konfiguration geladen." << std::endl;
	}
	printCurrentKeymapping();

	std::cout << "\n\nPush F12 to set a new configuration" << std::endl;

	//Go to the keyhandling
	HandleKeys();
}

void Pr0botter_Visual::printCurrentKeymapping()
{
	
	auto mapping = keyMapping->GetCurrentKeymapping();

	std::cout << "\n\nAktuelle Konfiguration: " << std::endl;

	// print all elements
	for (size_t i = 0; i < mapping.size(); i++)
	{
		std::cout << "Funktion: " << keyMapping->getStringForFunction(mapping[i].element) << "\t->\t" << keyMapping->getStringForKey(mapping[i].virtualSourceKeyValue) << std::endl;
	}

}

void Pr0botter_Visual::HandleKeys()
{

	//setup Keyboard Hook
	KeyboardHook = SetWindowsHookEx(
		WH_KEYBOARD_LL, // low-level keyboard input events
		HookProcedureSendKeys, // pointer to the hook procedure
		GetModuleHandle(NULL), // A handle to the DLL containing the hook procedure 
		NULL //Give pointer to current mapping to hook function
	);

	if (!KeyboardHook) {

	}
	else {
		MSG Msg;
		while (globLeaveLoopFlag == false)
		{
			PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE) > 0;
			//std::cout << "test" << std::endl;
		}
		setNewKeymapping();
	}
}