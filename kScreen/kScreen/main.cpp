#include <windows.h>
#include <windowsx.h>
//#pragma comment( lib, "comctl32.lib") 
//#include <commctrl.h >
//#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
//processorArchitecture='X86' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "define.h"
#include "nsTrayWait.h"


int WINAPI WinMain( HINSTANCE osInstance, HINSTANCE osPrevInst, LPSTR osCmdString, int osCmdShow )
{
	//return nsWMain::Run( osInstance , "Test", 50, 80, 640, 400);
	return nsTrayWait::Run( osInstance );
}
