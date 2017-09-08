#include <Windows.h>
#include <cstdio>
#include <string>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stbi_image.h"

#pragma comment(lib, "winmm.lib")

#define GetHInstance() ((HINSTANCE)GetModuleHandle(0))

struct GraphicsData									// 画像の構造体
{
	int width;
	int height;
	unsigned char* data;
	int bpp;
};
void DrawLine(int x1, int y1, int x2, int y2, COLORREF color, int thick);						// 線を描画
void DrawBox(int x1, int y1, int x2, int y2, COLORREF color, int thick, bool FillFlag);			// 四角を描画
void DrawCircle(int x1, int y1, int radius, COLORREF color, int thick, bool FillFlag);			// 円を描画
void DrawCircle(int x1, int y1, int x2, int y2, COLORREF color, int thick, bool FillFlag);		// 円を描画
void DrawString(int x1, int y1, LPCSTR text, COLORREF color, int thick);						// 文字列を描画
void DrawPixel(int x, int y, COLORREF color, double alpha);										// 点の描画
void DrawPixel(int x, int y, int Red, int Green, int Blue, double alpha);						// 点の描画
GraphicsData LoadGraph(std::string FilePath);													// 画像の読み込み
void DrawGraph(int x, int y, GraphicsData Graph, double alpha);									// 画像の描画
void ClearScreen();																				// 画面消去

bool Kuske_Init(int width, int height, int startX, int startY);
void Kuske_End();
int GetEndStatus();
bool ProcessMessage();
void SetBackScreen();
void ScreenFlip();

namespace KuskeWin32Library {};

MSG Kuske_msg;

HWND K_Lib_hwnd;

static bool FinishDrawFlag = false;

static MCI_OPEN_PARMS mop;
static int counter = 0;

std::vector<MCI_OPEN_PARMS> K_Music_Loop_List;



// 後でクラスとしてまとめておいて
// 名前も変更して
namespace KuskeMusicLib
{
	
}


namespace KuskeWin32Library
{

	static class Time
	{
	public:
		Time() = delete;
		~Time() = delete;

		int GetLocalTime();

	private:

	};


	int Time::GetLocalTime()
	{



		return 0;
	}



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
			static WindowSize GetCliantSize();

			static void ReGetWindowSize();
			static void ReGetCliantSize();

		private:
			static int WindowWidth;
			static int WindowHeight;

