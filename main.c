#include <windows.h>
#ifdef Menu
#define BIG 1<<22
#define Invisible
#else
#define BIG 1<<27
#endif
NOTIFYICONDATA nid = {sizeof(nid)};
void remove_icon(void) {Shell_NotifyIcon(2, &nid);}
#if 0 // this is for the menu which is not fully implemented
void add_to_startup(void) {
	HKEY hKey;
    char path[MAX_PATH];
	GetModuleFileName(0, path, sizeof(path));
	RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hKey);
	RegSetValueEx(hKey, "RunCat", 0, 1, (BYTE *) path, strlen(path) + 1);
	RegCloseKey(hKey);
}
#endif
int main(void) {
	int i = 0, j = 0;
	char path[10] = "cat\\*.ico"; // path to the icons
	HMENU hMenu = NULL;
	nid.uFlags = 7;
	nid.uID = 1;
#ifdef Invisible
	ShowWindow(FindWindowA("ConsoleWindowClass", 0), 0); // hide console window
#endif
#ifdef Menu
	POINT p; // mouse position
	hMenu = CreatePopupMenu(); // create menu
	AppendMenu(hMenu, 0, 1, "Exit"); // add exit button to menu
	AppendMenu(hMenu, 0, 2, "Add to startup"); // add add_to_startup button to menu
#endif
	nid.hWnd = CreateWindowEx(0, "STATIC", "", 1<<31, 0, 0, 0, 0, 0, hMenu, 0, 0); // make icon focused
	Shell_NotifyIcon(0, &nid); // add icon to tray
	atexit(remove_icon); // remove icon on exit (won't work since the window is hidden when not in DEBUG mode)
	while (1) { // main loop
		while (i++<BIG) // delay loop
#ifdef Menu
		{
			if (GetAsyncKeyState(1) || GetAsyncKeyState(2)) { // if mouse is clicked
					GetCursorPos(&p); // get mouse position
					TrackPopupMenu(hMenu, 2, p.x, p.y, 0, nid.hWnd, 0); // show menu near the mouse
					Sleep(100);
			}
		}
#else
		;
#endif
		path[4] = j+++'0'; // change icon path
		i %= BIG; // reset
		j %= 5; // reset
		nid.hIcon = (HICON)LoadImage(0, path, 1, 0, 0, LR_LOADFROMFILE); // load icon from path
		Shell_NotifyIcon(1, &nid); // update icon (will be shown on the tray)
	}
	return 0; // never reached
}