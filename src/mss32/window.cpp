#include "window.h"
#include "shared.h"

#include <windows.h>
#include <stdio.h>
#include <cstdint>
#include "patch.h"


#define vid_xpos                    (*((dvar_t**)0x00d77158))
#define vid_ypos                    (*((dvar_t**)0x00d77150))
#define r_fullscreen                (*((dvar_t**)0x00d77128))
#define r_autopriority              (*((dvar_t**)0x00d77130))
#define in_mouse                    (*((dvar_t**)0x00d52a4c))
#define cl_bypassMouseInput         (*((dvar_t**)0x006067d0))

#define r_mode                      (*((dvar_t**)(gfx_module_addr + 0x001ce688)))
#define r_displayRefresh            (*((dvar_t**)(gfx_module_addr + 0x001ce804)))
#define r_fullscreen_rendered       (*((dvar_t**)(gfx_module_addr + 0x001ce60c)))
#define r_monitor                   (*((dvar_t**)(gfx_module_addr + 0x001ce610)))

#define R_GetMonitorFromCvars       ((HMONITOR (__cdecl*)())(gfx_module_addr + 0x000127d0))

#define mouse_center_x              (*((int*)0x00d52a5c))
#define mouse_center_y              (*((int*)0x00d52a54))
#define mouse_windowIsActive        (*((int*)0x00d52a60)) // true when window is activated (in foreground, not minimized)
#define mouse_ingameMouseActive     (*((bool*)0x00d52a68))
#define mouse_isEnabled             (*((bool*)0x00d52a69))
#define mouse_offset_x_arr          (((int*)0x0098fda8))
#define mouse_offset_y_arr          (((int*)0x0098fdb0))
#define mouse_offset_index          (*((int*)0x0098fdb8))

#define menu_cursorX                (*((int*)0x01978034))
#define menu_cursorY                (*((int*)0x01978038))
#define menu_opened                 (*((bool*)0x01978254))

#define win_hwnd                    (*((HWND*)0x00d7713c))
#define win_isActivated             (*((int*)0x00d77144))
#define win_isMinimized             (*((int*)0x00d77148))
#define win_wheelRool               (*((UINT*)0x00d7712c))

#define input_mode                  (*((int*)0x0096b654))

dvar_t* m_debug;



// 004648e0
void Mouse_DeactivateIngameCursor()
{
    if (!mouse_isEnabled || !mouse_ingameMouseActive)
        return;

    mouse_ingameMouseActive = 0;
    ReleaseCapture();
    
	while (ShowCursor(TRUE) < 0);
}

// 00464750
void Mouse_ActivateIngameCursor()
{
    SetCapture(win_hwnd);
    
    struct tagRECT rect;
    GetWindowRect(win_hwnd, &rect);

    mouse_center_x = (rect.right + rect.left) / 2;
    mouse_center_y = (rect.bottom + rect.top) / 2;

    SetCursorPos(mouse_center_x, mouse_center_y);

	while (ShowCursor(FALSE) >= 0);
}