			static int CliantWidth;
			static int CliantHeight;

		};

	};

	int WindowStatus::Size::WindowWidth = 0;
	int WindowStatus::Size::WindowHeight = 0;



	void WindowStatus::Size::SetWindowSize(int Width, int Height)
	{
		WindowWidth = Width;
		WindowHeight = Height;
	}

	WindowSize WindowStatus::Size::GetWindowSize()
	{

		WindowSize ThisWindowSize;
		ThisWindowSize.Height = WindowHeight;
		ThisWindowSize.Width = WindowWidth;
		return ThisWindowSize;
	}

	WindowSize WindowStatus::Size::GetCliantSize()
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

		WindowStatus::Size::WindowHeight = rc.bottom;
		WindowStatus::Size::WindowWidth = rc.right;
	}

	void WindowStatus::Size::ReGetCliantSize()
	{

		RECT rc;
		GetClientRect(K_Lib_hwnd, &rc);

		WindowStatus::Size::WindowHeight = rc.bottom;
		WindowStatus::Size::WindowWidth = rc.right;
	}

	//////////////////////////////////////////////////////////////////////////////


	class Music
	{
	public:
		Music(std::string FileName, std::string MusicType);
		~Music();

		static class PlayMusicMode
		{
		public:
			PlayMusicMode() = delete;
			~PlayMusicMode() = delete;

			static const int Stop = -1;		// 止める
			static const int Pause = 0;		// 一時停止
			static const int Play = 1;			// 再生
			static const int BackGround = 2;	// バックグラウンド
			static const int Loop = 3;			// バックグラウンド + ループ

		};

		static class MusicType
		{
		public:
			MusicType() = delete;
			~MusicType() = delete;


			std::string	aif		=	"MPEGVideo"	;
			std::string	aifc	=	"MPEGVideo"	;
			std::string	aiff	=	"MPEGVideo"	;
			std::string	asf		=	"MPEGVideo"	;
			std::string	asx		=	"MPEGVideo"	;
			std::string	au		=	"MPEGVideo"	;
			std::string	avi		=	"avivideo"	;
			std::string	cda		=	"CDAudio"	;
			std::string	ivf		=	"MPEGVideo2";
			std::string	m1v		=	"MPEGVideo"	;
			std::string	m3u		=	"MPEGVideo"	;
			std::string	Mid		=	"Sequencer"	;
			std::string	mp2		=	"MPEGVideo"	;
			std::string	mp2v	=	"MPEGVideo"	;
			std::string	mp3		=	"MPEGVideo"	;
			std::string	mpa		=	"MPEGVideo"	;
			std::string	mpe		=	"MPEGVideo"	;
			std::string	mpeg	=	"MPEGVideo"	;
			std::string	mpg		=	"MPEGVideo"	;
			std::string	mpv2	=	"MPEGVideo"	;
			std::string	rmi		=	"Sequencer"	;
			std::string	snd		=	"MPEGVideo"	;
			std::string	Wav		=	"WaveAudio"	;
			std::string	wax		=	"MPEGVideo"	;
			std::string	wm		=	"MPEGVideo"	;
			std::string	wma		=	"MPEGVideo"	;
			std::string	wmp		=	"MPEGVideo2";
			std::string	wmv		=	"MPEGVideo"	;
			std::string	wmx		=	"MPEGVideo"	;
			std::string	wpl		=	"MPEGVideo"	;
			std::string	wvx		=	"MPEGVideo"	;




		private:

		};


		bool PlayMusic(int PlayMode);
		

	private:

		MCI_OPEN_PARMS mop;


	};

	Music::Music(std::string FileName, std::string MusicType)
	{

		mop.lpstrElementName = FileName.c_str();
		mop.lpstrDeviceType = MusicType.c_str();
		mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD_PTR)&mop);

		//MCI_PLAY_PARMS構造体の設定
		mop.dwCallback = (DWORD)K_Lib_hwnd;

	}

	Music::~Music()
	{
	}

	bool Music::PlayMusic(int PlayMode)
	{
		switch (PlayMode)
		{
		case PlayMusicMode::Stop:		// 止める

			mciSendCommand(mop.wDeviceID, MCI_STOP, 0, (DWORD)&mop);

			break;

		case PlayMusicMode::Pause:		// 一時停止

			mciSendCommand(mop.wDeviceID, MCI_PAUSE, 0, (DWORD)&mop);

			break;
		case PlayMusicMode::Play:			// 再生

			mciSendCommand(mop.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)&mop);

			break;
		case PlayMusicMode::BackGround:	// バックグラウンド

			mciSendCommand(mop.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)&mop);

			break;
		case PlayMusicMode::Loop:			// バックグラウンド + ループ

			mciSendCommand(mop.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)&mop);

			break;
		}

		return true;
	}




}

HDC hMemDC;
HBITMAP hBitmap;

bool WindowUpdateFlag = false;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	PAINTSTRUCT ps;
	// K_Lib_hwnd = hwnd;
		//メモリデバイスコンテキストを作る
	HDC hdc = GetDC(K_Lib_hwnd);
	bool tmp = false;
	switch (msg) {
	case WM_CREATE:
		mop.lpstrDeviceType = "MPEGVideo";
		mop.lpstrElementName = "桜スキップ.mp3";
		mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD_PTR)&mop);
		//MCI_PLAY_PARMS構造体の設定
		mop.dwCallback = (DWORD)hwnd;



		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		Kuske_End();
		ExitProcess(0);
		return 0;
	case WM_SIZE:
		KuskeWin32Library::WindowStatus::Size::ReGetWindowSize();
		return 0;
	case WM_LBUTTONDOWN:
		if(counter == 0)mciSendCommand(mop.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD_PTR)&mop);
		else if (counter % 2 == 1) mciSendCommand(mop.wDeviceID, MCI_PAUSE, 0, 0);
		else mciSendCommand(mop.wDeviceID, MCI_RESUME, 0, 0);

		counter++;


		return 0;

	case WM_RBUTTONDOWN:

		mciSendCommand(mop.wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, 0);
		mciSendCommand(mop.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)&mop);

		return 0;

	case WM_PAINT:
		if (WindowUpdateFlag = true)
		{

			BeginPaint(hwnd, &ps);
			//表画面へ転送
			BitBlt(hdc, 0, 0, KuskeWin32Library::WindowStatus::Size::GetWindowSize().Width, KuskeWin32Library::WindowStatus::Size::GetWindowSize().Height, hMemDC, 0, 0, SRCCOPY);
			EndPaint(hwnd, &ps);
		}



	case MM_MCINOTIFY:    //再生(正常終了した時だけ)
		if (wp != MCI_NOTIFY_SUCCESSFUL)
		{
			// 異常終了
			return 0;
		}

		mciSendCommand(mop.wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, 0);
		mciSendCommand(mop.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)&mop);
	}
	return DefWindowProc(hwnd, msg, wp, lp);
}

