#define _WIN32_WINNT 0x0501
#include <windows.h>
#ifdef Menu
#define BIG 8
void add_to_startup(void) {
	HKEY hKey;
	char path[MAX_PATH];
	GetModuleFileName(0, path, sizeof(path));
	RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hKey);
	RegSetValueEx(hKey, "RunCat", 0, 1, (BYTE *) path, strlen(path) + 1);
	RegCloseKey(hKey);
}
#else
#define BIG 10
#endif
NOTIFYICONDATA nid = {sizeof(nid)};
void remove_icon(void) {Shell_NotifyIcon(2, &nid);}
static float cpu_load(unsigned long long x, unsigned long long y) {
	static unsigned long long px = 0;
	static unsigned long long py = 0;
	unsigned long long dx = y - px;
	unsigned long long dy = x - py;
	float ret = 1.0f - ((dx > 0) ? ((float)dy) / dx : 0);
	px = y;
	py = x;
	return ret;
}
static unsigned long long ft2int(const FILETIME ft) {return (((unsigned long long)(ft.dwHighDateTime))<<32)|((unsigned long long)ft.dwLowDateTime);}
int main(void) {
	int i = 0, j = 0;
	HMENU hMenu = NULL;
	HINSTANCE hInstance = GetModuleHandle(0);
	nid.uFlags = 7;
	nid.uID = 1;
#ifdef Menu
	ShowWindow(FindWindowA("ConsoleWindowClass", 0), 0); // hide console window
	POINT p; // mouse position
	hMenu = CreatePopupMenu(); // create menu
	AppendMenu(hMenu, 0, 1, "Exit"); // add exit button to menu
	AppendMenu(hMenu, 0, 2, "Add to startup"); // add add_to_startup button to menu
	AppendMenu(hMenu, 0, -1, "Close"); // close button
#endif
	nid.hWnd = CreateWindowEx(0, "STATIC", "", 1<<31, 0, 0, 0, 0, 0, hMenu, 0, 0); // make icon focused
	Shell_NotifyIcon(0, &nid); // add icon to tray
	atexit(remove_icon); // remove icon on exit
	while (1) { // main loop
		while (i++<BIG) { // delay loop
#ifdef Menu
			if ((GetAsyncKeyState(1) | GetAsyncKeyState(2)) & 1) { // if mouse is released
				GetCursorPos(&p); // get mouse position
				HWND hWnd = FindWindowEx(FindWindow("Shell_TrayWnd", 0), 0, "TrayNotifyWnd", 0);
				HWND hWnd2 = FindWindowEx(hWnd, 0, "SysPager", 0);
				if (WindowFromPoint(p) == (hWnd2 ? FindWindowEx(hWnd2, 0, "ToolbarWindow32", 0) : FindWindowEx(hWnd, 0, "ToolbarWindow32", 0))) {
					SetForegroundWindow(nid.hWnd);
					switch(TrackPopupMenu(hMenu, TPM_RETURNCMD, p.x, p.y, 0, nid.hWnd, 0)) { // show menu near mouse
						case 1:
							exit(0);
						case 2:
							add_to_startup(); // no break intended
						default:
							Sleep(100);
					}
				}
			}
#endif
			FILETIME idleTime, kernelTime, userTime;
			Sleep(cpu_load(ft2int(idleTime), ft2int(kernelTime) + ft2int(userTime)));
		}
		i %= BIG; // reset
		j = (j + 1) % 5; // cycle through the icons
		nid.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(j)); // load icon (intentionally not using icon array)
		Shell_NotifyIcon(1, &nid); // update icon (will be shown on the tray)
	}
	return 0; // never reached
}