// 00464b30
void Mouse_Loop()
{
    // Originaly where was also some "ClickToContinue" cvar, removed

    if (mouse_isEnabled == 0)
        return;

    // Originally the cursor was showed in windowed move when console was opened, thats has been removed

    if (mouse_windowIsActive)
    {
        if (GetForegroundWindow() != win_hwnd)
            return;

        POINT cursorPoint;
        POINT cursorRelativePoint;
        RECT clientRect;

        GetCursorPos(&cursorPoint);

        GetClientRect(win_hwnd, &clientRect); // Get the inner area of the window

        // Ingame mouse is not active yet
        if (mouse_ingameMouseActive == 0)
        {
            // Get the cursor position relative to the window client area (inner window)
            cursorRelativePoint = cursorPoint;
            ScreenToClient(win_hwnd, &cursorRelativePoint);

            if (m_debug->value.boolean)
                Com_Printf("Windows cursor: %d %d (%d, %d)\n", cursorRelativePoint.x, cursorRelativePoint.y, cursorPoint.x, cursorPoint.y);

            // Cursor is outside the inner area of the window
            if (cursorRelativePoint.x <= clientRect.left || cursorRelativePoint.x >= clientRect.right || 
                cursorRelativePoint.y <= clientRect.top || cursorRelativePoint.y >= clientRect.bottom)
            {
                return;
            }

            // Scale the cursor position to the game window in 640x480 resolution
            // So if width is 1280 and cursor is at 1280, it will be 640 in 640x480 resolution
            menu_cursorX = (cursorRelativePoint.x * 640) / (clientRect.right - clientRect.left);
            menu_cursorY = (cursorRelativePoint.y * 480) / (clientRect.bottom - clientRect.top);

            mouse_ingameMouseActive = 1;
            Mouse_ActivateIngameCursor();

            return;
        }

        int32_t x_offset = (cursorPoint.x - mouse_center_x);
        int32_t y_offset = (cursorPoint.y - mouse_center_y);
        
        SetCursorPos(mouse_center_x, mouse_center_y);


        if ((x_offset != 0 || y_offset != 0))
        {
            if ((input_mode & 8) != 0) // in menu
            {
                if (!cl_bypassMouseInput->value.boolean) // quickmessages allows menu without mouse cursor
                {
                    int newMenuX = menu_cursorX + x_offset;
                    int newMenuY = menu_cursorY + y_offset;

                    // If the cursor is outside of the window in windowed mode, move it back inside
                    if (r_fullscreen->value.boolean == false && (newMenuX < 0 || newMenuX > 640 || newMenuY < 0 || newMenuY > 480))
                    {
                        // Set cursor outside of the window (outside of client area)

                        // First scale the menu cursor position in 640x480 resolution to the window client area
                        int clientX = (newMenuX * (clientRect.right - clientRect.left)) / 640;
                        int clientY = (newMenuY * (clientRect.bottom - clientRect.top)) / 480;

                        // Make sure the cursor is outside the client area atleast by 1 pixel
                        if (clientX <= 0) clientX--;
                        else if (clientX >= 640) clientX++;
                        if (clientY <= 0) clientY--;
                        else if (clientY >= 480) clientY++;
                    
                        // Now convert the client area position to the screen position
                        POINT screenPoint = {clientRect.left + clientX, clientRect.top + clientY};
                        ClientToScreen(win_hwnd, &screenPoint);

                        HMONITOR monitor = MonitorFromPoint(screenPoint, MONITOR_DEFAULTTONULL);
                        
                        if (m_debug->value.boolean)
                            Com_Printf("Cursor switch: menu(%d %d) client(%d %d) screen(%d %d) valid:%i \n", newMenuX, newMenuY, clientX, clientY, screenPoint.x, screenPoint.y, monitor != NULL);

                        // The new cursor position is a valid position on any monitor (it might in invalid when cursor is moved towards the edge of the screen)
                        if (monitor != NULL)
                        {
                            // Show the cursor position outside of the window
                            SetCursorPos(screenPoint.x, screenPoint.y);
                            Mouse_DeactivateIngameCursor();
                            return;
                        }
                    }
                    
                    // Make sure the cursor is inside the window
                    if (newMenuX < 0) newMenuX = 0;
                    else if (newMenuX > 640) newMenuX = 640;
                    if (newMenuY < 0) newMenuY = 0;
                    else if (newMenuY > 480) newMenuY = 480;

                    menu_cursorX = newMenuX;
                    menu_cursorY = newMenuY;

                    if (m_debug->value.boolean)
                        Com_Printf("Menu cursor: %d %d\n", newMenuX, newMenuY);

                    if (menu_opened) {
                        // Original function to process mouse movement
                        ((void (__cdecl*)(void* data, void* arg2, int32_t x, int32_t y))0x00542d60)(*((void**)0x005dcb10), nullptr, newMenuX, newMenuY);                  
                    }

                    return;
                }
            }
            
            // 2 dimensional array of mouse offsets used for mouse filtering and game movement
            // index is being swapped between 0 and 1
            mouse_offset_x_arr[mouse_offset_index] += x_offset;
            mouse_offset_y_arr[mouse_offset_index] += y_offset;
        } 

        return;
    }

    Mouse_DeactivateIngameCursor();
}





