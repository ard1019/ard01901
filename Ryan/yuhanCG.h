#pragma once

#include <windows.h>
#include <cmath>

// ���뺸�� �׸��� �Լ� ����
void DrawBonobono(HWND hWnd, HDC hdc, int blink);

// ���̾� �׸��� �Լ� ����
void DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom);

void DrawRectangle(HWND hWnd, HDC hdc, int left, int top, int right, int bottom);

void DrawEllipse(HWND hWnd, HDC hdc, int radius, POINT center);