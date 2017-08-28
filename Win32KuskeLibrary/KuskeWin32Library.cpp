#include <Windows.h>
#include <cstdio>
#include <string>

#define GetHInstance() ((HINSTANCE)GetModuleHandle(0))

void DrawLine(int x1, int y1, int x2, int y2, COLORREF color, int thick);		// ê¸Çï`âÊ
void DrawBox(int x1, int y1, int x2, int y2, COLORREF color, int thick);		// éläpÇï`âÊ
void DrawCircle(int x1, int y1, int radius, COLORREF color, int thick);		// â~Çï`âÊ
void DrawString(int x1, int y1, LPCWSTR text, COLORREF color, int thick);			// ï∂éöóÒÇï`âÊ

bool Kuske_Init(int width, int height, int startX, int startY);
void Kuske_End();
int GetEndStatus();
bool ProcessMessage();

HDC hdc;
MSG Kuske_msg;

HWND K_Lib_hwnd;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	PAINTSTRUCT ps;
	K_Lib_hwnd = hwnd;
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
		hdc = GetDC(hwnd);
		ReleaseDC(hwnd, hdc);
		return 0;
	case WM_PAINT:
		BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
	}
	return DefWindowProc(hwnd, msg, wp, lp);
}

void DrawLine(int x1, int y1, int x2, int y2, COLORREF color, int thick)
{
	hdc = GetDC(K_Lib_hwnd);
	CreatePen(PS_SOLID, thick, color);
	ReleaseDC(K_Lib_hwnd, hdc);
}

void DrawBox(int x1, int y1, int x2, int y2, COLORREF color, int thick)
{
	hdc = GetDC(K_Lib_hwnd);
	CreatePen(PS_SOLID, thick, color);
	Rectangle(hdc, x1, y1, x2, y2);
	ReleaseDC(K_Lib_hwnd, hdc);
}

void DrawCircle(int x1, int y1, int radius, COLORREF color, int thick)
{
	hdc = GetDC(K_Lib_hwnd);
	CreatePen(PS_SOLID, thick, color);
	ReleaseDC(K_Lib_hwnd, hdc);
}

void DrawString(int x1, int y1, LPCWSTR text, COLORREF color, int thick)
{
	hdc = GetDC(K_Lib_hwnd);
	CreatePen(PS_SOLID, thick, color);
	TextOut(hdc, x1, y1, text, lstrlen(text));
	ReleaseDC(K_Lib_hwnd, hdc);
}

bool Kuske_Init(int width, int height, int startX, int startY)
{

	HWND hwnd;
	WNDCLASS winc;

	HINSTANCE hInstance = GetHInstance();

	winc.style = CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc = WndProc;
	winc.cbClsExtra = winc.cbWndExtra = 0;
	winc.hInstance = hInstance;
	winc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winc.hCursor = LoadCursor(NULL, IDC_ARROW);
	winc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName = NULL;
	winc.lpszClassName = TEXT("Kuske");

	if (!RegisterClass(&winc)) return 0;

	hwnd = CreateWindow(
		TEXT("Kuske"), TEXT("Kitty on your lap"),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		startX, startY,
		width, height,
		NULL, NULL,
		hInstance, NULL
	);

	if (hwnd == NULL) return false;

	K_Lib_hwnd = hwnd;

	return true;
}

// ÉEÉBÉìÉhÉEÇè¡Ç∑ÇæÇØ
void Kuske_End()
{
	DestroyWindow(K_Lib_hwnd);
}

int GetEndStatus()
{
	return (int)Kuske_msg.wParam;
}

// WindowsÇÃÉÅÉbÉZÅ[ÉWÇèàóùÇ∑ÇÈ falseÇæÇ¡ÇΩÇÁÇ∑ÇÆÇ…ï¬Ç∂ÇƒÇ≠ÇæÇ≥Ç¢
bool ProcessMessage()
{

	if (GetMessage(&Kuske_msg, NULL, 0, 0) == false) return false;

	DispatchMessage(&Kuske_msg);
	return true;
}
