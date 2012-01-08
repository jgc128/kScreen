#include <windows.h>
#include <windowsx.h>

#include "Screenshot.h"

namespace nsWMain
{
	HINSTANCE Instance;
	HWND      hwShell;
	Screenshot * scr;

	int Run( HINSTANCE instance, char* name,
				 int x, int y, int w, int h );
	void ShellCreate( char* name, int x, int y, int w, int h);
	LRESULT WINAPI ShellManager( HWND, UINT, WPARAM, LPARAM );

	void OnCreate(HWND);

	void CaptureAnImage(HWND);
}

int nsWMain :: Run( HINSTANCE instance, char* name, int x, int y, int w, int h )
{
	scr = new Screenshot( hwShell );
	scr->Capture( 0, 0, 500, 400 );

	ShellCreate( name, x, y, w, h );

	ShowWindow(hwShell, SW_SHOW); 
	UpdateWindow(hwShell); 

	//MSG Message;
	//while( GetMessage( &Message,0,0,0 ) > 0 )
	//{	TranslateMessage( &Message );
	//	DispatchMessage( &Message );
	//}
	//return (int) Message.wParam;

	return 0;
}

void nsWMain :: ShellCreate( char* name,int x,int y,int w,int h )
{	WNDCLASS s;
	ZeroMemory( &s, sizeof s );
	s.hInstance     = Instance;
	s.lpfnWndProc   = ShellManager;
	s.hIcon         = LoadIcon( NULL, IDI_APPLICATION );
	s.hCursor       = LoadCursor( NULL, IDC_ARROW );
	s.hbrBackground = (HBRUSH) ( COLOR_MENU+1 );
	s.lpszClassName = name;
	RegisterClass( &s );
	hwShell = CreateWindow( name, name,
							WS_OVERLAPPEDWINDOW | WS_VISIBLE,
							x, y, w, h,
							NULL, NULL, Instance, NULL );

}

LRESULT WINAPI nsWMain :: ShellManager( HWND hw, UINT Code, WPARAM wP, LPARAM lP )
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rcClient;

	switch( Code ) 
	{
		case WM_DESTROY:
			delete scr;

			PostQuitMessage( 0 );
			break;
		case WM_CREATE:
			OnCreate( hw );
			break;
		case WM_PAINT:
			
			GetClientRect( hw, &rcClient );

			hdc = BeginPaint( hw, &ps );

			scr->PaintPreview( hdc, rcClient );
			//scr->PaintPreview( 0, 0, rcClient.right-rcClient.left, rcClient.bottom-rcClient.top );
			//CaptureAnImage(hwShell);
			
			EndPaint(hw, &ps);

			break;
		case WM_SIZE:
			if(wP == SIZE_RESTORED)
			{
				GetClientRect( hw, &rcClient );
				InvalidateRect( hw, &rcClient, false );
			}
			break;
		default:
			return DefWindowProc( hw, Code, wP, lP );//остальные сообщения
			break;
	}
	return 0;
}
void nsWMain :: OnCreate(HWND hWnd)
{


}

void nsWMain :: CaptureAnImage(HWND hWnd)
{
	// Capturing screenshot
	HDC hdcScreen;
	HDC hdcWnd;

	int screenHeight = GetSystemMetrics( SM_CYSCREEN );
	int screenWidth = GetSystemMetrics( SM_CXSCREEN );

	HDC hdcMemDC = NULL;
	HBITMAP hbmScreen = NULL;
	//BITMAP bmpScreen;

	hdcScreen = GetDC(NULL);
	hdcWnd = GetDC(hWnd);

	hdcMemDC = CreateCompatibleDC( hdcWnd );

	RECT rcClient;
	GetClientRect( hwShell, &rcClient );

	SetStretchBltMode( hdcWnd, HALFTONE );
	StretchBlt( hdcWnd, 0, 0, rcClient.right, rcClient.bottom,
				hdcScreen, 0, 0, screenWidth, screenHeight,
				SRCCOPY);

	hbmScreen = CreateCompatibleBitmap( hdcWnd, rcClient.right-rcClient.left, rcClient.bottom-rcClient.top );
	SelectObject( hdcMemDC, hbmScreen );
	BitBlt( hdcMemDC, 0, 0, rcClient.right-rcClient.left, rcClient.bottom-rcClient.top, 
			   hdcWnd, 0,0, SRCCOPY );

	DeleteObject(hbmScreen);
	DeleteObject(hdcMemDC);
	ReleaseDC(NULL,hdcScreen);
	ReleaseDC(hWnd,hdcWnd);
}