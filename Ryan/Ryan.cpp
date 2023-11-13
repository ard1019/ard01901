#include "YuhanCG.h"

HBRUSH hFaceBrush;  // 얼굴을 그리는데 사용할 브러시
HBRUSH hEyeBrush;   // 눈을 그리는데 사용할 브러시
HBRUSH hEarBrush;   // 귀를 그리는데 사용할 브러시
HBRUSH hMouthBrush; // 입을 그리는데 사용할 브러시

static HCURSOR hCrossCursor = LoadCursor(NULL, IDC_CROSS);  // 십자가 모양의 커서
static HCURSOR hArrowCursor = LoadCursor(NULL, IDC_ARROW);  // 화살표 모양의 커서

POINT startPoint = { 0 };       // 그리기 시작점
POINT endPoint = { 0 };         // 그리기 끝점
POINT startPoint1 = { 0 };      // 두 번째 시작점 (오른쪽 버튼 드래그 용)
POINT endPoint1 = { 0 };        // 두 번째 끝점 (오른쪽 버튼 드래그 용)
BOOL isDrawingEnabled = FALSE;  // 그리기 활성화 여부
BOOL isRectangleMode = TRUE;    // 사각형 그리기 모드
BOOL isCircleMode = FALSE;      // 원 그리기 모드
BOOL isBonobonoMode = FALSE;    // 보노보노 모드
BOOL isRyanMode = FALSE;        // Ryan 모드
BOOL isCubeMode = FALSE;        // Cube 모드
BOOL CircleScale = FALSE;       // 원 크기 조절 여부
BOOL isFirstClick = TRUE;       // 첫 번째 클릭 여부
RECT dragRect;                   // 드래그 영역
int button = 0;                 // 버튼 상태 (왼쪽 버튼: 0, 오른쪽 버튼: 1)
int isMouseLButtonPressed = 0;  // 마우스 왼쪽 버튼 눌림 여부
int isMouseRButtonPressed = 0;  // 마우스 오른쪽 버튼 눌림 여부
int blink = 1;                  // 깜빡임 여부
double xlength = 0, ylength = 0, left = 0, top = 0, right = 0, bottom = 0;  // 변수들


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
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
            SetCursor(hCrossCursor);
            return TRUE;
        }
        else
        {
            SetCursor(hArrowCursor);  // 클라이언트 영역 밖에 있는 경우 화살표 모양 커서로 설정
            return TRUE;
        }
    }
    break;


    case WM_COMMAND:
        if (LOWORD(wParam) == 1) // "사각형" 버튼이 클릭된 경우
        {
            isRectangleMode = TRUE;
            isCircleMode = FALSE;
            isBonobonoMode = FALSE;
            isRyanMode = FALSE;
            isCubeMode = FALSE;
            isFirstClick = TRUE;
            SetFocus(hwnd);
        }
        else if (LOWORD(wParam) == 2) // "원" 버튼이 클릭된 경우
        {
            isRectangleMode = FALSE;
            isCircleMode = TRUE;
            isBonobonoMode = FALSE;
            isRyanMode = FALSE;
            isCubeMode = FALSE;
            isFirstClick = TRUE;
            SetFocus(hwnd);
        }
        else if (LOWORD(wParam) == 3) // "보노보노 모드" 버튼이 클릭된 경우
        {
            isRectangleMode = FALSE;
            isCircleMode = FALSE;
            isBonobonoMode = TRUE; // "보노보노 모드" 활성화
            isRyanMode = FALSE;
            isCubeMode = FALSE;
            isFirstClick = TRUE;
            SetFocus(hwnd);
            InvalidateRect(hwnd, NULL, TRUE);  // 화면 갱신 요청
        }
        else if (LOWORD(wParam) == 4) // "Ryan" 버튼이 클릭된 경우
        {
            isRectangleMode = FALSE;
            isCircleMode = FALSE;
            isBonobonoMode = FALSE;
            isRyanMode = TRUE;
            isCubeMode = FALSE;
            isFirstClick = TRUE;
            SetFocus(hwnd);
        }
        else if (LOWORD(wParam) == 5) // "Cube" 버튼이 클릭된 경우
        {
            isRectangleMode = FALSE;
            isCircleMode = FALSE;
            isBonobonoMode = FALSE;
            isRyanMode = FALSE;
            isCubeMode = TRUE;
            isFirstClick = TRUE;
            SetFocus(hwnd);
        }
        break;

    case WM_RBUTTONDOWN:
    {
        if (isRectangleMode)
        {
            // 마우스 오른쪽 버튼 클릭 이벤트 처리
            POINTS pt = MAKEPOINTS(lParam);
            POINT clientPoint = { pt.x, pt.y };
            ScreenToClient(hwnd, &clientPoint);
            button = 1;

            // 클라이언트 좌표를 기반으로 어떤 객체를 클릭했는지 확인하는 코드를 추가합니다.
            // 이 예제에서는 현재 하나의 사각형만 처리하도록 가정합니다.

            // 선택된 사각형을 드래그할 때 필요한 정보를 저장합니다.
            isMouseRButtonPressed = 1;
            if (PtInRect(&dragRect, clientPoint)) {
                isDrawingEnabled = TRUE;
                startPoint1 = endPoint1 = clientPoint; // 시작 및 끝 포인트를 현재 마우스 위치로 설정합니다.
            }
            startPoint1 = endPoint1 = clientPoint; // 시작 및 끝 포인트를 현재 마우스 위치로 설정합니다.
        }
        if (isCircleMode)
        {
            // 마우스 오른쪽 버튼 클릭 이벤트 처리
            POINTS pt = MAKEPOINTS(lParam);
            POINT clientPoint = { pt.x, pt.y };
            ScreenToClient(hwnd, &clientPoint);
            CircleScale = 1;
            isDrawingEnabled = TRUE;
            // 클라이언트 좌표를 기반으로 어떤 객체를 클릭했는지 확인하는 코드를 추가합니다.
            // 이 예제에서는 현재 하나의 사각형만 처리하도록 가정합니다.

            // 선택된 사각형을 드래그할 때 필요한 정보를 저장합니다.
            isMouseRButtonPressed = 1;
            startPoint1 = endPoint1 = clientPoint; // 시작 및 끝 포인트를 현재 마우스 위치로 설정합니다.
        }
    }
    break;

    case WM_LBUTTONDOWN:
        if (isFirstClick)
        {
            POINT pt;
            GetCursorPos(&pt);             // 현재 마우스 위치 가져오기
            ScreenToClient(hwnd, &pt);     // 화면 좌표를 클라이언트 좌표로 변환

            RECT rc;
            rc.left = 16;
            rc.top = 90;
            rc.right = 800 - 32;
            rc.bottom = 480 - 56;
            button = 0;

            // 클라이언트 영역 안에 있는 경우
            if (pt.x > rc.left && pt.x < rc.right && pt.y > rc.top && pt.y < rc.bottom)
            {
                startPoint.x = LOWORD(lParam);
                startPoint.y = HIWORD(lParam);
                isFirstClick = FALSE;
                isMouseLButtonPressed = 1;
            }
        }
        break;

    case WM_LBUTTONUP:
        if (!isFirstClick)
        {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            isDrawingEnabled = TRUE;
            isMouseLButtonPressed = 0;
            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);  // 화면 갱신 요청
            isFirstClick = TRUE;
        }
        break;

    case WM_RBUTTONUP:
    {
        isMouseRButtonPressed = 0;
        isDrawingEnabled = TRUE;
        CircleScale = 0;
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
                endPoint.x = LOWORD(lParam);
                endPoint.y = HIWORD(lParam);
            }
            // WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
            InvalidateRect(hwnd, NULL, TRUE);  // 화면 갱신 요청
        }
        if (isMouseRButtonPressed)
        {
            endPoint1.x = LOWORD(lParam);
            endPoint1.y = HIWORD(lParam);

            // 현재 마우스 위치와 시작 클릭 위치 사이의 거리를 계산합니다.
            int deltaX = endPoint1.x - startPoint1.x;
            int deltaY = endPoint1.y - startPoint1.y;

            // 선택된 사각형을 이동합니다.
            OffsetRect(&dragRect, deltaX, deltaY);
            button = 1;
            startPoint1 = endPoint1; // 현재 마우스 위치를 새로운 시작점으로 설정합니다.

            InvalidateRect(hwnd, NULL, TRUE);  // 화면 갱신 요청
            // 화면 다시 그리기
        }
    }

    case WM_KEYDOWN:
        if (wParam == VK_SPACE) {
            blink = 0;  // 스페이스 바가 눌렸을 때, blink 변수를 0으로 설정 (깜박임 중지)
            InvalidateRect(hwnd, NULL, TRUE);  // 화면을 갱신 요청
        }
        break;

    case WM_KEYUP:
        if (wParam == VK_SPACE) {
            blink = 1;  // 스페이스 바가 떼어졌을 때, blink 변수를 1으로 설정 (깜박임 재개)
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

        if (isBonobonoMode) {
            // "보노보노 모드"가 활성화된 경우 배경을 그립니다.
            DrawBonobono(hwnd, hdc, blink);
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

        if (isRyanMode)
        {
            RECT rect;
            GetClientRect(hwnd, &rect);

            // 드래그 중인 상자 그리기
            left = min(startPoint.x, endPoint.x);
            top = min(startPoint.y, endPoint.y);
            right = max(startPoint.x, endPoint.x);
            bottom = max(startPoint.y, endPoint.y);

            DrawRyan(hwnd, hdc, left, top, right, bottom);
        }
        else if (isRectangleMode && (button == 1))
        {
            RECT rect;
            GetClientRect(hwnd, &rect);

            HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255)); // 핑크 브러시 생성
            FillRect(hdc, &dragRect, hBrush); // 핑크색 상자 그리기
            DeleteObject(hBrush);
        }

        ReleaseDC(hwnd, hdc);
        EndPaint(hwnd, &ps);
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
