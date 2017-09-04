#include <Windows.h>
#include <cstdio>
#include <string>
#include <vector>

#pragma comment(lib, "winmm.lib")

#define GetHInstance() ((HINSTANCE)GetModuleHandle(0))

void DrawLine(int x1, int y1, int x2, int y2, COLORREF color, int thick);						// 線を描画
void DrawBox(int x1, int y1, int x2, int y2, COLORREF color, int thick, bool FillFlag);			// 四角を描画
void DrawCircle(int x1, int y1, int radius, COLORREF color, int thick, bool FillFlag);			// 円を描画
void DrawCircle(int x1, int y1, int x2, int y2, COLORREF color, int thick, bool FillFlag);		// 円を描画
void DrawString(int x1, int y1, LPCSTR text, COLORREF color, int thick);						// 文字列を描画
void ClearScreen();																				// 画面消去

bool Kuske_Init(int width, int height, int startX, int startY);
void Kuske_End();
int GetEndStatus();
bool ProcessMessage();

namespace KuskeWin32Library {};

HDC hdc;
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

		private:
			static int WindowWidth;
			static int WindowHeight;
		};

	};

	int WindowStatus::Size::WindowWidth = 0;
	int WindowStatus::Size::WindowHeight = 0;



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


			std::string aif = "MPEGVideo";
			std::string aifc = "MPEGVideo";
			std::string aiff = "MPEGVideo";
			std::string asf = "MPEGVideo";
			std::string asx = "MPEGVideo";
			std::string au = "MPEGVideo";
			std::string avi = "avivideo";
			std::string cda = "CDAudio";
			std::string ivf = "MPEGVideo2";
			std::string m1v = "MPEGVideo";
			std::string m3u = "MPEGVideo";
			std::string Mid = "Sequencer";
			std::string mp2 = "MPEGVideo";
			std::string mp2v = "MPEGVideo";
			std::string mp3 = "MPEGVideo";
			std::string mpa = "MPEGVideo";
			std::string mpe = "MPEGVideo";
			std::string mpeg = "MPEGVideo";
			std::string mpg = "MPEGVideo";
			std::string mpv2 = "MPEGVideo";
			std::string rmi = "Sequencer";
			std::string snd = "MPEGVideo";
			std::string Wav = "WaveAudio";
			std::string wax = "MPEGVideo";
			std::string wm = "MPEGVideo";
			std::string wma = "MPEGVideo";
			std::string wmp = "MPEGVideo2";
			std::string wmv = "MPEGVideo";
			std::string wmx = "MPEGVideo";
			std::string wpl = "MPEGVideo";
			std::string wvx = "MPEGVideo";




		private:

		};


		bool PlayMusic(int PlayMode);
		

	private:

		MCI_OPEN_PARMS mop;


	};

	Music::Music(std::string FileName, std::string MusicType)
	{

		mop.lpstrElementName = FileName.c_str();
		mop.lpstrDeviceType = MusicType.c_str;
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	PAINTSTRUCT ps;
	K_Lib_hwnd = hwnd;
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
		if (FinishDrawFlag == true)
		{
			BeginPaint(hwnd, &ps);
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
	FinishDrawFlag = false;
	hdc = GetDC(K_Lib_hwnd);
	CreatePen(PS_SOLID, thick, color);
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	ReleaseDC(K_Lib_hwnd, hdc);
}

void DrawBox(int x1, int y1, int x2, int y2, COLORREF color, int thick, bool FillFlag)
{
	FinishDrawFlag = false;
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
	FinishDrawFlag = false;
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
	FinishDrawFlag = false;
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
	FinishDrawFlag = false;
	hdc = GetDC(K_Lib_hwnd);
	SetTextColor(hdc, color);
	SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, x1, y1, text, lstrlen(text));
	ReleaseDC(K_Lib_hwnd, hdc);
}

void ClearScreen()
{
	KuskeWin32Library::WindowSize MainWindowSize = KuskeWin32Library::WindowStatus::Size::GetWindowSize();
	DrawBox(0 - 1, 0 - 1, MainWindowSize.Width + 1, MainWindowSize.Height + 1, RGB(255, 255, 255), 1, true);
	FinishDrawFlag = true;
	InvalidateRect(K_Lib_hwnd, NULL, TRUE);
	UpdateWindow(K_Lib_hwnd);
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
		CW_USEDEFAULT, CW_USEDEFAULT,
		width, height,
		NULL, NULL,
		hInstance, NULL
	);

	if (hwnd == NULL) return false;

	K_Lib_hwnd = hwnd;

	return true;
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

	if (GetMessage(&Kuske_msg, NULL, 0, 0) == false) return false;

	DispatchMessage(&Kuske_msg);
	return true;
}
