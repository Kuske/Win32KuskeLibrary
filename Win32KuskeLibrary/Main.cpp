#include <Windows.h>
#include "KuskeWin32Library.h"
#include <Math.h>
#include <string>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow) {
	if (Kuske_Init(640, 480, 1000, 300) == false) return -1;

	std::string str = "Hello";

	while (ProcessMessage())
	{
		DrawBox(20, 20, 80, 180, RGB(255, 100, 100), 5);
		DrawString(50, 50, TEXT("Hello"), RGB(255, 0, 0), 10);
	}

	Kuske_End();
	return GetEndStatus();
}