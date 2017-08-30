#include <Windows.h>
#include <cstdio>
#include <string>

#pragma comment(lib, "winmm.lib")

#define GetHInstance() ((HINSTANCE)GetModuleHandle(0))



using namespace KuskeWin32Library;

void DrawLine(int x1, int y1, int x2, int y2, COLORREF color, int thick);						// ����`��
void DrawBox(int x1, int y1, int x2, int y2, COLORREF color, int thick, bool FillFlag);			// �l�p��`��
void DrawCircle(int x1, int y1, int radius, COLORREF color, int thick, bool FillFlag);			// �~��`��
void DrawCircle(int x1, int y1, int x2, int y2, COLORREF color, int thick, bool FillFlag);		// �~��`��
void DrawString(int x1, int y1, LPCSTR text, COLORREF color, int thick);						// �������`��
void ClearScreen();																				// ��ʏ���

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
	case WM_CREATE:
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_SIZE:
		WindowStatus::Size::ReGetWindowSize();
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

namespace KuskeWin32Library
{

	struct WindowSize
	{
		int Width;
		int Height;
	};


	static class WindowStatus
	{
	public:
		WindowStatus() = delete;
		~WindowStatus() = delete;

		static class Size
		{
		public:
			Size() = delete;
			~Size() = delete;

			static void SetWindowSize(int width, int height);
			static WindowSize GetWindowSize();

			static void ReGetWindowSize();

		};


	private:
		static int WindowWidth;
		static int WindowHeight;
	};

	void WindowStatus::Size::SetWindowSize(int Width, int Height)
	{

	}

	WindowSize WindowStatus::Size::GetWindowSize()
	{

		WindowSize ThisWindowSize;
		ThisWindowSize.Height = WindowHeight;
		ThisWindowSize.Width = WindowWidth;
		return ThisWindowSize;
	}

	void WindowStatus::Size::ReGetWindowSize()
	{

		RECT rc;
		GetClientRect(K_Lib_hwnd, &rc);

		WindowHeight = rc.bottom;
		WindowWidth = rc.right;
	}



}


void DrawLine(int x1, int y1, int x2, int y2, COLORREF color, int thick)
{
	hdc = GetDC(K_Lib_hwnd);
	CreatePen(PS_SOLID, thick, color);
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	ReleaseDC(K_Lib_hwnd, hdc);
}

void DrawBox(int x1, int y1, int x2, int y2, COLORREF color, int thick, bool FillFlag)
{
	if (FillFlag == true)
	{
		LOGBRUSH my_brush;
		my_brush.lbStyle = BS_SOLID;
		my_brush.lbColor = color;
		SelectObject(hdc, CreateBrushIndirect(&my_brush));
	}
	hdc = GetDC(K_Lib_hwnd);
	CreatePen(PS_SOLID, thick, color);
	Rectangle(hdc, x1, y1, x2, y2);
	ReleaseDC(K_Lib_hwnd, hdc);
}

void DrawCircle(int x1, int y1, int radius, COLORREF color, int thick, bool FillFlag)
{
	if (FillFlag == true)
	{
		LOGBRUSH my_brush;
		my_brush.lbStyle = BS_SOLID;
		my_brush.lbColor = color;
		SelectObject(hdc, CreateBrushIndirect(&my_brush));
	}
	hdc = GetDC(K_Lib_hwnd);
	CreatePen(PS_SOLID, thick, color);
	Ellipse(hdc, x1, y1, x1 + radius, y1 + radius);
	ReleaseDC(K_Lib_hwnd, hdc);
}

void DrawCircle(int x1, int y1, int x2, int y2, COLORREF color, int thick, bool FillFlag)
{
	if (FillFlag == true)
	{
		LOGBRUSH my_brush;
		my_brush.lbStyle = BS_SOLID;
		my_brush.lbColor = color;
		SelectObject(hdc, CreateBrushIndirect(&my_brush));
	}
	hdc = GetDC(K_Lib_hwnd);
	CreatePen(PS_SOLID, thick, color);
	Ellipse(hdc, x1, y1, x2, y2);
	ReleaseDC(K_Lib_hwnd, hdc);
}

void DrawString(int x1, int y1, LPCSTR text, COLORREF color, int thick)
{
	hdc = GetDC(K_Lib_hwnd);
	SetTextColor(hdc, color);
	SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, x1, y1, text, lstrlen(text));
	ReleaseDC(K_Lib_hwnd, hdc);
}

void ClearScreen()
{
	InvalidateRect(K_Lib_hwnd, NULL, TRUE);
	KuskeWin32Library::WindowSize MainWindowSize = KuskeWin32Library::WindowStatus::Size::GetWindowSize();
	DrawBox(0 - 1, 0 - 1, MainWindowSize.Width + 1, MainWindowSize.Height + 1, RGB(255, 255, 255), 1, true);
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

// �E�B���h�E����������
void Kuske_End()
{
	DestroyWindow(K_Lib_hwnd);
}

int GetEndStatus()
{
	return (int)Kuske_msg.wParam;
}

// Windows�̃��b�Z�[�W���������� false�������炷���ɕ��Ă�������
bool ProcessMessage()
{

	if (GetMessage(&Kuske_msg, NULL, 0, 0) == false) return false;

	DispatchMessage(&Kuske_msg);
	return true;
}
