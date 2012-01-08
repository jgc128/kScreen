#include <windows.h>
#include <windowsx.h>

class Screenshot
{
private:
	HWND hWnd;

	BITMAP bmpScr;
	HBITMAP hbmScr;
	unsigned char * lpBuf;

public:
	Screenshot( HWND hWnd);
	~Screenshot();

	void Capture( int x, int y, int width, int height );

	void PaintPreview( HDC hdc, RECT rcClient );

};