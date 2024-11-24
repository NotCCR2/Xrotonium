int w = GetSystemMetrics(0), h = GetSystemMetrics(1);

typedef struct _HSL {
  float h;
  float s;
  float l;
} HSL, *PHSL, *LPHSL;

int signx = 1, signy = 1, signxcopy = 1, signycopy = 1;
int increment = 10;
int x = 10, y = 10;

COLORREF HSV(int crLength) {
    double H = fmod(crLength, 360);
    double S = 1.0;
    double V = 0.5;
    double C = (1.0-fabs(2.0*V-1.0)) * S;
    double X = C*(1.0-fabs(fmod(H/60.0, 2.0) - 1.0));
    double M = V - C / 2.0;
    double R, G, B;
    if (H < 60) {
        R = C; G = X, B = 0;
    }
    else if (H < 120) {
        R = X; G = C; B = 0;
    }
    else if (H < 180) {
        R = 0; G = C; B = X;
    }
    else if (H < 240) {
        R = 0; G = X; B = C;
    }
    else if (H < 300) {
        R = X; G = 0; B = C;
    }
    else {
        R = C; G = 0; B = X;
    }
    
    int crRed = static_cast<INT>((R + M) * 255);
    int crGreen = static_cast<INT>((G + M) * 255);
    int crBlue = static_cast<INT>((B + M) * 255);
    return RGB(crRed, crGreen, crBlue);
}

HSL rgbQuadRGB(RGBQUAD rgbQuad) { // I only rewrote this.
	HSL hsl;
	
	BYTE r = rgbQuad.rgbRed, g = rgbQuad.rgbGreen, b = rgbQuad.rgbBlue;
	float fr = (float)r/255.f;
	float fg = (float)g/255.f;
	float fb = (float)b/255.f;
	
	float minr = __min(__min(fr, fg), fb), maxr = __max(__max(fr, fg), fb);
	/* I compiled the thing above with a GCC compiler,
	So if you are on Visual Studio, change it to min and max */
	float delta = maxr-minr;
	float delr, delg, delb;
	
	float h = 0.f, s = 0.f, l = (float)((maxr+minr)/2.f);
	
	if (delta != 0.f) {
		s = l < 0.5f ? (float)(delta / (maxr + minr)) : (float)(delta / (2.f - maxr - minr));
		delr = (float)(((maxr - fr) / 6.f + (delta / 2.f)) / delta);
		delg = (float)(((maxr - fg) / 6.f + (delta / 2.f)) / delta);
		delb = (float)(((maxr - fb) / 6.f + (delta / 2.f)) / delta);
		
		if (fr == maxr) h = delb-delg;
		else if (fg == maxr) h = (1.f / 3.f) + delr - delb;
		else if (fb == maxr) h = (2.f / 3.f) + delg - delr;
		if (h < 0.f) h += 1.f;
		if (h > 1.f) h -= 1.f;
	}
	
	hsl.h = h;
	hsl.s = s;
	hsl.l = l;
	return hsl;
}

RGBQUAD hslRGB(HSL hsl) {
	RGBQUAD rgbq;
	float r = hsl.l, g = hsl.l, b = hsl.l;
	float h = hsl.h, s2 = hsl.s, l = hsl.l;
	float vh = (l <= 0.5f) ? (l*(1.f + s2)) : (l+s2-l*s2);
	
	float m, sv, frac, vsf, mid, mid2;
	int st;
	
	if (vh > 0.f) {
		m = l + l - vh;
		sv = (vh - m) / vh;
		h *= 6.f;
		st = (int)h;
		frac = h-st;
		vsf = vh*sv*frac;
		mid = m+vsf;
		mid2 = vh-vsf;
		switch(st) {
			case 0:
				r = vh;
				g = mid;
				b = m;
				break;
			case 1:
				r = mid2;
				g = vh;
				b = m;
				break;
			case 2:
				r = m;
				g = vh;
				b = mid;
				break;
			case 3:
				r = m;
				g = mid2;
				b = vh;
				break;
			case 4:
				r = mid;
				g = m;
				b = vh;
				break;
			case 5:
				r = vh;
				g = m;
				b = mid2;
				break;
        }
	}
	
	rgbq.rgbRed = (BYTE)(r*255.f);
	rgbq.rgbGreen = (BYTE)(g*255.f);
	rgbq.rgbBlue = (BYTE)(b*255.f);
	return rgbq;
}

