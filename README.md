# CoD2x
![alt text](images/cod2-window.png)

CoD2x is modification of Call of Duty 2 client and server.

This "patch" or "extended version" is build on top of 1.3 version.

> :warning: **Testing**: Right now only test version is available. Please just test if that patch is working and then uninstall it. It's not recommended to use it for official matches with anticheat enabled yet.


Aims primarily for the competitive community to fix bugs and add new features to the game.


# Features

#### Changes
- Dialog "Run in safe mode?" is removed
- Dialog "Set Optimal Settings?" and "Recommended Settings Update" is removed
- New text in the console to indicate that CoD2x is loaded
- Changed auto-update server with ability to download the latest version of CoD2x
  - ![alt text](images/cod2-auto-update.png)
- Ability to connect both original 1.3 servers and new 1.4 servers
- New server errors descriptions when non-compatible clients tried to connect to the server
  - ![alt text](images/cod2-different-version-error.png)
- Fixed black screen on startup - caused by missing microphone / sound device
- Added requirement to run the game as administrator to fix problems with VirtualStore folder and the need to have write access into Program Files folder (as it was possible in Windows XP)
  - ![alt text](images/cod2-run-as-admin.png)
- Crouch to stand peak bug fix - matching the animation time to be the same as in 1st view 
  - ![alt text](images/cod2-clip-fix.gif)
- Fixed "+smoke" bug - when player holds smoke or grenade button, but has none, it suppresses sounds of firing, footsteps, jumping and other sounds for other players

#### Improvements
- Added windowed and borderless window mode:
    - windowed mode: `r_fullscreen 0`
    - borderless mode: `r_fullscreen 0` and `r_mode [screen resolution]`
    - fullscreen mode: `r_fullscreen 1` (default)
- Added support for rinput (raw input for mouse movement) 
    - ![alt text](images/cod2-rinput.png)
    - enabled: `m_rinput 1` (raw mouse movement, not affected by Windows settings)
    - disabled: `m_rinput 0` (default)
- Added possibility to restrict FPS via mod (like zPAM) into range 125 - 250 using new cvar `com_maxfps_limit` (the cvar is cheat protected and can be set only by the server)
  - ![alt text](images/cod2-com-max-fps.png)
- Ignoring custom IWD mods on game start to avoid runtime errors (only files starting with 'iw_' or 'localized_' are loaded)
- Set sv_cheats 1 on disconnect to allow to play demo without the need to do devmap
- Added possibility to change the master server via cvars `sv_masterServer`, `sv_masterPort`




# Plans
- Fix the "iwd sum/name mismatch" error when there are too many IWD files
- Translations for mod developers
- URL protocol to connect to the server from website (cod2://ip:port)
- Make it possible to show more than 4 servers in server browser on LAN
- Fix MG sensitivity
- Fix numberic 8 and 2 when typing into console
- Hide IP in scoreboard for streamers to avoid server attacks
- Add custom FPS counter rendering


# Known issues
- Single player not working


# References
- [CoD2rev_Server](https://github.com/voron00/CoD2rev_Server)
- [CoD4x_Server](https://github.com/callofduty4x/CoD4x_Server)
- [zk_libcod](https://github.com/ibuddieat/zk_libcod)
- [Enemy-Territory](https://github.com/id-Software/Enemy-Territory)




# How to install (client on Windows)
1. You need original Call of Duty 2 with version [1.3](https://www.moddb.com/games/call-of-duty-2/downloads/call-of-duty-2-pc-patch-v-13) installed.
2. Download latest version of CoD2x - [CoD2x_v1_test6_windows.zip](https://github.com/eyza-cod2/CoD2x/releases/download/v1_test6/CoD2x_v1_test6_windows.zip)
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

# How to uninstall (client on Windows)
1. Delete the following files:
    - 📄 CoD2x Installation and uninstallation manual.txt
    - 📄 mss32.dll
2. Rename following file:
    - 📄 mss32_original.dll  ->  📄 mss32.dll


# How to install (server on Linux)
1. Extract the content of the archive to the Call of Duty 2 folder:
    - 📄 CoD2x Installation and uninstallation manual.txt
    - 📄 cod2_lnxded    *(official 1.3 game version)*
    - 📄 libCoD2x.so
2. Final structure should look like this:
    - 📁 Call of Duty 2
        - 📁 main
        - 📁 pb
        - 📄 CoD2x Installation and uninstallation manual.txt
        - 📄 cod2_lnxded
        - 📄 libCoD2x.so
3. Run the game with LD_PRELOAD, for example:
`LD_PRELOAD=libCoD2x.so ./cod2_lnxded +exec server.cfg`



# How to install for developers
1. Clone this repository.
2. Copy .iwd files from original Call of Duty 2 1.3 main folder to `./bin/windows/main` folder in this repository (iw_01..iw_15 and localized_english_iw00..localized_english_iw11)
3. Instal MinGW-w64 by Brecht Sanders [winlibs-i686-posix-dwarf-gcc-14.2.0-mingw-w64msvcrt-12.0.0-r2](https://github.com/brechtsanders/winlibs_mingw/releases/download/14.2.0posix-19.1.1-12.0.0-msvcrt-r2/winlibs-i686-posix-dwarf-gcc-14.2.0-mingw-w64msvcrt-12.0.0-r2.zip) into `./tools/mingw`

4. Install WSL (Windows Subsystem for Linux) with Ubuntu 24.04 LTS
    - `wsl --install` (should install 'Ubuntu' instance name)
    - `sudo apt update`
    - `sudo dpkg --add-architecture i386`
    - `sudo apt update`
    - `sudo apt install -y make gcc gdb gdbserver:i386 build-essential`
    - `sudo apt install -y libc6:i386 libstdc++5:i386 libgcc1:i386` (runtime libraries to run original CoD2) 
    - `sudo apt install -y gcc-multilib libc6-dev:i386` (development libraries to compile new code)
    - `sudo apt-get install gcc-multilib g++-multilib` (some dependencies for compiling)
    - `exit`
    - `wsl --set-default Ubuntu`
    - |
    - Setup tmux: (enable mouse scrolling)
    - `nano ~/.tmux.conf`
    - `set -g mouse on`
    - `tmux source-file ~/.tmux.conf`
    - |
    - How to get IP of WSL virtual machine to connect from Windows to Linux CoD2x server: 
    - `ip addr show eth0 | grep inet | awk '{ print $2; }' | sed 's/\/.*$//'`
5. Run VSCode as administrator (:warning: needed to be able to run CoD2 also as administrator while debugging)
6. Use VSCode to compile, run and debug

# Repository layout
- 📁 **bin**
    - 📁 **linux** - *Linux server binaries*
    - 📁 **windows** - *Windows game binaries from original CD with 1.3 patch applied*
- 📁 **src**
    - 📁 **linux** - *code related only for Linux server*
    - 📁 **mss32** - *code related for Windows, mimicking mss32.dll*
    - 📁 **shared** - *code shared for both Linux server and Windows version*
    - 📁 **other** - *reversed / testing code*
- 📁 **tools** - *contains external tools for coding, compiling, etc..*
- 📁 **zip** - *zip files are generated here*

To avoid source code duplication, the code that is used for both Linux and Windows is placed in `📁src / 📁shared` folder. Its primarily a server side code. 

The code that is related only for Windows version or Linux server is placed in particular folders `📁src / 📁mss32` or `📁src / 📁linux`, both sharing the shared folder.



# How the Windows mss32.dll works
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