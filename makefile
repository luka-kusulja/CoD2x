# ==========================
# Directories and Files
# ==========================
VERSION = v1_test2

# Output directories
WIN_BIN_DIR = bin\windows
LINUX_BIN_DIR = bin\linux

# Targets
MSS32_WIN_TARGET = $(WIN_BIN_DIR)\mss32.dll
COD2X_LINUX_TARGET = $(LINUX_BIN_DIR)\libCoD2x.so

# Source and object directories
MSS32_SRC_DIR = src\mss32
MSS32_WIN_OBJ_DIR = obj\windows\mss32
COD2X_LINUX_OBJ_DIR = obj\linux\CoD2x

# Define source files and target paths
ZIP_EXEC = 7za.exe
ZIP_WIN_DIR = zip\windows
ZIP_WIN_FILES = $(MSS32_WIN_TARGET) bin\windows\mss32_original.dll $(COD2X_WIN_TARGET)
ZIP_WIN_NAME = CoD2x_$(VERSION)_windows.zip
ZIP_WIN_OUTPUT = $(ZIP_WIN_DIR)\$(ZIP_WIN_NAME)

# Source files
MSS32_C_SOURCES = $(wildcard $(MSS32_SRC_DIR)/*.cpp)

MSS32_ASM_SOURCES = $(wildcard $(MSS32_SRC_DIR)/*.asm)

# Platform-specific object files
MSS32_WIN_OBJECTS = $(patsubst $(MSS32_SRC_DIR)/%.cpp, $(MSS32_WIN_OBJ_DIR)/%.o, $(MSS32_C_SOURCES)) \
                    $(patsubst $(MSS32_SRC_DIR)/%.asm, $(MSS32_WIN_OBJ_DIR)/%.o, $(MSS32_ASM_SOURCES))
COD2X_LINUX_OBJECTS = $(patsubst $(COD2X_SRC_DIR)/%.cpp, $(COD2X_LINUX_OBJ_DIR)/%.o, $(COD2X_C_SOURCES))

# ==========================
# Compilation Settings
# ==========================

CFLAGS = -Wall -Wextra -Wno-unused-parameter -g -m32 -shared -lstdc++
# Flag explanations:
# -Wall: Enable all compiler warnings
# -Wextra: Enable extra compiler warnings
# -Wno-unused-parameter: Disable warnings for unused function parameters
# -g: Include debugging information
# -m32: Generate 32-bit code
# -shared: Create a shared library (windows: DLL, linux: SO)
# -lstdc++: Link with the C++ standard library

# Windows toolchain
WIN_CC = gcc.exe
WIN_AS = nasm
WIN_CFLAGS = $(CFLAGS) -mwindows -static
WIN_ASFLAGS = -f win32	# Output format for NASM (32-bit Windows)
WIN_LIBS = -lkernel32 -lwininet
# -mwindows: Link with the Windows GUI subsystem (no console)
# -static: Link libraries statically

# Linux toolchain
LINUX_CC = gcc
LINUX_CFLAGS = $(CFLAGS) -fPIC -shared
LINUX_LIBS = -ldl -pthread
# -fPIC: Generate position-independent code
# -shared: Create a shared library (SO)

# ==========================
# Build Targets and Rules
# ==========================

# Default target
all: build_mss32_win build_cod2x_linux
	@echo "Build completed for all targets."


# MSS32 Windows target
build_mss32_win: $(MSS32_WIN_TARGET)
	@echo "MSS32 (Windows) build complete."

$(MSS32_WIN_TARGET): $(MSS32_WIN_OBJECTS)
	@echo "Linking $@..."
	$(WIN_CC) $(WIN_CFLAGS) -o $@ $^ $(WIN_LIBS) $(MSS32_SRC_DIR)/mss32.def

$(MSS32_WIN_OBJ_DIR)/%.o: $(MSS32_SRC_DIR)/%.cpp | $(MSS32_WIN_OBJ_DIR)
	@echo "Compiling $< for MSS32 (Windows)..."
	$(WIN_CC) $(WIN_CFLAGS) -MMD -MP -c -o $@ $<

$(MSS32_WIN_OBJ_DIR)/%.o: $(MSS32_SRC_DIR)/%.asm | $(MSS32_WIN_OBJ_DIR)
	@echo "Assembling $< for MSS32 (Windows)..."
	$(WIN_AS) $(WIN_ASFLAGS) $< -o $@


# CoD2x Linux target
build_cod2x_linux: $(COD2X_LINUX_TARGET)
	@echo "CoD2x (Linux) build complete."

$(COD2X_LINUX_TARGET): $(COD2X_LINUX_OBJECTS) | $(LINUX_BIN_DIR)
	@echo "Linking $@..."
	$(LINUX_CC) $(LINUX_CFLAGS) -o $@ $^ $(LINUX_LIBS)

$(COD2X_LINUX_OBJ_DIR)/%.o: $(COD2X_SRC_DIR)/%.cpp | $(COD2X_LINUX_OBJ_DIR)
	@echo "Compiling $< for CoD2x (Linux)..."
	$(LINUX_CC) $(LINUX_CFLAGS) -MMD -MP -c -o $@ $<

# Include dependency files
-include $(MSS32_WIN_OBJ_DIR)/*.d
-include $(COD2X_LINUX_OBJ_DIR)/*.d

# Create directories
$(MSS32_WIN_OBJ_DIR) $(COD2X_LINUX_OBJ_DIR) $(WIN_BIN_DIR) $(LINUX_BIN_DIR):
	@if not exist $@ mkdir $@


# Rule to create the zip file
$(ZIP_WIN_OUTPUT): $(ZIP_WIN_FILES) | $(ZIP_WIN_DIR)
	@echo "Copying files to $(ZIP_WIN_DIR)..."
	@for %%f in ($(ZIP_WIN_FILES)) do copy %%f $(ZIP_WIN_DIR) >nul
	@echo "Creating zip archive $(ZIP_WIN_OUTPUT) using 7-Zip..."
	@echo $(ZIP_EXEC) a -tzip "$(ZIP_WIN_OUTPUT)" "$(ZIP_WIN_DIR)\*"
	@cd $(ZIP_WIN_DIR) && $(ZIP_EXEC) a -tzip "$(ZIP_WIN_NAME)" *
	@echo "Zip archive created at $(ZIP_WIN_OUTPUT)."

# Rule to ensure the zip directory exists
$(ZIP_WIN_DIR):
	@echo "Creating directory $(ZIP_WIN_DIR)..."
	@mkdir -p $(ZIP_WIN_DIR)



# ==========================
# Zip output files
# ==========================
zip_win: zip_win_clean $(ZIP_WIN_OUTPUT)

zip_win_clean:
	@echo "Cleaning up $(ZIP_WIN_DIR), preserving manual..."
	@if exist $(ZIP_WIN_DIR) ( \
	    for %%f in ($(ZIP_WIN_DIR)\*) do if /I not "%%~nxf"=="CoD2x Installation and uninstallation manual.txt" del /Q "%%f" \
	)
	@echo "Cleanup up $(ZIP_WIN_DIR) complete."


# ==========================
# Cleaning Up
# ==========================

clean: zip_win_clean
	@echo "Cleaning up build files..."
	@if exist $(MSS32_WIN_OBJ_DIR)\*.o del /Q $(MSS32_WIN_OBJ_DIR)\*.o
	@if exist $(MSS32_WIN_OBJ_DIR)\*.d del /Q $(MSS32_WIN_OBJ_DIR)\*.d
	@if exist $(COD2X_LINUX_OBJ_DIR)\*.o del /Q $(COD2X_LINUX_OBJ_DIR)\*.o
	@if exist $(COD2X_LINUX_OBJ_DIR)\*.d del /Q $(COD2X_LINUX_OBJ_DIR)\*.d
	@if exist $(MSS32_WIN_TARGET) del /Q $(MSS32_WIN_TARGET)
	@if exist $(COD2X_LINUX_TARGET) del /Q $(COD2X_LINUX_TARGET)
	@echo "Done."

# ==========================
# Phony Targets
# ==========================

.PHONY: all clean build_mss32_win build_cod2x_linux zip_win zip_win_clean