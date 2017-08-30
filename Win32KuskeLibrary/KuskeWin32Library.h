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