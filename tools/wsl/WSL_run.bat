@echo off
:: The first argument is the Windows path
set "WINPATH=%~1"
set "ARGS=%~2"

:: Convert the Windows path to a WSL path using wslpath:
:: We use a FOR /F loop to capture the output of the wslpath command.
for /f "usebackq tokens=*" %%i in (`wsl wslpath -u "%WINPATH%"`) do set "WSLPATH=%%i"
echo WSL path: %WSLPATH%

:: Create necessary directories and copy files to WSL
echo Copying files to WSL...
:: Create the base directory /tmp/CoD2x if it doesn't exist
wsl bash -c "mkdir -p /tmp/CoD2x"
:: Check if /tmp/CoD2x/main exists; if not, create it and copy files from the Windows "main" directory
wsl bash -c "if [ ! -d /tmp/CoD2x/main ]; then echo 'Directory /tmp/CoD2x/main does not exist, copying...'; mkdir -p /tmp/CoD2x/main && cp -ru \"%WSLPATH%/bin/windows/main\"/* /tmp/CoD2x/main && echo 'Files copied successfully.'; else echo 'Directory /tmp/CoD2x/main already exists.'; fi"
echo Copying executables...
:: Copy files from the "linux" directory, only newer files are copied
wsl bash -c "cp -ru \"%WSLPATH%/bin/linux\"/* /tmp/CoD2x/"

:: Terminate any existing gdbserver and tmux sessions to avoid conflicts
echo Terminating any existing gdbserver instances...
wsl pkill gdbserver

echo Terminating any existing tmux sessions...
wsl tmux kill-session -t gdbsession 2>nul
wsl tmux kill-session -t appsession 2>nul

:: Start gdbserver to launch the app in a tmux session named 'gdbsession' with valid window size
echo Starting gdbserver in tmux session 'gdbsession'...
set cmd="cd /tmp/CoD2x && LD_PRELOAD=/tmp/CoD2x/libCoD2x.so gdbserver :1234 ./cod2_lnxded %ARGS%"
echo %cmd%
wsl tmux new-session -d -s gdbsession %cmd%

:: Open a new Windows Terminal window and attach to the 'gdbsession' tmux session to view and interact with the app's console
echo Opening a new terminal window to interact with the application's console...
wt.exe wsl tmux attach-session -t gdbsession