// 00468db0
LRESULT CALLBACK CoD2WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    bool callOriginal = true;

    switch (uMsg)
    {
        case WM_CREATE:
            win_hwnd = hwnd;
            win_wheelRool = RegisterWindowMessageA("MSWHEEL_ROLLMSG");

            vid_xpos = Dvar_RegisterInt("vid_xpos", 3, -100000, 100000, (enum dvarFlags_e)(DVAR_ARCHIVE | DVAR_CHANGEABLE_RESET));
            vid_ypos = Dvar_RegisterInt("vid_ypos", 22, -100000, 100000, (enum dvarFlags_e)(DVAR_ARCHIVE | DVAR_CHANGEABLE_RESET));
            r_fullscreen = Dvar_RegisterBool("r_fullscreen", true, (enum dvarFlags_e)(DVAR_ARCHIVE | DVAR_LATCH | DVAR_CHANGEABLE_RESET));
            r_autopriority = Dvar_RegisterBool("r_autopriority", false, (enum dvarFlags_e)(DVAR_ARCHIVE | DVAR_CHANGEABLE_RESET));
            m_debug = Dvar_RegisterBool("m_debug", false, (enum dvarFlags_e)(DVAR_CHANGEABLE_RESET));

            callOriginal = false;        
            break;


        case WM_DESTROY:
            win_hwnd = NULL;
            callOriginal = false;
            break;


        // Called when the window is moved
        case WM_MOVE:
            if (r_fullscreen->value.integer == 0) // Windowed mode
            {
                RECT lpRect;
                lpRect.left = 0;
                lpRect.top = 0;
                lpRect.right = 1;
                lpRect.bottom = 1;
                // Get window X and Y - lpRect.left and lpRect.top will contain negative values representing the size of the window borders and title bar.
                AdjustWindowRect(&lpRect, GetWindowLongA(hwnd, GWL_STYLE), 0);

                int xPos = LOWORD(lParam); // X-coordinate
                int yPos = HIWORD(lParam); // Y-coordinate

                Dvar_SetInt(vid_xpos, xPos + lpRect.left);
                Dvar_SetInt(vid_ypos, yPos + lpRect.top);

                vid_xpos->modified = false;
                vid_ypos->modified = false;

                if (win_isActivated)
                    mouse_windowIsActive = 1;
            }

            // Original function also contained logic to handle hiding the cursor, thats removed now

            callOriginal = false;

            break;

        // Called when the window is activated or deactivated with minimized state
        case WM_ACTIVATE:
			bool bActivated = LOWORD(wParam) != WA_INACTIVE; // was activated (WA_ACTIVE or WA_CLICKACTIVE, not WA_INACTIVE)
			bool bMinimized = HIWORD(wParam) != 0;

            win_isMinimized = bMinimized;

            // Something with bindlist
            ((void (*)())0x0040bd50)();

            if (bActivated && bMinimized == 0) {
                win_isActivated = 1;              
                ((void (*)())0x0042c600)(); // Com_TouchMemory();
            } else {
                win_isActivated = 0;
            }

            mouse_windowIsActive = win_isActivated;

            if (!win_isActivated)
                Mouse_DeactivateIngameCursor();

            // Original function also contained logic to handle hiding the cursor, thats removed now as its handled in Mouse_Loop

            callOriginal = false;

            break;
    }

    if (!callOriginal) {
        return DefWindowProcA(hwnd, uMsg, wParam, lParam);
    }

    // Call the original function
	LRESULT ret = ((LRESULT (CALLBACK *)(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam))0x00468db0)(hwnd, uMsg, wParam, lParam);

    return ret;
}


struct GfxWindowParms
{
    HWND hwnd;
    int32_t hz;
    int32_t fullscreen;
    int32_t x;
    int32_t y;
    int32_t renderWidth;
    int32_t renderHeight;
    int32_t unk;
    int32_t aaSamples;
};



bool window_doBorderless(int renderWidth, int renderHeight, LONG *windowX, LONG *windowY) {
    bool doBorderless = false;

    // Call original function to determine on which monitor the game should be displayed according to r_monitor / vid_xpos / vid_ypos
    HMONITOR hMonitor = R_GetMonitorFromCvars();

    MONITORINFO monitorInfo;
    ZeroMemory(&monitorInfo, sizeof(MONITORINFO));
    monitorInfo.cbSize = sizeof(MONITORINFO);
    if (!GetMonitorInfoA(hMonitor, &monitorInfo)) {
        Com_Printf("Couldn't get monitor info for borderless window.");
    } else {
        int monitorWidth = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
        int monitorHeight = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;

        // Check if monitor resolutions match the required game resolution
        if (monitorWidth == renderWidth && monitorHeight == renderHeight) {
            *windowX = monitorInfo.rcMonitor.left;
            *windowY = monitorInfo.rcMonitor.top;
            doBorderless = true;
        }
    }
    return doBorderless;
}


