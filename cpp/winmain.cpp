#include <windows.h>

// int CALLBACK winMain (
int CALLBACK WinMain (
    HINSTANCE Instance,
    HINSTANCE PrevInstance,
    LPSTR CommandLine,
    int ShowCode
) {
    MessageBox(
        0,
        "Test Message",
        "Box Caption",
        MB_OK | MB_ICONINFORMATION
    );
    return 0;
}
