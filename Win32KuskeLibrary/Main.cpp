#include <Windows.h>
#include "KuskeWin32Library.h"
#include <Math.h>
#include <string>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow) {
	if (Kuske_Init(640, 480, 1000, 300) == false) return -1;

	std::string str = "Hello";

	int count = 0;

	while (ProcessMessage())
	{
		ClearScreen();
		DrawBox(80, 0, 90, 300, RGB(0, 0, 0), 50, true);
		DrawBox(20, 50, 200, 65, RGB(0, 0, 0), 50, true);
		DrawString(count, 100, TEXT("(^ _ ^)"), RGB(255, 0, 0), 5);

		count++;

		Sleep(50);

	}

	Kuske_End();
	return GetEndStatus();
}