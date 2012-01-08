#include <windows.h>
#include <windowsx.h>

#include "nsWMain.h"
#include "TrayIcon.h"
#include "resource.h"

namespace nsTrayWait
{
	HINSTANCE Instance;
	HWND      hwShell;
	TrayIcon *ti;

	int Run( HINSTANCE instance );
	void ShellCreate( char* name, int x, int y, int w, int h);
	LRESULT WINAPI ShellManager( HWND, UINT, WPARAM, LPARAM );

	void ShowTrayMenu();

	void wmTray( HWND hw, UINT Code, WPARAM wP, LPARAM lP );
	void wmCommand( HWND hw, UINT Code, WPARAM wP, LPARAM lP );
};

int nsTrayWait :: Run( HINSTANCE instance )
{
	Instance = instance;

	ShellCreate( "traywnd", 0, 0, 0, 0 ); 
	ShowWindow(hwShell,SW_HIDE);

	ti = new TrayIcon( Instance, hwShell, TRAYICON_ID, MAKEINTRESOURCE(IDI_ICONTRAY), WM_TRAY,TEXT("kScreen") );

	MSG Message;
	while( GetMessage( &Message,0,0,0 ) > 0 )
	{	
		TranslateMessage( &Message );
		DispatchMessage( &Message );
	}
	return (int) Message.wParam;
}
LRESULT WINAPI nsTrayWait :: ShellManager( HWND hw, UINT Code, WPARAM wP, LPARAM lP )
{
	switch( Code ) 
	{
		case WM_DESTROY:
			//DestroyTrayIcon();
			delete ti;

			PostQuitMessage(0);
			break;
		case WM_TRAY:
			wmTray( hw, Code, wP, lP );
			break;
		case WM_COMMAND:
			wmCommand( hw, Code, wP, lP );
			break;
		default:
			return DefWindowProc( hw, Code, wP, lP );
			break;
	}
	return 0;
}
void nsTrayWait :: ShellCreate( char* name,int x,int y,int w,int h )
{	
	WNDCLASS s;
	ZeroMemory( &s, sizeof s );
	s.hInstance     = Instance;
	s.lpfnWndProc   = ShellManager;
	s.lpszClassName = name;
	RegisterClass( &s );
	hwShell = CreateWindow( name, name,
							WS_EX_TOOLWINDOW,
							x, y, w, h,
							NULL, NULL, Instance, NULL );
}

void nsTrayWait :: ShowTrayMenu()
{
	HMENU hMenu = LoadMenu( Instance, MAKEINTRESOURCE(IDR_MENUTRAY) );
	if(!hMenu)  return;
	HMENU hPopup = GetSubMenu(hMenu, 0);
	if(!hPopup) return;

	SetForegroundWindow(hwShell);

	POINT pt;
	GetCursorPos(&pt);
	BOOL bOK = TrackPopupMenu(hPopup, TPM_LEFTALIGN, pt.x, pt.y, 0, hwShell, NULL);

	DestroyMenu(hMenu);
}

void nsTrayWait :: wmTray( HWND hw, UINT Code, WPARAM wP, LPARAM lP )
{
	if(wP == TRAYICON_ID)
	{
		switch((UINT)lP)
		{
			case WM_LBUTTONDOWN:
				//ti->ShowMessage( TEXT("Тест"), NIIF_INFO, NULL );
				nsWMain::Run( Instance, "Screenshot", CW_USEDEFAULT, CW_USEDEFAULT, 800,600 );
				break;
			case WM_RBUTTONDOWN:
				ShowTrayMenu();
				break;
		}
	}
}
void nsTrayWait :: wmCommand( HWND hw, UINT Code, WPARAM wP, LPARAM lP )
{
	switch(wP)
	{
		case ID_TRAYMENU_EXIT:
			SendMessage(hwShell,WM_DESTROY,NULL,NULL);
			break;
	}
}