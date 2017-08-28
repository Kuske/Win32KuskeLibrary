#pragma once

#include <Windows.h>

void DrawLine(int x1, int y1, int x2, int y2, COLORREF color, int thick);		// ü‚ğ•`‰æ
void DrawBox(int x1, int y1, int x2, int y2, COLORREF color, int thick);		// lŠp‚ğ•`‰æ
void DrawCircle(int x1, int y1, int radius, COLORREF color, int thick);		// ‰~‚ğ•`‰æ
void DrawString(int x1, int y1, LPCSTR text, COLORREF color, int thick);		// •¶š—ñ‚ğ•`‰æ


bool Kuske_Init(int width, int height, int startX, int startY);
void Kuske_End();
int GetEndStatus();
bool ProcessMessage();