void DrawLine(int x1, int y1, int x2, int y2, COLORREF color, int thick)
{
	// HDC hMemDC = GetDC(K_Lib_hwnd);
	HPEN my_pen = CreatePen(PS_SOLID, thick, color);
	MoveToEx(hMemDC, x1, y1, NULL);
	LineTo(hMemDC, x2, y2);
	ReleaseDC(K_Lib_hwnd, hMemDC);
	DeleteObject(my_pen);
}

void DrawBox(int x1, int y1, int x2, int y2, COLORREF color, int thick, bool FillFlag)
{
	// HDC hMemDC = GetDC(K_Lib_hwnd);
	HBRUSH brush;
	HPEN my_pen = CreatePen(PS_SOLID, thick, color);
	SelectObject(hMemDC, my_pen);
	if (FillFlag == true)
	{
		SelectObject(hMemDC, brush = CreateSolidBrush(color));
		Rectangle(hMemDC, x1, y1, x2, y2);
		ReleaseDC(K_Lib_hwnd, hMemDC);
		DeleteObject(my_pen);
		DeleteObject(brush);
	}
	else
	{
		SelectObject(hMemDC, GetStockObject(NULL_BRUSH));
		Rectangle(hMemDC, x1, y1, x2, y2);
		ReleaseDC(K_Lib_hwnd, hMemDC);
		DeleteObject(my_pen);
	}



}

void DrawCircle(int x1, int y1, int radius, COLORREF color, int thick, bool FillFlag)
{
	// HDC hMemDC = GetDC(K_Lib_hwnd);
	HBRUSH brush;
	HPEN my_pen = CreatePen(PS_SOLID, thick, color);
	if (FillFlag == true)
	{
		SelectObject(hMemDC, brush = CreateSolidBrush(color));

		Ellipse(hMemDC, x1, y1, x1 + radius, y1 + radius);

		ReleaseDC(K_Lib_hwnd, hMemDC);
		DeleteObject(my_pen);
		DeleteObject(brush);
	}
	else
	{
		SelectObject(hMemDC, GetStockObject(NULL_BRUSH));

		Ellipse(hMemDC, x1, y1, x1 + radius, y1 + radius);

		// ReleaseDC(K_Lib_hwnd, hMemDC);
		DeleteObject(my_pen);
	}
	ReleaseDC(K_Lib_hwnd, hMemDC);
}

void DrawCircle(int x1, int y1, int x2, int y2, COLORREF color, int thick, bool FillFlag)
{
	// HDC hMemDC = GetDC(K_Lib_hwnd);
	HBRUSH brush;
	HPEN my_pen = CreatePen(PS_SOLID, thick, color);
	if (FillFlag == true)
	{
		SelectObject(hMemDC, brush = CreateSolidBrush(color));

		Ellipse(hMemDC, x1, y1, x2, y2);

		// ReleaseDC(K_Lib_hwnd, hMemDC);
		DeleteObject(my_pen);
		DeleteObject(brush);
	}
	else
	{
		SelectObject(hMemDC, GetStockObject(NULL_BRUSH));

		Ellipse(hMemDC, x1, y1, x2, y2);

		// ReleaseDC(K_Lib_hwnd, hMemDC);
		DeleteObject(my_pen);
	}
	ReleaseDC(K_Lib_hwnd, hMemDC);
}

void DrawString(int x1, int y1, LPCSTR text, COLORREF color, int thick)
{
	// HDC hMemDC = GetDC(K_Lib_hwnd);
	SetTextColor(hMemDC, color);
	SetBkMode(hMemDC, TRANSPARENT);
	TextOut(hMemDC, x1, y1, text, lstrlen(text));
	// ReleaseDC(K_Lib_hwnd, hMemDC);
}

