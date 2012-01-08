#include <windows.h>
#include <windowsx.h>

#include "TrayIcon.h"

TrayIcon :: TrayIcon(HINSTANCE instance, HWND hWnd, UINT uIconId, LPCSTR lpIconName, UINT uMessage, LPCSTR lpTip)
{
	memset(&nid, 0, sizeof(nid));
	nid.cbSize = sizeof(nid);

	nid.hWnd = hWnd;
	nid.uID = uIconId;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = uMessage;
	nid.hIcon = LoadIcon(instance, lpIconName);
	lstrcpyn(nid.szTip, lpTip, sizeof(nid.szTip)/sizeof(nid.szTip[0]) );

	BOOL bSuccess = Shell_NotifyIcon(NIM_ADD, &nid);
}
TrayIcon :: ~TrayIcon()
{
	BOOL bSuccess = Shell_NotifyIcon(NIM_DELETE, &nid);
}

void TrayIcon :: SetDefaultInfoTitle(LPCSTR InfoTitle)
{
	lstrcpyn(szInfoTitle, InfoTitle, sizeof(szInfoTitle)/sizeof(szInfoTitle) );
}
void TrayIcon :: SetTimeout(UINT uTime)
{
	uTimeout = uTime;
	nid.uTimeout = 50000;

	BOOL bSuccess = Shell_NotifyIcon(NIM_MODIFY, &nid);
}
void TrayIcon :: ShowMessage(LPCSTR lpText, DWORD dwType, LPCSTR lpTitle)
{
	lstrcpyn(nid.szInfo, lpText, sizeof(nid.szInfo)/sizeof(nid.szInfo[0]));
	nid.uFlags = NIF_INFO;
	nid.dwInfoFlags = dwType;

	if(lpTitle == NULL)
		lstrcpyn( nid.szInfoTitle, szInfoTitle, sizeof(szInfoTitle)/sizeof(szInfoTitle) );
	else
		lstrcpyn( nid.szInfoTitle, lpTitle, sizeof(szInfoTitle)/sizeof(szInfoTitle) );

	BOOL bSuccess = Shell_NotifyIcon(NIM_MODIFY, &nid);
}