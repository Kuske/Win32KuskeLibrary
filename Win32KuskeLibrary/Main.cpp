#include <Windows.h>
#include <Math.h>
#include <string>
#include "KuskeWin32Library.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow) {
	if (Kuske_Init(640, 480, 100, 300) == false) return -1;

	int count = 0;

	char str[3000];

	int MapData[16][16];

	GraphicsData Lion;
	Lion = LoadGraph("tiger-png-9.png");

	SetBackScreen();

	while (ProcessMessage())
	{
		ClearScreen();



		count++;

		sprintf_s(str, "%d", count);
		DrawGraph(0, 0, Lion, 1.0);

		DrawString(400, 400, TEXT(str), RGB(0, 0, 0), 5);

		ScreenFlip();

	}

	Kuske_End();
	return GetEndStatus();
}