void DrawPixel(int x, int y, COLORREF color, double alpha)
{

	// HDC hMemDC = GetDC(K_Lib_hwnd);
	COLORREF PixelColor;
	if (alpha < 0.95 && 0.05 < alpha)
	{
		// 透明対応する

		PixelColor = GetPixel(hMemDC, x, y);
		int Red = GetRValue(PixelColor);
		int Green = GetGValue(PixelColor);
		int Blue = GetBValue(PixelColor);
		int Add_Red = GetRValue(color);
		int Add_Green = GetGValue(color);
		int Add_Blue = GetBValue(color);

		SetPixel(hMemDC, x, y, RGB(Red * (1.0 - alpha) + Add_Red * (alpha), Green * (1.0 - alpha) + Add_Green * (alpha), Blue * (1.0 - alpha) + Add_Blue * (alpha)));

	}
	else
	{
		// そのまま描画
		if (alpha >= 0.95)
			SetPixel(hMemDC, x, y, color);
	}

	ReleaseDC(K_Lib_hwnd, hMemDC);


}
void DrawPixel(int x, int y, int Red, int Green, int Blue, double alpha)
{

	// HDC hMemDC = GetDC(K_Lib_hwnd);
	COLORREF PixelColor;
	if (alpha < 0.95 && 0.05 < alpha)
	{
		// 透明対応する

		PixelColor = GetPixel(hMemDC, x, y);
		int Add_Red = GetRValue(PixelColor);
		int Add_Green = GetGValue(PixelColor);
		int Add_Blue = GetBValue(PixelColor);

		SetPixel(hMemDC, x, y, RGB(Red * (1.0 - alpha) + Add_Red * (alpha), Green * (1.0 - alpha) + Add_Green * (alpha), Blue * (1.0 - alpha) + Add_Blue * (alpha)));

	}
	else
	{
		// そのまま描画
		if (alpha >= 0.95)
			SetPixel(hMemDC, x, y, RGB(Red, Green, Blue));
	}

	ReleaseDC(K_Lib_hwnd, hMemDC);


}


GraphicsData LoadGraph(std::string FilePath)
{

	GraphicsData my_graph;
	// ファイルを読み込み、画像データを取り出す
	//   最後の引数でピクセルあたりのバイト数を強制できる
	my_graph.data = stbi_load(FilePath.c_str(), &my_graph.width, &my_graph.height, &my_graph.bpp, 4);

	return my_graph;

}

void DrawGraph(int x, int y, GraphicsData Graph, double alpha)
{

	for (int Loop_y = 0; Loop_y < Graph.width; ++Loop_y)
	{
		for (int Loop_x = 0; Loop_x < Graph.height; ++Loop_x)
		{

			int pos = (Loop_y * Graph.width + Loop_x) * 4;

			int Red = Graph.data[pos + 0];
			int Green = Graph.data[pos + 1];
			int Blue = Graph.data[pos + 2];
			double alpha_graph = Graph.data[pos + 3];

			DrawPixel(Loop_x + x, Loop_y + y, RGB(Red, Green, Blue), (alpha_graph / 255.0) * alpha);
		}

	}

	ProcessMessage();

}


void ClearScreen()
{
	int x, y;
	x = KuskeWin32Library::WindowStatus::Size::GetWindowSize().Width;
	y = KuskeWin32Library::WindowStatus::Size::GetWindowSize().Height;
	DrawBox(-1, -1, x + 1, y + 1, RGB(255, 255, 255), 1, true);

}


bool Kuske_Init(int width, int height, int startX, int startY)
{

	HWND hwnd;
	WNDCLASS winc;

	HINSTANCE hInstance = GetHInstance();

	KuskeWin32Library::WindowStatus::Size::SetWindowSize(width, height);

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

	KuskeWin32Library::WindowStatus::Size::ReGetWindowSize();

	return true;
}

void SetBackScreen()
{
	HDC hdc = GetDC(K_Lib_hwnd);

	auto DrawWindowSize = KuskeWin32Library::WindowStatus::Size::GetWindowSize();

	hBitmap = CreateCompatibleBitmap(hdc, DrawWindowSize.Width, DrawWindowSize.Height);
	hMemDC = CreateCompatibleDC(hdc);
	ReleaseDC(K_Lib_hwnd, hdc);
	SelectObject(hMemDC, hBitmap);
	DeleteObject(hBitmap);
}

// ウィンドウを消すだけ
void Kuske_End()
{
	DestroyWindow(K_Lib_hwnd);
}

int GetEndStatus()
{
	return (int)Kuske_msg.wParam;
}

// Windowsのメッセージを処理する falseだったらすぐに閉じてください
bool ProcessMessage()
{
	
	if (PeekMessage(&Kuske_msg, NULL, 0, 0, PM_REMOVE)) {
		if (Kuske_msg.message == WM_QUIT) return false;
		DispatchMessage(&Kuske_msg);
	}

	WindowUpdateFlag = false;
	// if (GetMessage(&Kuske_msg, NULL, 0, 0) == false) return false;
	// 
	// DispatchMessage(&Kuske_msg);
	 return true;
}

void ScreenFlip()
{

	HDC hdc = GetDC(K_Lib_hwnd);
	WindowUpdateFlag = true;

	InvalidateRect(K_Lib_hwnd, NULL, TRUE);



}
