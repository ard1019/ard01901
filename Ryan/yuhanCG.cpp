#include "yuhanCG.h"

void DrawEllipse(HWND hWnd, HDC hdc, int radius, POINT center) {
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
    Ellipse(hdc, center.x - radius, center.y - radius, center.x + radius, center.y + radius);
    SelectObject(hdc, hBrush);
    DeleteObject(hBrush); // �귯�� ����
}

void DrawBonobono(HWND hwnd, HDC hdc, int blink)
{
    RECT rc = { 16, 90, 800 - 32, 480 - 56 };
    // ����� �׸��ϴ�.
    if (blink)
    {
        HBRUSH bBrush = CreateSolidBrush(RGB(0, 0, 0)); // ���� ����
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255)); // ���� ����
        HBRUSH hEllipseBrush = CreateSolidBrush(RGB(127, 200, 255));
        HBRUSH ddllipseBrush = CreateSolidBrush(RGB(255, 150, 255));// ��ȫ��
        HBRUSH xxllipseBrush = CreateSolidBrush(RGB(255, 255, 255));// �Ͼ��
        FillRect(hdc, &rc, hBrush);
        DeleteObject(hBrush);
        SelectObject(hdc, hEllipseBrush); // �Ķ��� �귯�� ����
        Ellipse(hdc, 250, 100, 525, 375); // ��
        SelectObject(hdc, ddllipseBrush); // �Ķ��� �귯�� ����
        Ellipse(hdc, 375, 250, 405, 310); // ��
        SelectObject(hdc, xxllipseBrush); // ��� �귯�� ����
        Ellipse(hdc, 350, 235, 390, 275); // �Լ�
        Ellipse(hdc, 390, 235, 430, 275); // �Լ�
        SelectObject(hdc, bBrush);
        Ellipse(hdc, 275, 215, 285, 240); // ��
        Ellipse(hdc, 490, 215, 500, 240); // ��2
        SelectObject(hdc, xxllipseBrush);
        Ellipse(hdc, 277, 220, 283, 230); // ���� ������
        Ellipse(hdc, 492, 220, 498, 230); // ������ ������
        SelectObject(hdc, bBrush);
        Ellipse(hdc, 375, 225, 405, 250); // ��
        //����
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

        HBRUSH bBrush = CreateSolidBrush(RGB(0, 0, 0)); // ���� ����
        HBRUSH hEllipseBrush = CreateSolidBrush(RGB(127, 200, 255));
        HBRUSH ddllipseBrush = CreateSolidBrush(RGB(255, 150, 255));// ��ȫ��
        HBRUSH xxllipseBrush = CreateSolidBrush(RGB(255, 255, 255));// �Ͼ��
        GetClientRect(hwnd, &rect);
        SelectObject(hdc, hEllipseBrush); // �Ķ��� �귯�� ����
        Ellipse(hdc, 250, 100, 525, 375);// ��
        SelectObject(hdc, ddllipseBrush); // �Ķ��� �귯�� ����
        Ellipse(hdc, 375, 250, 405, 310);
        SelectObject(hdc, xxllipseBrush); // ��� �귯�� ����
        Ellipse(hdc, 350, 235, 390, 275);       // �Լ�
        Ellipse(hdc, 390, 235, 430, 275);       // �Լ�2
        MoveToEx(hdc, 275, 215, NULL);
        LineTo(hdc, 320, 225); // >< ��
        MoveToEx(hdc, 275, 235, NULL);
        LineTo(hdc, 320, 225);
        MoveToEx(hdc, 500, 215, NULL);
        LineTo(hdc, 450, 225); // >< ��
        MoveToEx(hdc, 500, 235, NULL);
        LineTo(hdc, 450, 225);
        SelectObject(hdc, bBrush);
        Ellipse(hdc, 375, 225, 405, 250); // ��
        //����
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

    // ���� �� �׸��� (�����)
    HBRUSH hLeftEarColor = CreateSolidBrush(RGB(255, 200, 15));
    SelectObject(hdc, hLeftEarColor);
    Ellipse(hdc, left, top, left + xlength / 3, top + ylength / 3);
    DeleteObject(hLeftEarColor);

    // ������ �� �׸��� (�����)
    HBRUSH hRightEarColor = CreateSolidBrush(RGB(255, 200, 15));
    SelectObject(hdc, hRightEarColor);
    Ellipse(hdc, left + xlength * 2 / 3, top, left + xlength, top + ylength / 3);
    DeleteObject(hRightEarColor);

    // �� �׸��� (�����)
    HBRUSH hFaceColor = CreateSolidBrush(RGB(255, 200, 15));
    SelectObject(hdc, hFaceColor);
    Ellipse(hdc, left + xlength / 18, top + ylength / 13, left + xlength / 18 * 17, top + ylength);
    DeleteObject(hFaceColor);

    // ���� �׸��� (��� ����)
    SelectObject(hdc, GetStockObject(BLACK_BRUSH));
    SelectObject(hdc, GetStockObject(BLACK_PEN));

    // ���� �� ���� �׸���
    Rectangle(hdc, left + xlength * 2 / 9 + 10, top + ylength * 40 / 144 - 5, left + xlength * 10 / 27 + 10, top + ylength * 40 / 144 + 5);

    // ������ �� ���� �׸���
    Rectangle(hdc, left + xlength * 10 / 18 + 10, top + ylength * 40 / 144 - 5, left + xlength * 20 / 28 + 10, top + ylength * 40 / 144 + 5);

    // �� �׸��� (������)
    SelectObject(hdc, GetStockObject(BLACK_BRUSH));

    // ���� ��
    Ellipse(hdc, left + xlength * 15 / 54 + 10, top + ylength * 27 / 72, left + xlength * 18 / 54 + 10, top + ylength * 31 / 72);

    // ������ ��
    Ellipse(hdc, left + xlength * 32 / 54 + 10, top + ylength * 27 / 72, left + xlength * 35 / 54 + 10, top + ylength * 31 / 72);



    // �� �׸��� (��� ����, ���)
    HBRUSH hMouthColor = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, hMouthColor);
    int mouthL = left + xlength * 8 / 20;
    int mouthR = left + xlength / 2;
    int mouthT = top + ylength * 35 / 72;
    int mouthB = top + ylength * 42 / 72;
    Ellipse(hdc, mouthL, mouthT, mouthR, mouthB);

    mouthL = left + xlength / 2;
    mouthR = left + xlength * 12 / 20;
    Ellipse(hdc, mouthL, mouthT, mouthR, mouthB);

    // �� �׸��� (������)
    HBRUSH hNoseColor = CreateSolidBrush(RGB(0, 0, 0));
    SelectObject(hdc, hNoseColor);
    Ellipse(hdc, left + xlength / 2 - 5, top + ylength * 35 / 72, left + xlength / 2 + 5, top + ylength * 38 / 72);

    DeleteObject(hMouthColor);
}


void DrawRectangle(HWND hWnd, HDC hdc, int left, int top, int right, int bottom) {
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0)); // ��ũ �귯�� ����
    RECT rect = { left, top, right, bottom }; // RECT Ÿ���� ������ �����ϰ� ���� ����
    FillRect(hdc, &rect, hBrush); // ��ũ�� �簢�� �׸���
    DeleteObject(hBrush); // �귯�� ����
}