DWORD CALLBACK Redraw(LPVOID lp) {
	while (true) {
		Sleep(500);
		RedrawWindow(NULL, NULL, NULL, RDW_INVALIDATE|RDW_ERASE|RDW_ALLCHILDREN);
	}
}

DWORD CALLBACK Redraw2(LPVOID lp) {
	while (true) {
		Sleep(1000);
		RedrawWindow(NULL, NULL, NULL, RDW_INVALIDATE|RDW_ERASE|RDW_ALLCHILDREN);
	}
}

DWORD CALLBACK RedrawRnd(LPVOID lp) {
	while (true) {
		Sleep(rand() % 200 + 800);
		RedrawWindow(NULL, NULL, NULL, RDW_INVALIDATE|RDW_ERASE|RDW_ALLCHILDREN);
	}
}

namespace GDI {
	DWORD WINAPI ANDDispRoto(LPVOID pvoid)
	{
 	double angle = 0.0;
 	while (true) {
		 
	 
	 HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
	 int wsize = w/4, hsize = h/4;
	 BITMAPINFO bmp = { sizeof(BITMAPINFO), wsize, hsize, 1, 32, BI_RGB };
	 LPRGBQUAD rgbq;
	 HBITMAP hbit = CreateDIBSection(hdc, &bmp, 0, (VOID**)&rgbq, NULL, 0);
	 SelectObject(mdc, hbit);
	 int t = 0;
	 StretchBlt(mdc, 0, 0, wsize, hsize, hdc, 0, 0, w, h, SRCCOPY);
	 for (int X = 0; X < wsize; X++) {
		 for (int Y = 0; Y < hsize; Y++) {
			 int cx = (X - (wsize/2)),
			 cy = (Y - (hsize/2));
			 int zx = cos(angle) * cx - sin(angle) * cy,
			 zy = sin(angle) * cx + cos(angle) * cy;
			 int xy = (zx+t)&(zy+t);
			 int index = Y * wsize + X;
			 rgbq[index].rgbRed += xy;
			 rgbq[index].rgbGreen += xy;
			 rgbq[index].rgbBlue += xy;

		 }
	 }
	 angle += 0.01;
	 StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wsize, hsize, SRCCOPY);
	 Sleep(10);
 }
 }
 
 	DWORD WINAPI ANDDispAbsRoto(LPVOID pvoid)
 	{
 	double angle = 0.0;
 	while (true) {
		 
	 
	 HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
	 int wsize = w/4, hsize = h/4;
	 BITMAPINFO bmp = { sizeof(BITMAPINFO), wsize, hsize, 1, 32, BI_RGB };
	 LPRGBQUAD rgbq;
	 HBITMAP hbit = CreateDIBSection(hdc, &bmp, 0, (VOID**)&rgbq, NULL, 0);
	 SelectObject(mdc, hbit);
	 int t = 0;
	 StretchBlt(mdc, 0, 0, wsize, hsize, hdc, 0, 0, w, h, SRCCOPY);
	 for (int X = 0; X < wsize; X++) {
		 for (int Y = 0; Y < hsize; Y++) {
			 int cx = abs(X - (wsize/2)),
			 cy = abs(Y - (hsize/2));
			 int zx = cos(angle) * cx - sin(angle) * cy,
			 zy = sin(angle) * cx + cos(angle) * cy;
			 int xy = (zx+t)&(zy+t);
			 int index = Y * wsize + X;
			 rgbq[index].rgbRed += xy;
			 rgbq[index].rgbGreen += xy;
			 rgbq[index].rgbBlue += xy;

		 }
	 }
	 angle += 0.01;
	 StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wsize, hsize, SRCCOPY);
	 Sleep(10);
 }
 }
 
 	DWORD WINAPI HalftoneANDRoto(LPVOID pvoid)
 	{
 	double angle = 0.0;
 	while (true) {
		 
	 
	 HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
	 int wsize = w/4, hsize = h/4;
	 BITMAPINFO bmp = { sizeof(BITMAPINFO), wsize, hsize, 1, 32, BI_RGB };
	 LPRGBQUAD rgbq;
	 HBITMAP hbit = CreateDIBSection(hdc, &bmp, 0, (VOID**)&rgbq, NULL, 0);
	 SelectObject(mdc, hbit);
	 int t = 0;
	 SetStretchBltMode(mdc, STRETCH_HALFTONE);
	 SetStretchBltMode(hdc, STRETCH_HALFTONE);
	 StretchBlt(mdc, 0, 0, wsize, hsize, hdc, 0, 0, w, h, SRCCOPY);
	 for (int X = 0; X < wsize; X++) {
		 for (int Y = 0; Y < hsize; Y++) {
			 int cx = (X - (wsize/2)),
			 cy = (Y - (hsize/2));
			 int zx = cos(angle) * cx - sin(angle) * cy,
			 zy = sin(angle) * cx + cos(angle) * cy;
			 int xy = (zx+t)&(zy+t);
			 int index = Y * wsize + X;
			 rgbq[index].rgbRed += xy;
			 rgbq[index].rgbGreen += xy;
			 rgbq[index].rgbBlue += xy;

		 }
	 }
	 angle += 0.01;
	 StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wsize, hsize, SRCCOPY);
	 Sleep(10);
 }
 }
 
 	DWORD WINAPI CustomANDRoto(LPVOID pvoid)
 	{
 	double angle = 0.0;
 	while (true) {
		 
	 
	 HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
	 int wsize = w/4, hsize = h/4;
	 BITMAPINFO bmp = { sizeof(BITMAPINFO), wsize, hsize, 1, 32, BI_RGB };
	 LPRGBQUAD rgbq;
	 HBITMAP hbit = CreateDIBSection(hdc, &bmp, 0, (VOID**)&rgbq, NULL, 0);
	 SelectObject(mdc, hbit);
	 int t = 0;
	 StretchBlt(mdc, 0, 0, wsize, hsize, hdc, 0, 0, w, h, SRCCOPY);
	 for (int X = 0; X < wsize; X++) {
		 for (int Y = 0; Y < hsize; Y++) {
			 int cx = (X - (wsize/2)),
			 cy = (Y - (hsize/2));
			 int zx = log2(angle) * cx - sin(angle) * cy,
			 zy = tan(angle) * cx + cos(angle) * cy;
			 int xy = (zx+t)&(zy+t);
			 int index = Y * wsize + X;
			 rgbq[index].rgbRed += xy;
			 rgbq[index].rgbGreen += xy;
			 rgbq[index].rgbBlue += xy;

		 }
	 }
	 angle += 0.01;
	 StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wsize, hsize, SRCCOPY);
	 Sleep(10);
 }
 }
 
 	DWORD WINAPI InitialScreenMovement(LPVOID pvoid)
 	{
	 	float intensity = 10.0;
	 	while (true) {
			 HDC hdc = GetDC(0);
			 for (int t = 0; t < intensity; t++) {
				 StretchBlt(hdc, rand() % 2 + 1, rand() % 2 + 1, w, h, hdc, rand() % 2 + 1, rand() % 2 + 1, w, h, SRCCOPY);
			 }
			 intensity -= 2.0;
			 if (intensity < 6.0) Sleep(250);
			 if (intensity < 3.0) Sleep(500);
			 if (intensity < 2.0) intensity = 10.0;
			 ReleaseDC(0, hdc);
			 Sleep(10);
		 }
	}
	
	DWORD WINAPI BrightPixelate(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
			BLENDFUNCTION ftn = { AC_SRC_OVER, 0 , 5, 0 };
			HBITMAP hbit = CreateCompatibleBitmap(hdc, w, h);
			SelectObject(mdc, hbit);
			int wsize = w/8, hsize = h/8;
			SetStretchBltMode(mdc, STRETCH_ORSCANS);
			SetStretchBltMode(hdc, STRETCH_ORSCANS);
			StretchBlt(mdc, 0, 0, wsize, hsize, hdc, 0, 0, w, h, SRCCOPY);
			AlphaBlend(hdc, 0, 0, w, h, mdc, 0, 0, wsize, hsize, ftn);
			ReleaseDC(0, hdc);
			Sleep(100);
		}
	}
 	
 	DWORD WINAPI HSLShader1(LPVOID pvoid)
 	{
		HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
		BITMAPINFO bmp = { { sizeof(BITMAPINFO), w, h, 1, 32, BI_RGB }, 0 };
		LPRGBQUAD rgbq = NULL;
		HSL hsl;
		HBITMAP hbit = CreateDIBSection(hdc, &bmp, DIB_RGB_COLORS, (LPVOID*)&rgbq, NULL, 0);
		SelectObject(mdc, hbit);
		int t = 0;
		while (true) {
			StretchBlt(mdc, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
			RGBQUAD mrgbq;
			for (int x = 0; x < w; x++) {
				for (int y = 0; y < h; y++) {
					int iIndex = y * w + x;
					int HslPreset = (int)((t*4)+(t^4)*ceill(20)); // egg
					mrgbq = rgbq[iIndex];
					hsl = rgbQuadRGB(mrgbq);
					hsl.h = fmod(HslPreset/400.f+y/h*0.2f, 1.f);
					rgbq[iIndex] = hslRGB(hsl);
				}
			}
			t++;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, w, h, SRCCOPY);
			Sleep(10);
		}
		return 0;
	}
	
	DWORD WINAPI RotatingTextouts(LPVOID pvoid)
	{
	 	float hfEscapement = 0.f;
	 	while (true) {
			 HDC hdc = GetDC(0);
			 LPCSTR lpArray[] = {
				 "addins", "apppatch",
				 "assembly", "Boot",
				 "Branding", "CbsTemp",
				 "Cursors", "debug",
				 "diagnostics", "Downloaded Program Files",
				 "Firmware", "Fonts",
				 "Help", "IdentityCRL",
				 "IME", "INF",
				 "Logs", "Media",
				 "OCR", "oem",
				 "Resources", "schemas",
				 "Setup", "Speech", 
				 "System32", "SystemTemp",
				 "SysWOW64", "TAPI",
				 "Temp", "twain_32",
				 "WaaS", "Web"
			 };
			 int ArrayItemCount = rand() % _countof(lpArray);
			 HFONT hfnt = CreateFontW(60, 0, hfEscapement + 1, 0, FW_HEAVY, rand() % 2, false, false, ANSI_CHARSET,
			 0, 0, 0, 0, L"Courier New");
			 SelectObject(hdc, hfnt);
			 LPCSTR Index = lpArray[ArrayItemCount];
			 SetTextColor(hdc, RGB(rand() % 0xff, rand() % 0xff, rand() % 0xff));
			 SetBkColor(hdc, RGB(rand() % 25, rand() % 25, rand() % 25));
			 TextOutA(hdc, rand() % w, rand() % h, Index, strlen(Index));
			 ReleaseDC(0, hdc);
			 hfEscapement -= 20;
			 Sleep(10);
		 }
	}
	
	DWORD WINAPI SrcPaintAndDisp(LPVOID pvoid)
	{ // Psychomania!
		while (true) {
			HDC hdc = GetDC(0);
			if (rand() % 25 == 20) {
				BitBlt(hdc, 5, 0, w, h, hdc, 0, 5, SRCPAINT);
			}
			if (rand() % 25 == 0) {
				BitBlt(hdc, 5, 0, w, h, hdc, 0, 5, SRCAND);
			}
			RedrawWindow(NULL, NULL, NULL, RDW_INVALIDATE|RDW_ERASE|RDW_ALLCHILDREN);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	/* DWORD WINAPI ScreenWarp(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			BitBlt(hdc, 0, 0, w, rand() % h, hdc, rand() % 3 - 1, 0, SRCCOPY);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	} */
	
	DWORD WINAPI OrPixelate(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
			HBITMAP hbit = CreateCompatibleBitmap(hdc, w, h);
			SelectObject(mdc, hbit);
			SetStretchBltMode(mdc, STRETCH_ORSCANS);
			SetStretchBltMode(hdc, STRETCH_ORSCANS);
			StretchBlt(mdc, 0, 0, w/5, h/5, hdc, 0, 0, w, h, SRCCOPY);
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, w/5, h/5, SRCCOPY);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI KaleidoscopeEffect(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			StretchBlt(hdc, 0, 0, w, h, hdc, w/2, 0, -w, h, SRCCOPY);
			StretchBlt(hdc, -w/2, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
			StretchBlt(hdc, 0, 0, w, h, hdc, 0, h/2, w, -h, SRCCOPY);
			StretchBlt(hdc, 0, -h/2, w, h, hdc, 0, 0, w, h, SRCCOPY);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI EllipsePatShake(LPVOID pvoid)
	{
		CreateThread(NULL, 0, Redraw, NULL, 0, 0);
		while (true) {
			HDC hdc = GetDC(0);
			HBRUSH hbsh = CreateSolidBrush(RGB(rand() % 0xff, rand() % 0xff, rand() % 0xff));
			SelectObject(hdc, hbsh);
			PatBlt(hdc, 0, 0, w, h, PATINVERT);
			BitBlt(hdc, rand() % 20, rand() % 20, w, h, hdc, rand() % 20, rand() % 20, SRCCOPY);
			int randx = rand() % w, randy = rand() % h;
			Rectangle(hdc, randx, randy, randx+100, randy+100);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI ErrorSphere(LPVOID pvoid)
	{
		float incrementB = 0.0;
		float angle = 0.0;
		while (true) {
			x += increment * signx;
			y += increment * signy;
			HDC hdc = GetDC(0);
			LOGPEN lopn = {PS_SOLID, {5, 5}, HSV(incrementB)};
			SelectObject(hdc, GetStockObject(NULL_BRUSH));
			HPEN hp = CreatePenIndirect(&lopn);
			SelectObject(hdc, hp);
			int radiusx = (cos(angle)*100)+50, radiusy =(sin(angle)*100)+50;
			Ellipse(hdc, x, y, x+150, y+150);
		 	DrawIcon(hdc, x+radiusx, y+radiusy, LoadIcon(NULL, IDI_ERROR));
		 	if (x > w) signx = -1;
		 	if (y > h) signy = -1;
		 	if (x == 0) signx = 1;
		 	if (y == 0) signy = 1;
		 	incrementB += M_PI_2;
		 	 angle += 1;
		 	 ReleaseDC(0, hdc);
		 	 Sleep(10);
		}
	}
	
	DWORD WINAPI ScreenLines(LPVOID pvoid)
	{
		CreateThread(NULL, 0, Redraw2, NULL, 0, 0);
		float angle = 0.0;
		while (true) {
			HDC hdc = GetDC(0);
			for (float t = 0; t < w + h; t += 0.9f) {
				int axis = tan(angle) * 100;
				BitBlt(hdc, 0, t, w, 1, hdc, axis, t, (rand() % 2)?SRCPAINT:SRCAND);
				angle += M_PI / 50;
			}
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI HSLSierpinski(LPVOID pvoid)
	{
		HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
		BITMAPINFO bmp = { { sizeof(BITMAPINFO), w, h, 1, 32, BI_RGB }, 0 };
		LPRGBQUAD rgbq = NULL;
		HSL hsl;
		HBITMAP hbit = CreateDIBSection(hdc, &bmp, DIB_RGB_COLORS, (LPVOID*)&rgbq, NULL, 0);
		SelectObject(mdc, hbit);
		int t = 0;
		while (true) {
			StretchBlt(mdc, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
			RGBQUAD mrgbq;
			for (int x = 0; x < w; x++) {
				for (int y = 0; y < h; y++) {
					int iIndex = y * w + x;
					int HslPreset = (int)((t*4)+(t^4)*128+(128*ceil(t^x|y)));
					mrgbq = rgbq[iIndex];
					hsl = rgbQuadRGB(mrgbq);
					hsl.h = fmod(HslPreset/400.f+y/h*0.2f, 1.f);
					rgbq[iIndex] = hslRGB(hsl);
				}
			}
			t++;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, w, h, SRCCOPY);
			Sleep(10);
		}
		return 0;
	}
	
	DWORD WINAPI ScreenMelter(LPVOID pvoid)
	{
		CreateThread(NULL, 0, RedrawRnd, NULL, 0, 0);
		while (true) {
			HDC hdc = GetDC(0);
			int random = rand() % w, randy = rand() % h;
			BitBlt(hdc, random, rand() % 100 - 50, 100, h, hdc, random, 0, SRCPAINT);
			BitBlt(hdc, rand() % 100 - 50, randy, w, 100, hdc, 0, randy, SRCPAINT);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI ScreenStatic(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
			BITMAPINFO bmp = { 40, w, h, 1, 24, BI_RGB };
			RGBTRIPLE* rgbt;
			HBITMAP hbit = CreateDIBSection(hdc, &bmp, DIB_RGB_COLORS, (LPVOID*)&rgbt, NULL, 0);
			SelectObject(mdc, hbit);
			BitBlt(mdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
			for (int t = 0; t < w * h; t++) {
				rgbt[t].rgbtRed += rand();
				rgbt[t].rgbtGreen += rand();
				rgbt[t].rgbtBlue += rand();
			}
			BitBlt(hdc, 0, 0, w, h, mdc, 0, 0, SRCCOPY);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI TrigonShake(LPVOID pvoid)
	{
		float angle = 0.0;
		while (true) {
			HDC hdc = GetDC(0);
			int radiusx = cos(angle) * 10, radiusy = sin(angle) * 10;
			BitBlt(hdc, radiusx, radiusy, w, h, hdc, 0, 0, SRCCOPY);
			ReleaseDC(0, hdc);
			angle += M_PI / 10;
			Sleep(10);
		}
	}
	
	DWORD WINAPI Rotator(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			HWND hwnd = GetDesktopWindow();
			RECT rect; GetWindowRect(hwnd, &rect);
			POINT lpt[3];
			// int factor = 10; (Why would I need this?)
			if (rand() % 2 == 0) {
				lpt[0].x = rect.left + 40; lpt[0].y = rect.top - 40;
				lpt[1].x = rect.right + 40; lpt[1].y = rect.top + 40;
				lpt[2].x = rect.left - 40; lpt[2].y = rect.bottom - 40;
			}
			else if (rand() % 2 == 1) {
				lpt[0].x = rect.left - 80; lpt[0].y = rect.top + 80;
				lpt[1].x = rect.right - 80; lpt[1].y = rect.top - 80;
				lpt[2].x = rect.left + 80; lpt[2].y = rect.bottom + 80;
			}
			PlgBlt(hdc, lpt, hdc, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, NULL, 0, 0);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
}
