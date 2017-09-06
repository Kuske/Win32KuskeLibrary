#include <Windows.h>
#include <Math.h>
#include <string>
#include "KuskeWin32Library.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow) {
	if (Kuske_Init(640, 480, 100, 300) == false) return -1;

	int count = 0;

	char str[3000];
	while (ProcessMessage())
	{
		ClearScreen();


		DrawBox(80, 0, 90, 300, RGB(0, 0, 0), 50, true);
		DrawBox(20, 50, 200, 65, RGB(0, 0, 0), 50, true);
		DrawString(count % 500, 100, TEXT("(^ _ ^)"), RGB(255, 0, 0), 5);


		count++;

		sprintf_s(str, "%d", count);

		DrawString(100, 300, TEXT(str), RGB(0, 0, 0), 5);

	}

	Kuske_End();
	return GetEndStatus();
}
