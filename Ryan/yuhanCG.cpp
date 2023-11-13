#include "yuhanCG.h"

void DrawBonobono(HWND hwnd, HDC hdc, int blink)
{
    RECT rc = { 16, 90, 800 - 32, 480 - 56 };
    // 배경을 그립니다.
    if (blink)
    {
        HBRUSH bBrush = CreateSolidBrush(RGB(0, 0, 0)); // 배경색 지정
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 240, 200)); // 배경색 지정
        FillRect(hdc, &rc, hBrush);
        DeleteObject(hBrush);
        HBRUSH hEllipseBrush = CreateSolidBrush(RGB(127, 200, 255));
        HBRUSH ddllipseBrush = CreateSolidBrush(RGB(255, 150, 255));// 분홍색
        HBRUSH xxllipseBrush = CreateSolidBrush(RGB(255, 255, 255));// 하얀색
        SelectObject(hdc, hEllipseBrush); // 파랑색 브러시 선택
        Ellipse(hdc, 250, 100, 525, 375); // 얼굴
        SelectObject(hdc, ddllipseBrush); // 파랑색 브러시 선택
        Ellipse(hdc, 375, 250, 405, 310); // 입
        SelectObject(hdc, xxllipseBrush); // 흰색 브러시 선택
        Ellipse(hdc, 350, 235, 390, 275); // 입술
        Ellipse(hdc, 390, 235, 430, 275); // 입술
        SelectObject(hdc, bBrush);
        Ellipse(hdc, 275, 215, 285, 240); // 눈
        Ellipse(hdc, 490, 215, 500, 240); // 눈2
        SelectObject(hdc, xxllipseBrush);
        Ellipse(hdc, 277, 220, 283, 230); // 왼쪽 눈동자
        Ellipse(hdc, 492, 220, 498, 230); // 오른쪽 눈동자
        SelectObject(hdc, bBrush);
        Ellipse(hdc, 375, 225, 405, 250); // 코
        //수염
        MoveToEx(hdc, 370, 250, NULL);
        LineTo(hdc, 330, 230);
        MoveToEx(hdc, 370, 260, NULL);
        LineTo(hdc, 330, 280);
        MoveToEx(hdc, 410, 250, NULL);
        LineTo(hdc, 450, 230);
        MoveToEx(hdc, 410, 260, NULL);
        LineTo(hdc, 450, 280);
    }
    else
    {
        HDC hdc = GetDC(hwnd);
        RECT rect;
        GetClientRect(hwnd, &rect);
        HBRUSH bBrush = CreateSolidBrush(RGB(0, 0, 0)); // 배경색 지정
        HBRUSH hEllipseBrush = CreateSolidBrush(RGB(127, 200, 255));
        HBRUSH ddllipseBrush = CreateSolidBrush(RGB(255, 150, 255));// 분홍색
        HBRUSH xxllipseBrush = CreateSolidBrush(RGB(255, 255, 255));// 하얀색
        SelectObject(hdc, hEllipseBrush); // 파랑색 브러시 선택
        Ellipse(hdc, 250, 100, 525, 375);// 얼굴
        SelectObject(hdc, ddllipseBrush); // 파랑색 브러시 선택
        Ellipse(hdc, 375, 250, 405, 310);
        SelectObject(hdc, xxllipseBrush); // 흰색 브러시 선택
        Ellipse(hdc, 350, 235, 390, 275);       // 입술
        Ellipse(hdc, 390, 235, 430, 275);       // 입술2
        MoveToEx(hdc, 275, 215, NULL);
        LineTo(hdc, 320, 225); // >< 눈
        MoveToEx(hdc, 275, 235, NULL);
        LineTo(hdc, 320, 225);
        MoveToEx(hdc, 500, 215, NULL);
        LineTo(hdc, 450, 225); // >< 눈
        MoveToEx(hdc, 500, 235, NULL);
        LineTo(hdc, 450, 225);
        SelectObject(hdc, bBrush);
        Ellipse(hdc, 375, 225, 405, 250); // 코
        //수염
        MoveToEx(hdc, 370, 250, NULL);
        LineTo(hdc, 330, 230);
        MoveToEx(hdc, 370, 260, NULL);
        LineTo(hdc, 330, 280);
        MoveToEx(hdc, 410, 250, NULL);
        LineTo(hdc, 450, 230);
        MoveToEx(hdc, 410, 260, NULL);
        LineTo(hdc, 450, 280);

        ReleaseDC(hwnd, hdc);
    }
}

void DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom)
{
    double xlength = 0, ylength = 0;

    xlength = right - left;
    ylength = bottom - top;

    // 왼쪽 귀 그리기 (노란색)
    HBRUSH hLeftEarColor = CreateSolidBrush(RGB(255, 200, 15));
    SelectObject(hdc, hLeftEarColor);
    Ellipse(hdc, left, top, left + xlength / 3, top + ylength / 3);
    DeleteObject(hLeftEarColor);

    // 오른쪽 귀 그리기 (노란색)
    HBRUSH hRightEarColor = CreateSolidBrush(RGB(255, 200, 15));
    SelectObject(hdc, hRightEarColor);
    Ellipse(hdc, left + xlength * 2 / 3, top, left + xlength, top + ylength / 3);
    DeleteObject(hRightEarColor);

    // 얼굴 그리기 (노란색)
    HBRUSH hFaceColor = CreateSolidBrush(RGB(255, 200, 15));
    SelectObject(hdc, hFaceColor);
    Ellipse(hdc, left + xlength / 18, top + ylength / 13, left + xlength / 18 * 17, top + ylength);
    DeleteObject(hFaceColor);

    // 눈썹 그리기 (가운데 정렬)
    SelectObject(hdc, GetStockObject(BLACK_PEN));

    // 왼쪽 눈 가로선 그리기
    MoveToEx(hdc, left + xlength * 2 / 9 + 10, top + ylength * 40 / 144, NULL);
    LineTo(hdc, left + xlength * 10 / 27 + 10, top + ylength * 40 / 144);
    MoveToEx(hdc, left + xlength * 10 / 18 + 10, top + ylength * 40 / 144, NULL);
    LineTo(hdc, left + xlength * 13 / 18 + 10, top + ylength * 40 / 144);

    // 왼쪽 눈 세로선 그리기
    MoveToEx(hdc, left + xlength * 2 / 9 + 10, top + ylength * 41 / 144, NULL);
    LineTo(hdc, left + xlength * 10 / 27 + 10, top + ylength * 41 / 144);
    MoveToEx(hdc, left + xlength * 10 / 18 + 10, top + ylength * 41 / 144, NULL);
    LineTo(hdc, left + xlength * 13 / 18 + 10, top + ylength * 41 / 144);

    // 왼쪽 눈 밑 부분 그리기
    MoveToEx(hdc, left + xlength * 2 / 9 + 10, top + ylength * 42 / 144, NULL);
    LineTo(hdc, left + xlength * 10 / 27 + 10, top + ylength * 42 / 144);
    MoveToEx(hdc, left + xlength * 10 / 18 + 10, top + ylength * 42 / 144, NULL);
    LineTo(hdc, left + xlength * 13 / 18 + 10, top + ylength * 42 / 144);

    // 눈 그리기 (검정색)
    SelectObject(hdc, GetStockObject(BLACK_BRUSH));

    // 왼쪽 눈
    Ellipse(hdc, left + xlength * 15 / 54 + 10, top + ylength * 27 / 72, left + xlength * 18 / 54 + 10, top + ylength * 31 / 72);

    // 오른쪽 눈
    Ellipse(hdc, left + xlength * 32 / 54 + 10, top + ylength * 27 / 72, left + xlength * 35 / 54 + 10, top + ylength * 31 / 72);

    // 입 그리기 (가운데 정렬, 흰색)
    HBRUSH hMouthColor = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, hMouthColor);
    int mouthLeft = left + xlength * 8 / 20;
    int mouthRight = left + xlength / 2;
    int mouthTop = top + ylength * 35 / 72;
    int mouthBottom = top + ylength * 42 / 72;
    Ellipse(hdc, mouthLeft, mouthTop, mouthRight, mouthBottom);

    mouthLeft = left + xlength / 2;
    mouthRight = left + xlength * 12 / 20;
    Ellipse(hdc, mouthLeft, mouthTop, mouthRight, mouthBottom);

    DeleteObject(hMouthColor);
}
