#include <windows.h>
#include <windowsx.h>
class TrayIcon
{
private:
	NOTIFYICONDATA nid;
	CHAR szInfoTitle[64];
	UINT uTimeout;
public:
	TrayIcon(HINSTANCE instance, HWND hWnd, UINT uIconId, LPCSTR lpIconName, UINT uMessage, LPCSTR lpTip);
	~TrayIcon();


	void SetDefaultInfoTitle(LPCSTR InfoTitle);
	void SetTimeout(UINT uTime);
	void ShowMessage(LPCSTR lpText, DWORD dwType, LPCSTR Title);
};