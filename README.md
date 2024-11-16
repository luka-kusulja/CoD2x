# CoD2x
![alt text](images/cod2-window.png)

CoD2x is modification of Call of Duty 2 client and server.

> :warning: **Testing**: Right now only test version is available. Please just test if that patch is working and then uninstall it. It's not recommended to use it for official matches with anticheat enabled yet.

# Features
- Fix: black screen on startup - caused by missing microphone / sound device
- Improvement: windowed mode (now forced, will be configurable in the future)
- Change: Dialog "Run in safe mode?" is removed
- Change: Cvar 'com_maxFps' limited from 125 to 250
- Change: New text in the console to indicate that CoD2x is loaded

# Plans
- Auto update
- Configurable windowed mode / borderless windowed mode - it might fix the black screen issues with alt-tabbing
- Set sv_cheats 1 when playing demo
- Run the game without additional IWD files referenced to fix "iwd sum/name mismatch" error
- Fix clipping bug by adjusting the player's animation transition time from crouch to stand (would require server-side fix, including linux binaries)

# How to install
1. You need original Call of Duty 2 with version [1.3](https://www.moddb.com/games/call-of-duty-2/downloads/call-of-duty-2-pc-patch-v-13) installed.
2. Download latest version of CoD2x - [CoD2x_v1_test1_windows.zip](https://github.com/eyza-cod2/CoD2x/releases/download/v1_test1/CoD2x_v1_test1_windows.zip)
3. Extract the content of the archive to the Call of Duty 2 folder, replacing any existing file:
    - 📄 CoD2x Installation and uninstallation manual.txt
    - 📄 CoD2x_v1_test1.dll
    - 📄 mss32.dll
    - 📄 mss32_original.dll
4. Final structure should look like this:
    - 📁 Call of Duty 2
        - 📁 Docs
        - 📁 main
        - 📁 miles
        - 📁 pb
        - 📄 CoD2MP_s.exe
        - 📄 CoD2SP_s.exe
        - 📄 **CoD2x Installation and uninstallation manual.txt**
        - 📄 **CoD2x_v1_test1.dll**
        - 📄 gfx_d3d_mp_x86_s.dll
        - 📄 gfx_d3d_x86_s.dll
        - 📄 **mss32.dll**
        - 📄 **mss32_original.dll**
        - 📄 ... (other files)

# How to uninstall
1. Delete the following files:
    - 📄 CoD2x Installation and uninstallation manual.txt
    - 📄 CoD2x_v1_test1.dll
    - 📄 mss32.dll
2. Rename following file:
    - 📄 mss32_original.dll  ->  📄 mss32.dll



# Paths to consider
`C:\Program Files\Steam\SteamApps\Common\Call of Duty 2\`
`C:\Users\%USERNAME%\AppData\Local\VirtualStore\Program Files (x86)\Call of Duty 2\`


# Install for developers
1. Clone this repository.
2. Copy .iwd files from original Call of Duty 2 1.3 main folder to `./bin/windows/main` folder in this repository (iw_01..iw_15 and localized_english_iw00..localized_english_iw11)
3. Instal MinGW-w64 by Brecht Sanders [winlibs-i686-posix-dwarf-gcc-14.2.0](https://github.com/brechtsanders/winlibs_mingw/releases/download/14.2.0posix-19.1.1-12.0.0-msvcrt-r2/winlibs-i686-posix-dwarf-gcc-14.2.0-mingw-w64msvcrt-12.0.0-r2.zip) into `./tools/mingw`
4. Use VSCode to compile, run and debug


# How it works
CoD2MP_s.exe has following dynamic libraries:
- WINMM.dll       
- WSOCK32.dll     
- mss32.dll       <-- *hooking this library*
- d3d9.dll        
- DSOUND.dll      
- KERNEL32.dll    
- USER32.dll      
- GDI32.dll       
- ADVAPI32.dll    
- SHELL32.dll     

These libraries are loaded at runtime when the CoD2MP_s.exe is started.

File mss32.dll is a Miles Sound System dynamic link library used for audio playback.
This file is replaced with our custom mss32.dll, which exports the same functions as the original mss32.dll.

The CoD2MP_s.exe imports 364 functions from original mss32.dll:
- _AIL_set_sample_adpcm_block_size@8
- _AIL_enumerate_3D_providers@12
- _AIL_end_sample@4
- _AIL_set_3D_position@16
- ...

Our version of mss32.dll has the same exported functions as original.
These functions act as a proxy to the original functions in the original mss32.dll.
    
    [CoD2MP_s.exe]
        ↓
    [mss32.dll]            <- this file
        ↓
    [mss32_original.dll]   <- original mss32.dll

When our mss32.dll is loaded, it loads mss32_original.dll and redirect all exported functions.
It also runs patching process that modifies the game memory to fix some bugs and add new features.