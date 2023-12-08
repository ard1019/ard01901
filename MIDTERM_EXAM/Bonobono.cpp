#include <windows.h>

// 드로잉 영역의 시작과 끝 좌표
POINT drawstart, drawend;
// 마우스가 드로잉 영역 내에 있는지 여부
BOOL mindraw = FALSE;
// 드로잉 모드
int drawmode = 0;
// 이전 사각형의 좌표를 저장하는 변수
BOOL isDrawing = FALSE;
// 스페이스바 상태
bool sp = false;
// 보노보노 모드
bool bonoMode = false;



// 보노보노 그리기 함수
void bono(HWND hWnd, HDC hdc, bool sp) {
    RECT rect;
    // 클라이언트 영역 크기 가져오기
    GetClientRect(hWnd, &rect);

    if (bonoMode) {
        // 파랑색 얼굴 그리기
        HBRUSH hBrush = CreateSolidBrush(RGB(127, 200, 255));
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 250, 100, 525, 375);

        // 핑크색 입 그리기
        HBRUSH h3Brush = CreateSolidBrush(RGB(255, 150, 255));
        SelectObject(hdc, h3Brush);
        Ellipse(hdc, 375, 250, 405, 310);
        DeleteObject(hBrush);

        // 흰색 입술 그리기
        HBRUSH h2Brush = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(hdc, h2Brush);
        Ellipse(hdc, 350, 235, 390, 275);
        Ellipse(hdc, 390, 235, 430, 275);

        // 검정색 코 그리기
        HBRUSH h1Brush = CreateSolidBrush(RGB(0, 0, 0));
        SelectObject(hdc, h1Brush);
        Ellipse(hdc, 375, 225, 405, 250);
        DeleteObject(hBrush);

        // 수염 그리기
        MoveToEx(hdc, 370, 250, NULL);
        LineTo(hdc, 330, 230);
        MoveToEx(hdc, 370, 260, NULL);
        LineTo(hdc, 330, 280);
        MoveToEx(hdc, 410, 250, NULL);
        LineTo(hdc, 450, 230);
        MoveToEx(hdc, 410, 260, NULL);
        LineTo(hdc, 450, 280);

        if (sp == false) {
            // 일반 눈 그리기
            Ellipse(hdc, 275, 215, 285, 240);
            Ellipse(hdc, 490, 215, 500, 240);
            SelectObject(hdc, h2Brush);
            Ellipse(hdc, 277, 220, 283, 230);
            Ellipse(hdc, 492, 220, 498, 230);
        }
        else {
            SelectObject(hdc, h1Brush);
            // >< 눈 그리기
            MoveToEx(hdc, 275, 215, NULL);
            LineTo(hdc, 320, 225);
            MoveToEx(hdc, 275, 235, NULL);
            LineTo(hdc, 320, 225);

            MoveToEx(hdc, 500, 215, NULL);
            LineTo(hdc, 450, 225);
            MoveToEx(hdc, 500, 235, NULL);
            LineTo(hdc, 450, 225);
        }
    }
}

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_KEYDOWN:
        if (wParam == VK_SPACE) {
            // 스페이스바 눌림
            sp = true;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;

    case WM_KEYUP:
        if (wParam == VK_SPACE) {
            // 스페이스바 떼어짐
            sp = false;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == 1) { // 1번: 박스 그리기
            drawmode = 1;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        else if (LOWORD(wParam) == 2) { // 2번: 원 그리기
            drawmode = 2;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        else if (LOWORD(wParam) == 3) { // 3번: 보노보노 그리기 모드
            drawmode = 3;
            bonoMode = true;
            SetFocus(hWnd);
            InvalidateRect(hWnd, NULL, TRUE);
        }
        else if (LOWORD(wParam) == 4) { // 4번: 라이언 그리기 모드
            drawmode = 4;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        else if (LOWORD(wParam) == 5) { // 5번: 큐브 그리기 모드
            drawmode = 5;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;

    case WM_MOUSEMOVE:
        POINT mousePos;
        GetCursorPos(&mousePos);
        // 이동한 마우스 위치가 드로잉 영역 내에 있는지 확인
        if (mousePos.x >= drawstart.x && mousePos.x <= drawend.x &&
            mousePos.y >= drawstart.y && mousePos.y <= drawend.y) {
            mindraw = TRUE; // 마우스가 드로잉 영역 내에 있음
        }
        else {
            mindraw = FALSE; // 마우스가 드로잉 영역 밖에 있음
        }
        break;

    case WM_PAINT:
        if (true) {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            // 클라이언트 영역 크기 가져오기
            RECT clientRect;
            GetClientRect(hWnd, &clientRect);

            int margin = 8;
            int boxWidth = clientRect.right - clientRect.left - 2 * margin;
            int boxHeight = clientRect.bottom - clientRect.top - 2 * margin;

            // RGB(255, 240, 200) 색상의 네모 그리기
            HBRUSH hColorBrush = CreateSolidBrush(RGB(255, 240, 200));
            SelectObject(hdc, hColorBrush);

            int left = margin;
            int top = margin;
            int right = left + boxWidth;
            int bottom = top + boxHeight;

            // 네모 그리기
            Rectangle(hdc, left, top, right, bottom);

            // 드로잉 영역 그리기
            HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
            SelectObject(hdc, whiteBrush);
            Rectangle(hdc, left + 8, top + 88, right - 8, bottom - 8);
            drawstart.x = left + 8;
            drawstart.y = top + 88;
            drawend.x = right - 8;
            drawend.y = bottom - 8;

            if (wParam == VK_SPACE) {
                sp = true;
            }

            bono(hWnd, hdc, sp);
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_SETCURSOR: {
        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(hWnd, &pt);

        if (pt.x > drawstart.x && pt.x < drawend.x &&
            pt.y > drawstart.y && pt.y < drawend.y) {
            // 마우스 커서를 십자가 모양으로 설정
            SetCursor(LoadCursor(NULL, IDC_CROSS));
            return TRUE; // 처리됨을 알림
        }
        else { // 다시 화살표 
            SetCursor(LoadCursor(NULL, IDC_ARROW));
        }
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 메인 함수
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    HWND hWnd;
    HWND hButton1, hButton2, hButton3, hButton4, hButton5;

    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(255, 240, 200));
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"ButtonWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
        return 1;
    }

    hWnd = CreateWindow(
        L"ButtonWindowClass", L"202007022 전성현 중간고사 대체 과제",
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, 0, 800, 480, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        return FALSE;
    }

    int btnmargin = 146;
    int btnstart = 32;

    // 버튼 생성
    hButton1 = CreateWindow(
        L"BUTTON", L"Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        btnstart, 16, 130, 64, hWnd, (HMENU)1, hInstance, NULL);

    hButton2 = CreateWindow(
        L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        btnstart + btnmargin, 16, 130, 64, hWnd, (HMENU)2, hInstance, NULL);

    hButton3 = CreateWindow(
        L"BUTTON", L"Bonobono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        btnstart + btnmargin * 2, 16, 130, 64, hWnd, (HMENU)3, hInstance, NULL);

    hButton4 = CreateWindow(
        L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        btnstart + btnmargin * 3, 16, 130, 64, hWnd, (HMENU)4, hInstance, NULL);

    hButton5 = CreateWindow(
        L"BUTTON", L"Cube", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        btnstart + btnmargin * 4, 16, 130, 64, hWnd, (HMENU)5, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
