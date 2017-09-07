#include <Windows.h>
#include <Math.h>
#include <string>
#include "KuskeWin32Library.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow) {
	if (Kuske_Init(640, 480, 100, 300) == false) return -1;

	int count = 0;

	char str[3000];

	GraphicsData Lion;
	Lion = LoadGraph("hoge.png");

	while (ProcessMessage())
	{
		ClearScreen();



		count++;

		sprintf_s(str, "%d", count);

		DrawString(100, 300, TEXT(str), RGB(0, 0, 0), 5);

		DrawGraph(200, 200, Lion);

		ScreenFlip();

	}

	Kuske_End();
	return GetEndStatus();
}
