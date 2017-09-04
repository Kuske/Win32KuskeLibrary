#pragma once

#include <Windows.h>

void DrawLine(int x1, int y1, int x2, int y2, COLORREF color, int thick);						// ê¸Çï`âÊ
void DrawBox(int x1, int y1, int x2, int y2, COLORREF color, int thick, bool FillFlag);			// éläpÇï`âÊ
void DrawCircle(int x1, int y1, int radius, COLORREF color, int thick, bool FillFlag);			// â~Çï`âÊ
void DrawCircle(int x1, int y1, int x2, int y2, COLORREF color, int thick, bool FillFlag);		// â~Çï`âÊ
void DrawString(int x1, int y1, LPCSTR text, COLORREF color, int thick);						// ï∂éöóÒÇï`âÊ
void ClearScreen();																				// âÊñ è¡ãé

bool Kuske_Init(int width, int height, int startX, int startY);
void Kuske_End();
int GetEndStatus();
bool ProcessMessage();

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

		};

		static class MusicType
		{
		public:
			MusicType() = delete;
			~MusicType() = delete;




		private:

		};


		bool PlayMusic(int PlayMode);


	private:

		MCI_OPEN_PARMS mop;


	};


};