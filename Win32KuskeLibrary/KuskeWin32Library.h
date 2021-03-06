#pragma once

#include <Windows.h>

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