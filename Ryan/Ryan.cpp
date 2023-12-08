#include "YuhanCG.h"


static HCURSOR hCross = LoadCursor(NULL, IDC_CROSS);  // 십자가 모양의 커서
static HCURSOR hArrow = LoadCursor(NULL, IDC_ARROW);  // 화살표 모양의 커서

POINT paintStart1 = { 0 };       // 그리기 시작점
POINT paintEnd1 = { 0 };         // 그리기 끝점
POINT paintStart2 = { 0 };      // 두 번째 시작점 (오른쪽 버튼 드래그 용)
POINT paintEnd2 = { 0 };        // 두 번째 끝점 (오른쪽 버튼 드래그 용)
POINT center;
BOOL DrawingEnabled = FALSE;  // 그리기 활성화 여부
BOOL RectangleMode = FALSE;   // 사각형 그리기 모드
BOOL CircleMode = FALSE;      // 원 그리기 모드
BOOL BonobonoMode = FALSE;    // 보노보노 모드
BOOL RyanMode = FALSE;        // Ryan 모드
BOOL CubeMode = FALSE;        // Cube 모드
BOOL isblink = TRUE;
BOOL CircleScale = FALSE;       // 원 크기 조절 여부
BOOL FirstClick = TRUE;       // 첫 번째 클릭 여부
BOOL isMouseLButtonPressed = 0;  // 마우스 왼쪽 버튼 눌림 여부
BOOL isMouseRButtonPressed = 0;  // 마우스 오른쪽 버튼 눌림 여부
RECT rec;
int radius = 0;
double xlength = 0, ylength = 0, left = 0, top = 0, right = 0, bottom = 0;  // 변수들
                 // 드래그 영역

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    switch (uMsg)
    {

    case WM_COMMAND:
        if (LOWORD(wParam) == 1) // "사각형" 버튼이 클릭된 경우
        {
            RectangleMode = TRUE;
            CircleMode = FALSE;
            BonobonoMode = FALSE;
            RyanMode = FALSE;
            CubeMode = FALSE;
            FirstClick = TRUE;
            SetFocus(hwnd);
        }
        else if (LOWORD(wParam) == 2) // "원" 버튼이 클릭된 경우
        {
            RectangleMode = FALSE;
            CircleMode = TRUE;
            BonobonoMode = FALSE;
            RyanMode = FALSE;
            CubeMode = FALSE;
            FirstClick = TRUE;
            SetFocus(hwnd);
        }
        else if (LOWORD(wParam) == 3) // "보노보노 모드" 버튼이 클릭된 경우
        {
            RectangleMode = FALSE;
            CircleMode = FALSE;
            BonobonoMode = TRUE; // "보노보노 모드" 활성화
            RyanMode = FALSE;
            CubeMode = FALSE;
            FirstClick = TRUE;
            SetFocus(hwnd);
            InvalidateRect(hwnd, NULL, TRUE);  // 화면 갱신 요청
        }
        else if (LOWORD(wParam) == 4) // "Ryan" 버튼이 클릭된 경우
        {
            RectangleMode = FALSE;
            CircleMode = FALSE;
            BonobonoMode = FALSE;
            RyanMode = TRUE;
            CubeMode = FALSE;
            FirstClick = TRUE;
            SetFocus(hwnd);
        }
        else if (LOWORD(wParam) == 5) // "Cube" 버튼이 클릭된 경우
        {
            RectangleMode = FALSE;
            CircleMode = FALSE;
            BonobonoMode = FALSE;
            RyanMode = FALSE;
            CubeMode = TRUE;
            FirstClick = TRUE;
            SetFocus(hwnd);
        }
        break;

    case WM_LBUTTONUP:
        if (!FirstClick)
        {
            paintEnd1.x = LOWORD(lParam);
            paintEnd1.y = HIWORD(lParam);
            DrawingEnabled = TRUE;
            isMouseLButtonPressed = 0;
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;

    case WM_LBUTTONDOWN:

        POINT pt;
        GetCursorPos(&pt);             // 현재 마우스 위치 가져오기
        ScreenToClient(hwnd, &pt);     // 화면 좌표를 클라이언트 좌표로 변환

        RECT rc;
        rc.left = 16;
        rc.top = 90;
        rc.right = 800 - 32;
        rc.bottom = 480 - 56;

        // 클라이언트 영역 안에 있는 경우
        if (pt.x > rc.left && pt.x < rc.right && pt.y > rc.top && pt.y < rc.bottom)
        {
            paintStart1.x = LOWORD(lParam);
            paintStart1.y = HIWORD(lParam);
            FirstClick = FALSE;
            isMouseLButtonPressed = 1;
        }
        break;



    case WM_RBUTTONUP:
    {
        isMouseRButtonPressed = 0;
    }
    break;

    case WM_RBUTTONDOWN:
    {
        if (RectangleMode)
        {
            // 마우스 오른쪽 버튼 클릭 이벤트 처리
            POINTS pt = MAKEPOINTS(lParam);
            POINT clientPoint = { pt.x, pt.y };
            // 선택된 사각형을 드래그할 때 필요한 정보를 저장합니다.
            if (PtInRect(&rec, clientPoint)) {
                paintStart2 = paintEnd2 = clientPoint; // 시작 및 끝 포인트를 현재 마우스 위치로 설정합니다.
                isMouseRButtonPressed = 1;
            }
        }
        if (CircleMode)
        {
            // 마우스 오른쪽 버튼 클릭 이벤트 처리
            POINTS pt = MAKEPOINTS(lParam);
            POINT clientPoint = { pt.x, pt.y };

            // 선택된 사각형을 드래그할 때 필요한 정보를 저장합니다.
            isMouseRButtonPressed = 1;
            paintStart2 = paintEnd2 = clientPoint; // 시작 및 끝 포인트를 현재 마우스 위치로 설정합니다.
        }
    }
    break;

    case WM_MOUSEMOVE:
    {
        // 마우스 이동 중
        if (isMouseLButtonPressed)
        {
            POINT pt;
            GetCursorPos(&pt);             // 현재 마우스 위치 가져오기
            ScreenToClient(hwnd, &pt);     // 화면 좌표를 클라이언트 좌표로 변환

            RECT rc;
            rc.left = 16;
            rc.top = 90;
            rc.right = 800 - 24;
            rc.bottom = 480 - 56;

            // 클라이언트 영역 안에 있는 경우
            if (pt.x > rc.left && pt.x < rc.right && pt.y > rc.top && pt.y < rc.bottom)
            {
                paintEnd1.x = LOWORD(lParam);
                paintEnd1.y = HIWORD(lParam);
            }
            int deltaX = LOWORD(lParam) - center.x;
            int deltaY = HIWORD(lParam) - center.y;
        
            radius = static_cast<int>(sqrt(deltaX * deltaX + deltaY * deltaY));
            // WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
            InvalidateRect(hwnd, NULL, TRUE);  // 화면 갱신 요청
        }
        if (RectangleMode && isMouseRButtonPressed)
        {
            POINT pt;
            GetCursorPos(&pt);
            ScreenToClient(hwnd, &pt);

            RECT rc;
            rc.left = 16;
            rc.top = 90;
            rc.right = 800 - 20;
            rc.bottom = 520 - 56;
            if (pt.x > rc.left && pt.x < rc.right && pt.y > rc.top && pt.y < rc.bottom)
            {
                paintEnd2.x = LOWORD(lParam);
                paintEnd2.y = HIWORD(lParam);
            }
            // 현재 마우스 위치와 시작 클릭 위치 사이의 거리를 계산합니다.
            int deltaX = paintEnd2.x - paintStart2.x;
            int deltaY = paintEnd2.y - paintStart2.y;

            // 선택된 사각형을 이동합니다.
            OffsetRect(&rec, deltaX, deltaY);
            paintStart2 = paintEnd2; // 현재 마우스 위치를 새로운 시작점으로 설정합니다.

            InvalidateRect(hwnd, NULL, TRUE);
        }
        if (CircleMode && isMouseRButtonPressed)
        {
            // 우클릭으로 크기 조절 중
            int deltaX = LOWORD(lParam) - center.x;
            int deltaY = HIWORD(lParam) - center.y;

            // 마우스 이동 방향에 따라 반지름을 조절합니다.
            radius += (deltaX > 0) ? 5 : -5; // 우측으로 이동시 반지름 증가
            if (radius < 0)
            {
                radius = 0; // 반지름이 음수가 되지 않도록 보정
            }
            InvalidateRect(hwnd, NULL, TRUE);
        }
    }

    case WM_KEYDOWN:
        if (wParam == VK_SPACE) {
            isblink = FALSE;  // 스페이스 바가 눌렸을 때, blink 변수를 0으로 설정 (깜박임 중지)
            InvalidateRect(hwnd, NULL, TRUE);  // 화면을 갱신 요청
        }
        break;

    case WM_KEYUP:
        if (wParam == VK_SPACE) {
            isblink = 1;  // 스페이스 바가 떼어졌을 때, blink 변수를 1으로 설정 (깜박임 재개)
            InvalidateRect(hwnd, NULL, TRUE);  // 화면을 갱신 요청
        }
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        RECT rc;

        rc.left = 16;
        rc.top = 90;
        rc.right = 800 - 24;
        rc.bottom = 480 - 56;

        HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
        FillRect(hdc, &rc, whiteBrush);
        DeleteObject(whiteBrush);

        GetClientRect(hwnd, &rc);

        if (RectangleMode && !isMouseRButtonPressed)
        {
            rec.left = min(paintStart1.x, paintEnd1.x);
            rec.top = min(paintStart1.y, paintEnd1.y);
            rec.right = max(paintStart1.x, paintEnd1.x);
            rec.bottom = max(paintStart1.y, paintEnd1.y);
            DrawRectangle(hwnd, hdc, rec.left, rec.top, rec.right, rec.bottom);
        }
        if (isMouseRButtonPressed && RectangleMode)
        {
            RECT rect;
            GetClientRect(hwnd, &rect);


            HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255)); // 핑크 브러시 생성
            FillRect(hdc, &rec, hBrush); // 핑크색 상자 그리기
            DeleteObject(hBrush);

        }
        if (CircleMode)
        {
            DrawEllipse(hwnd, hdc, radius, center);
        }

        if (BonobonoMode) {
            // "보노보노 모드"가 활성화된 경우 배경을 그립니다.
            DrawBonobono(hwnd, hdc, isblink);
        }

        // 그리기를 위한 좌표 계산
        int left1 = 16;
        int top1 = 90;
        int right1 = rc.right - 16;
        int bottom1 = rc.bottom - 16;

        // 패딩과 마진이 8px인 사각형 테두리 그리기
        RECT rect1 = { left1, top1, right1, bottom1 };
        FrameRect(hdc, &rect1, (HBRUSH)GetStockObject(BLACK_BRUSH));

        int left2 = 8;
        int top2 = 8;
        int right2 = rc.right - 8;
        int bottom2 = rc.bottom - 8;

        // 패딩과 마진이 8px인 사각형 테두리 그리기
        RECT rect2 = { left2, top2, right2, bottom2 };
        FrameRect(hdc, &rect2, (HBRUSH)GetStockObject(BLACK_BRUSH));


        if (RyanMode)
        {
            RECT rect;
            GetClientRect(hwnd, &rect);

            // 드래그 중인 상자 그리기
            left = min(paintStart1.x, paintEnd1.x);
            top = min(paintStart1.y, paintEnd1.y);
            right = max(paintStart1.x, paintEnd1.x);
            bottom = max(paintStart1.y, paintEnd1.y);

            DrawRyan(hwnd, hdc, left, top, right, bottom);
        }

        ReleaseDC(hwnd, hdc);
        EndPaint(hwnd, &ps);
    }
    break;

    case WM_SETCURSOR:
    {
        POINT pt;
        GetCursorPos(&pt);            // 현재 마우스 위치 가져오기
        ScreenToClient(hwnd, &pt);    // 화면 좌표를 클라이언트 좌표로 변환

        RECT rc;
        rc.left = 16;
        rc.top = 90;
        rc.right = 800 - 32;
        rc.bottom = 480 - 56;

        // 클라이언트 영역 안에 있는 경우 십자가 모양 커서로 설정
        if (pt.x > rc.left && pt.x < rc.right && pt.y > rc.top && pt.y < rc.bottom)
        {
            SetCursor(hCross);
            return TRUE;
        }
        else
        {
            SetCursor(hArrow);  // 클라이언트 영역 밖에 있는 경우 화살표 모양 커서로 설정
            return TRUE;
        }
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);  // 프로그램 종료 메시지를 보냄
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"202007022 Midterm";
    const wchar_t WINDOW_NAME[] = L"202007022 Midterm";

    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;  // 윈도우 프로시저 함수 설정
    wc.hInstance = hInstance;

    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = CreateSolidBrush(RGB(255, 240, 200));  // 배경색 설정
    wc.hCursor = LoadCursor(NULL, IDC_CROSS);  // 기본 커서 설정
    LPCTSTR cursor = IDC_HAND;  // 사용하지 않는 변수, 주석 처리 가능

    RegisterClass(&wc);  // 윈도우 클래스 등록

    HWND hwnd = CreateWindowEx(
        0,  // 추가적인 창 스타일
        CLASS_NAME,  // 등록된 윈도우 클래스 이름
        WINDOW_NAME,  // 윈도우 제목
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,  // 윈도우 스타일 (크기 조절 및 최대화 버튼 비활성화)

        // 윈도우 크기 및 위치
        CW_USEDEFAULT, CW_USEDEFAULT, 810, 480,

        NULL,       // 부모 윈도우 핸들
        NULL,       // 메뉴 핸들
        hInstance,  // 인스턴스 핸들
        NULL        // 추가적인 애플리케이션 데이터
    );


    if (hwnd == NULL) {
        return 0;
    }

    // 버튼의 크기와 간격 설정
    int buttonWidth = 140;
    int buttonHeight = 64;
    int buttonSpacing = 12;
    int leftMargin = 24;

    // 각 버튼을 생성하고 위치와 크기 설정
    CreateWindow(TEXT("BUTTON"), TEXT("Box Mode"), WS_VISIBLE | WS_CHILD, leftMargin - 8, 16, buttonWidth, buttonHeight, hwnd, (HMENU)1, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("Circle Mode"), WS_VISIBLE | WS_CHILD, leftMargin - 4 + buttonWidth + buttonSpacing + 1, 16, buttonWidth, buttonHeight, hwnd, (HMENU)2, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("Bonobono Mode"), WS_VISIBLE | WS_CHILD, leftMargin + 2 * (buttonWidth + buttonSpacing) + 2, 16, buttonWidth, buttonHeight, hwnd, (HMENU)3, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("Ryan Mode"), WS_VISIBLE | WS_CHILD, leftMargin + 3 * (buttonWidth + buttonSpacing) + 3, 16, buttonWidth, buttonHeight, hwnd, (HMENU)4, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("Cube Mode"), WS_VISIBLE | WS_CHILD, leftMargin + 4 * (buttonWidth + buttonSpacing) + 4, 16, buttonWidth, buttonHeight, hwnd, (HMENU)5, NULL, NULL);
    ShowWindow(hwnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
