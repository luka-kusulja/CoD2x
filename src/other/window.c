#include <windows.h>

#define BUTTON_WINDOWED 1
#define BUTTON_FULLSCREEN 2
#define BUTTON_BORDERLESS 3

// Global variable for windosw mode
int windowMode = 2;  // 0 for windowed, 1 for fullscreen, 2 for borderless fullscreen

int windowClosedByUser = 0;  // 0 means not closed by user, 1 means closed by user


// Window Procedure function
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hwndButtonWindowed, hwndButtonFullscreen, hwndButtonBorderless;
    PAINTSTRUCT ps;
    HDC hdc;

    switch (uMsg) {
        case WM_CREATE:
            // Create buttons
            hwndButtonWindowed = CreateWindow(
                "BUTTON", "Windowed Mode",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                20, 20, 150, 30,
                hwnd, (HMENU)BUTTON_WINDOWED, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

            hwndButtonFullscreen = CreateWindow(
                "BUTTON", "Fullscreen Mode",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                20, 60, 150, 30,
                hwnd, (HMENU)BUTTON_FULLSCREEN, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

            hwndButtonBorderless = CreateWindow(
                "BUTTON", "Borderless Fullscreen",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                20, 100, 150, 30,
                hwnd, (HMENU)BUTTON_BORDERLESS, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

            InvalidateRect(hwnd, NULL, TRUE);  // Forces the window to be redrawn, ensuring the buttons appear
            break;

        case WM_COMMAND:
            if (LOWORD(wParam) == BUTTON_WINDOWED) {
                // Switch to windowed mode and recreate the window
                windowMode = 0;
                DestroyWindow(hwnd);
                PostQuitMessage(0);
            } else if (LOWORD(wParam) == BUTTON_FULLSCREEN) {
                // Switch to fullscreen mode and recreate the window
                windowMode = 1;
                DestroyWindow(hwnd);
                PostQuitMessage(0);
            } else if (LOWORD(wParam) == BUTTON_BORDERLESS) {
                // Switch to borderless fullscreen mode and recreate the window
                windowMode = 2;
                DestroyWindow(hwnd);
                PostQuitMessage(0);
            }
            break;

        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH)GetStockObject(WHITE_BRUSH));  // Fill the background with white color
            EndPaint(hwnd, &ps);
            return 0;

        case WM_ERASEBKGND:
            return 1;  // Indicate that we handled background erase to prevent flickering

        case WM_CLOSE:
            windowClosedByUser = 1;  // Set the flag to indicate the window was closed by the user
            DestroyWindow(hwnd);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

// Function to create the main window with a specific mode
HWND CreateMainWindow(HINSTANCE hInstance, int nCmdShow) {
    const char CLASS_NAME[] = "Sample Window Class";
    DWORD dwExStyle, dwStyle;

    // Set window style based on windowMode
    switch (windowMode) {
        default:
        case 0:
            // Windowed
            dwExStyle = 0;
            dwStyle = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX; // Standard window style with title bar, system menu, and minimize button (0x00C80000)
            break;
        case 1:
            // Fullscreen
            dwExStyle = WS_EX_TOPMOST; // Ensures the window stays on top of all other windows (0x00000008)
            dwStyle = WS_POPUP; // Creates a window without borders, used for fullscreen (0x80000000)
            break;
        case 2:
            // Borderless fullscreen window
            dwExStyle = 0;
            dwStyle = WS_POPUP | WS_VISIBLE; // Borderless window that acts like fullscreen without being topmost (0x80000000)
            break;
    }

    // Register the window class
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);  // Set a background brush to ensure the window is cleared
    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
        dwExStyle,            // Extended window style
        CLASS_NAME,           // Window class name
        "Window Title",       // Window title
        dwStyle,              // Window style
        CW_USEDEFAULT,        // Initial x position
        CW_USEDEFAULT,        // Initial y position
        800,                  // Width
        600,                  // Height
        NULL,                 // Parent window
        NULL,                 // Menu
        hInstance,            // Instance handle
        NULL                  // Additional application data
    );



    if (hwnd != NULL) {
        // Apply additional changes based on the window mode
        if (windowMode == 1 || windowMode == 2) {
            // Fullscreen or borderless fullscreen
            SetWindowLongPtr(hwnd, GWL_STYLE, dwStyle);
            SetWindowLongPtr(hwnd, GWL_EXSTYLE, dwExStyle);
            SetWindowPos(hwnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED | SWP_SHOWWINDOW);
            ShowWindow(hwnd, SW_MAXIMIZE);
        } else {
            // Windowed mode
            SetWindowLongPtr(hwnd, GWL_STYLE, dwStyle);
            SetWindowLongPtr(hwnd, GWL_EXSTYLE, dwExStyle);
            SetWindowPos(hwnd, HWND_NOTOPMOST, 100, 100, 800, 600, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
            ShowWindow(hwnd, SW_RESTORE);
        }

        // Ensure the window is repainted
        InvalidateRect(hwnd, NULL, TRUE);  // Invalidate the entire window area to force redraw
        UpdateWindow(hwnd);                // Ensure that the window and all child controls are redrawn
        //RedrawWindow(hwnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);  // Redraw the window and all children
    }

    return hwnd;
}

// Main function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    HWND hwnd = NULL;
    MSG msg = {0};


    while (1) {
        // Create the main window with the current mode
        hwnd = CreateMainWindow(hInstance, nCmdShow);

        if (hwnd == NULL) {
            return 0;
        }

        // Run the message loop
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (windowClosedByUser) {
            return 0;  // Exit the application if the window was closed by the user
        }
    }

    return 0;
}
