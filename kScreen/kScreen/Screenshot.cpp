#include <windows.h>
#include <windowsx.h>

#include "Screenshot.h"

Screenshot :: Screenshot(HWND hWindow)
{
	hWnd = hWindow;
	hbmScr = NULL;
}

Screenshot :: ~Screenshot()
{
	DeleteObject( hbmScr );
}

void Screenshot :: Capture( int x, int y, int width, int height )
{
	HDC hdc;
	HDC hdcScr;

	hdc = GetDC( NULL );
	hdcScr = CreateCompatibleDC( hdc );
	hbmScr = CreateCompatibleBitmap( hdc, width, height );

	SelectObject( hdcScr, hbmScr );
	BitBlt( hdcScr, 0, 0, width, height,
			hdc, x, y, SRCCOPY );

	GetObject( hbmScr, sizeof(BITMAP), &bmpScr );

	//BITMAPINFOHEADER bi;
	//bi.biSize = sizeof(BITMAPINFOHEADER);    
	//bi.biWidth = bmpScr.bmWidth;    
	//bi.biHeight = bmpScr.bmHeight;  
	//bi.biPlanes = 1;    
	//bi.biBitCount = 32;    
	//bi.biCompression = BI_RGB;    
	//bi.biSizeImage = 0;  
	//bi.biXPelsPerMeter = 0;    
	//bi.biYPelsPerMeter = 0;    
	//bi.biClrUsed = 0;    
	//bi.biClrImportant = 0;

	//DWORD dwBmpSize = ((bmpScr.bmWidth * bi.biBitCount + 31) / 32) * 4 * bmpScr.bmHeight;
	//HANDLE hDIB = GlobalAlloc(GHND,dwBmpSize); 
	//lpBuf = (unsigned char *)GlobalLock(hDIB);

	//GetDIBits( hdcScr, hbmScr, 0, (UINT)bmpScr.bmHeight, lpBuf, (BITMAPINFO *)&bi, DIB_RGB_COLORS );
	//bmpScr.bmBits = lpBuf;


	DeleteObject( hdcScr );
	ReleaseDC( NULL, hdc );

}

void Screenshot :: PaintPreview( HDC hdc, RECT rcClient )
{
	const int width=rcClient.right-rcClient.left;
	const int height=rcClient.bottom-rcClient.top;


	HDC hdcMem = CreateCompatibleDC( hdc );

	SetStretchBltMode( hdc, HALFTONE );

	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbmScr);

	StretchBlt( hdc, 0, 0, width, height,
				hdcMem, 0, 0, bmpScr.bmWidth, bmpScr.bmHeight, SRCCOPY);

	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem);
}


