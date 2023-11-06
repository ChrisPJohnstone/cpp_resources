#include <windows.h>

LRESULT CALLBACK MainWindowCallback(
    HWND Window,
    UINT Message,
    WPARAM wParam,
    LPARAM lParam
) {
    LRESULT Result = 0;
    switch(Message) {
        case WM_CLOSE:
            DestroyWindow(Window);
        case WM_DESTROY:
            PostQuitMessage(0);
        case WM_PAINT:
        {
            PAINTSTRUCT Paint;
            HDC DeviceContext = BeginPaint(Window, &Paint);
            
            /*
            -----------------------------------------------
            This (and other wingdi functions) only work
            if you add `-lgdi32` to compile command
            -----------------------------------------------
            
            int X = Paint.rcPaint.left;
            int Y = Paint.rcPaint.top;
            int Width = Paint.rcPaint.right - Paint.rcPaint.left;
            int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
            PatBlt(DeviceContext, X, Y, Width, Height, BLACKNESS);
            */

            FillRect(DeviceContext, &Paint.rcPaint, (HBRUSH) (COLOR_WINDOWTEXT));
            EndPaint(Window, &Paint);
        }
        default:
        {
            Result = DefWindowProc(Window, Message, wParam, lParam);
            break;
        }
    }
    return Result;
}

int CALLBACK WinMain (
    HINSTANCE Instance,
    HINSTANCE PrevInstance,
    LPSTR CommandLine,
    int ShowCode
) {
    WNDCLASS WindowClass = {};
    WindowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    WindowClass.lpfnWndProc = MainWindowCallback;
    WindowClass.hInstance = Instance;
    // WindowClass.hIcon = ;
    WindowClass.lpszClassName = "TestWindowClass";
    
    RegisterClass(&WindowClass);
    HWND WindowHandle = CreateWindowEx(
        0,
        WindowClass.lpszClassName,
        "Test",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        0,
        0,
        Instance,
        0
    );
    
    if (WindowHandle) {
        for (;;) {
            MSG Message;
            BOOL MessageResult = GetMessage(&Message, 0, 0, 0);
            if (MessageResult <= 0) {
                break;
            }
            TranslateMessage(&Message);
            DispatchMessage(&Message);             
        }
    }

    return 0;
}