// 10012a80
// Function called in R_Init
int R_CreateWindow()
{
    // Load data from esi register using assembly
    struct GfxWindowParms* windowInfo;
    __asm__ ("movl %%esi, %0\n\t" : "=m"(windowInfo));

    int wsExStyle;
    int wsStyle;
    RECT rect;

    if (r_fullscreen_rendered->value.boolean) // Fullscreen
    {
        Com_Printf("Attempting %i x %i fullscreen with 32 bpp at %i hz\n", windowInfo->renderWidth, windowInfo->renderHeight, windowInfo->hz);
        wsExStyle = WS_EX_TOPMOST;
        wsStyle = WS_POPUP;
        windowInfo->fullscreen = 1; 
    }
    else
    {
        POINT borderlessPoint = {0, 0};
        bool doBorderless = window_doBorderless(windowInfo->renderWidth, windowInfo->renderHeight, &borderlessPoint.x, &borderlessPoint.y);

        if (doBorderless) {
            Com_Printf("Attempting %i x %i borderless window at (%i, %i)\n", windowInfo->renderWidth, windowInfo->renderHeight, borderlessPoint.x, borderlessPoint.y);               
            wsExStyle = 0;
            wsStyle = WS_POPUP; // hide the border
            windowInfo->x = borderlessPoint.x;
            windowInfo->y = borderlessPoint.y;
        } else {
            Com_Printf("Attempting %i x %i window at (%i, %i)\n", windowInfo->renderWidth, windowInfo->renderHeight, windowInfo->x, windowInfo->y);
            wsExStyle = 0;
            wsStyle = WS_GROUP | WS_CAPTION | WS_SYSMENU;  
        }      
        windowInfo->fullscreen = 0;
    }

    // Calculates the required size of the window rectangle, based on the desired size of the client rectangle.
    rect.left = 0;
    rect.right = windowInfo->renderWidth;
    rect.top = 0;
    rect.bottom = windowInfo->renderHeight;
    AdjustWindowRectEx(&rect, wsStyle, 0, wsExStyle); // we provide required size, it returns the size of the full window rectangle including borders

    windowInfo->hwnd = CreateWindowExA(wsExStyle, "CoD2", "Call of Duty 2x Multiplayer", wsStyle, windowInfo->x, windowInfo->y,
                           rect.right - rect.left, rect.bottom - rect.top, 0, 0, GetModuleHandleA(nullptr), 0);

    if (!windowInfo->hwnd)
    {
        Com_Printf("Couldn't create a window.\n");
        return 0;
    }

    Com_Printf("Game window successfully created.\n");
    
    return 1;
}



// 0x1001309c - original function loading cvars R_*
void __stdcall R_InitCvarsAll() {

    // Change flags of r_fullscreen cvar - removed original DVAR_ROM flag - now user can change the value
    patch_int32(gfx_module_addr + 0x000ba43 + 1, (DVAR_ARCHIVE | DVAR_LATCH | DVAR_CHANGEABLE_RESET | DVAR_RENDERER));

    // Call the original function
	((void (__stdcall *)())(gfx_module_addr + 0x0000aaf0))();
}



void window_hook_rendered() {

    // Patch the function that creates the window
    patch_call(gfx_module_addr + 0x00012d69, (unsigned int)R_CreateWindow);
    
    // Call init cvars
    patch_call(gfx_module_addr + 0x0001309c, (unsigned int)R_InitCvarsAll);
}

void window_hook() {
    // Hook the game window procedure
    patch_int32(0x004663D1 + 4, (unsigned int)&CoD2WindowProc);

    // Hook calls of functions processing mouse movement
    patch_call(0x0040932e, (unsigned int)&Mouse_Loop);
    patch_call(0x0040f787, (unsigned int)&Mouse_Loop);
    patch_call(0x0043512e, (unsigned int)&Mouse_Loop);
}