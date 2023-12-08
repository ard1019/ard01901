#pragma once

#include <windows.h>
#include <cmath>

// 보노보노 그리기 함수 선언
void DrawBonobono(HWND hWnd, HDC hdc, int blink);

// 라이언 그리기 함수 선언
void DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom);

void DrawRectangle(HWND hWnd, HDC hdc, int left, int top, int right, int bottom);

void DrawEllipse(HWND hWnd, HDC hdc, int radius, POINT center);