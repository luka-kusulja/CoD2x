# CoD2x
![alt text](images/cod2-window.png)

CoD2x is modification of Call of Duty 2 client and server.

This "patch" or "extended version" is build on top of 1.3 version.

> :warning: **Testing**: Right now only test version is available. Please just test if that patch is working and then uninstall it. It's not recommended to use it for official matches with anticheat enabled yet.



# Features
- Fix: black screen on startup - caused by missing microphone / sound device
- Fix: requirement to run the game as administrator to fix problems with VirtualStore folder and the need to have write access into Program Files folder (as it was possible in Windows XP)
- Improvement: windowed and borderless window mode
    - windowed mode: `r_fullscreen 0`
    - borderless mode: `r_fullscreen 0` and `r_mode [screen resolution]`
    - fullscreen mode: `r_fullscreen 1` (default)
- Improvement: rinput (raw input for mouse movement) 
    - enabled: `m_rinput 1` (raw mouse movement, not affected by Windows settings)
    - disabled: `m_rinput 0` (default)
- Improvement: possibility to limit restrict FPS to range 125 - 250 via mod (like zPAM) using new cvar `com_maxfps_limit` (the cvar is cheat protected and can be set only by the server)
- Change: dialog "Run in safe mode?" is removed
- Change: dialog "Set Optimal Settings?" and "Recommended Settings Update" is removed
- Change: new text in the console to indicate that CoD2x is loaded
- Change: changed auto-update server with ability to download the latest version of CoD2x



# Plans
- Set sv_cheats 1 when playing demo
- Run the game without additional IWD files referenced to fix "iwd sum/name mismatch" error
- Fix clipping bug by adjusting the player's animation transition time from crouch to stand (would require server-side fix, including linux binaries)
- Translations for mod developers
- URL protocol to connect to the server from website (cod2://ip:port)
- Make it possible to show more than 4 servers in server browser on LAN
- Detect if incorrect version of CoD2 is installed
- Fix MG sensitivity
- Fix numberic 8 and 2 when typing into console
- Implement 1.4 version with server side patches
- Implement dynamic version switch between 1.3 and 1.4
    - 1.3 version -> basic fixes and improvements, without changing the gameplay (like Windows compatibility mode, microphone bug, fullscreen mode, black screen, etc)
    - 1.4 version -> additional new features, it requires updated server side binaries


# Known issues
- Single player not working



# How to install
1. You need original Call of Duty 2 with version [1.3](https://www.moddb.com/games/call-of-duty-2/downloads/call-of-duty-2-pc-patch-v-13) installed.
2. Download latest version of CoD2x - [CoD2x_v1_test5_windows.zip](https://github.com/eyza-cod2/CoD2x/releases/download/v1_test5/CoD2x_v1_test5_windows.zip)
3. Extract the content of the archive to the Call of Duty 2 folder, replacing any existing file:
    - 📄 CoD2x Installation and uninstallation manual.txt
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
        - 📄 gfx_d3d_mp_x86_s.dll
        - 📄 gfx_d3d_x86_s.dll
        - 📄 **mss32.dll**
        - 📄 **mss32_original.dll**
        - 📄 ... (other files)

# How to uninstall
1. Delete the following files:
    - 📄 CoD2x Installation and uninstallation manual.txt
    - 📄 mss32.dll
2. Rename following file:
    - 📄 mss32_original.dll  ->  📄 mss32.dll



# Paths to consider
`C:\Program Files\Steam\SteamApps\Common\Call of Duty 2\`
`C:\Users\%USERNAME%\AppData\Local\VirtualStore\Program Files (x86)\Call of Duty 2\`


# Install for developers
1. Clone this repository.
2. Copy .iwd files from original Call of Duty 2 1.3 main folder to `./bin/windows/main` folder in this repository (iw_01..iw_15 and localized_english_iw00..localized_english_iw11)
3. Instal MinGW-w64 by Brecht Sanders [winlibs-i686-posix-dwarf-gcc-14.2.0-mingw-w64msvcrt-12.0.0-r2](https://github.com/brechtsanders/winlibs_mingw/releases/download/14.2.0posix-19.1.1-12.0.0-msvcrt-r2/winlibs-i686-posix-dwarf-gcc-14.2.0-mingw-w64msvcrt-12.0.0-r2.zip) into `./tools/mingw`
4. Run VSCode as administrator (:warning: needed to be able to run CoD2 also as administrator while debugging)
5. Use VSCode to compile, run and debug


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

# Logo
![alt text](images/logo.png)