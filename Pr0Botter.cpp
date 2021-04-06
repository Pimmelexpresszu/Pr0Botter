// Pr0Botter.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>


//Set output mode for non ascii characters
#include <io.h>
#include <fcntl.h>


//Local Pr0botter includes
#include "Visual.h"


int main()
{
    //_setmode(_fileno(stdout), _O_U16TEXT);

    Pr0botter_Visual* visual;
    visual = &Pr0botter_Visual::getInstance();

 //   KeyboardHook = SetWindowsHookEx(
 //       WH_KEYBOARD_LL, // low-level keyboard input events
 //       HookProcedure, // pointer to the hook procedure
 //       GetModuleHandle(NULL), // A handle to the DLL containing the hook procedure 
 //       NULL //desktop apps, if this parameter is zero
 //   );
 //
 //   if (!KeyboardHook) {
 //
 //   }
 //   else {
 //       MSG Msg;
 //       while (GetMessage(&Msg, NULL, 0, 0) > 0)
 //       {
 //           TranslateMessage(&Msg);
 //           DispatchMessage(&Msg);
 //       }
 //   }
 //
 //   UnhookWindowsHookEx(
 //       KeyboardHook
 //   );
}




