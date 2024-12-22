# ==========================
# Directories and Files
# ==========================
VERSION = v1_test5

# Output directories
WIN_BIN_DIR = bin/windows
LINUX_BIN_DIR = bin/linux

# Targets
WIN_MSS32_TARGET = $(WIN_BIN_DIR)/mss32.dll
LINUX_TARGET = $(LINUX_BIN_DIR)/libCoD2x.so

# Source and object directories
WIN_MSS32_SRC_DIR = src/mss32
WIN_MSS32_OBJ_DIR = obj/mss32
LINUX_OBJ_DIR = obj/linux
LINUX_SRC_DIR = src/linux
SHARED_SRC_DIR = src/shared
SHARED_OBJ_DIR = obj/shared

# Define source files and target paths
ZIP_EXEC = 7za.exe
ZIP_WIN_DIR = zip/windows
ZIP_WIN_FILES = $(WIN_MSS32_TARGET) bin/windows/mss32_original.dll $(COD2X_WIN_TARGET)
ZIP_WIN_NAME = CoD2x_$(VERSION)_windows.zip
ZIP_WIN_OUTPUT = $(ZIP_WIN_DIR)/$(ZIP_WIN_NAME)

# Source files
MSS32_C_SOURCES = $(wildcard $(WIN_MSS32_SRC_DIR)/*.cpp)
MSS32_ASM_SOURCES = $(wildcard $(WIN_MSS32_SRC_DIR)/*.asm)
LINUX_C_SOURCES = $(wildcard $(LINUX_SRC_DIR)/*.cpp)
SHARED_C_SOURCES = $(wildcard $(SHARED_SRC_DIR)/*.cpp)

# Shared object files for Windows and Linux
SHARED_WIN_OBJECTS = $(patsubst $(SHARED_SRC_DIR)/%.cpp, $(WIN_MSS32_OBJ_DIR)/shared_%.o, $(SHARED_C_SOURCES))
SHARED_LINUX_OBJECTS = $(patsubst $(SHARED_SRC_DIR)/%.cpp, $(LINUX_OBJ_DIR)/shared_%.o, $(SHARED_C_SOURCES))

# Platform-specific object files
WIN_MSS32_OBJECTS = $(patsubst $(WIN_MSS32_SRC_DIR)/%.cpp, $(WIN_MSS32_OBJ_DIR)/%.o, $(MSS32_C_SOURCES)) \
                    $(patsubst $(WIN_MSS32_SRC_DIR)/%.asm, $(WIN_MSS32_OBJ_DIR)/%.o, $(MSS32_ASM_SOURCES)) \
					$(SHARED_WIN_OBJECTS)
LINUX_OBJECTS = $(patsubst $(LINUX_SRC_DIR)/%.cpp, $(LINUX_OBJ_DIR)/%.o, $(LINUX_C_SOURCES)) \
				$(SHARED_LINUX_OBJECTS)

# ==========================
# Compilation Settings
# ==========================

# Compilation flags
CFLAGS = -Wall -Wextra -Wno-unused-parameter -g -m32 -lstdc++ -O0
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
WIN_LFLAGS = -shared -m32
WIN_ASFLAGS = -f win32	# Output format for NASM (32-bit Windows)
WIN_LIBS = -lkernel32 -lwininet
# -mwindows: Link with the Windows GUI subsystem (no console)
# -static: Link libraries statically

# Linux toolchain
LINUX_CC = gcc
LINUX_CFLAGS = $(CFLAGS) -fPIC
LINUX_LFLAGS = -shared -m32
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
build_mss32_win: $(WIN_MSS32_TARGET)
	@echo "MSS32 (Windows) build complete."

$(WIN_MSS32_TARGET): $(WIN_MSS32_OBJECTS)
	@echo "Linking $@..."
	$(WIN_CC) $(WIN_LFLAGS) -o $@ $^ $(WIN_LIBS) $(WIN_MSS32_SRC_DIR)/mss32.def

$(WIN_MSS32_OBJ_DIR)/%.o: $(WIN_MSS32_SRC_DIR)/%.cpp | $(WIN_MSS32_OBJ_DIR)
	@echo "Compiling $< for MSS32 (Windows)..."
	$(WIN_CC) $(WIN_CFLAGS) -MMD -MP -c -o $@ $<

$(WIN_MSS32_OBJ_DIR)/%.o: $(WIN_MSS32_SRC_DIR)/%.asm | $(WIN_MSS32_OBJ_DIR)
	@echo "Assembling $< for MSS32 (Windows)..."
	$(WIN_AS) $(WIN_ASFLAGS) $< -o $@


# CoD2x Linux target
build_cod2x_linux: $(LINUX_TARGET)
	@echo "CoD2x (Linux) build complete."

$(LINUX_TARGET): $(LINUX_OBJECTS)
	@echo "Linking to $@..."
	$(LINUX_CC) $(LINUX_LFLAGS) -o $@ $^ $(LINUX_LIBS)

$(LINUX_OBJ_DIR)/%.o: $(LINUX_SRC_DIR)/%.cpp | $(LINUX_OBJ_DIR)
	@echo "Compiling $< for CoD2x (Linux)..."
	$(LINUX_CC) $(LINUX_CFLAGS) -MMD -MP -c -o $@ $<



# Compile shared functionality objects for Windows
$(WIN_MSS32_OBJ_DIR)/shared_%.o: $(SHARED_SRC_DIR)/%.cpp | $(WIN_MSS32_OBJ_DIR)
	@echo "Compiling $< for shared functionality (Windows)..."
	$(WIN_CC) $(WIN_CFLAGS) -MMD -MP -c -o $@ $<

# Compile shared functionality objects for Linux
$(LINUX_OBJ_DIR)/shared_%.o: $(SHARED_SRC_DIR)/%.cpp | $(LINUX_OBJ_DIR)
	@echo "Compiling $< for shared functionality (Linux)..."
	$(LINUX_CC) $(LINUX_CFLAGS) -MMD -MP -c -o $@ $<



# Include dependency files
-include $(WIN_MSS32_OBJ_DIR)/*.d
-include $(LINUX_OBJ_DIR)/*.d


# Create directories (Windows)
$(WIN_MSS32_OBJ_DIR) $(WIN_BIN_DIR):
	@if not exist $(subst /,\, $@) mkdir $(subst /,\, $@)

# Create directories (Linux)
$(LINUX_OBJ_DIR) $(LINUX_BIN_DIR):
	@mkdir -p $@


# Rule to create the zip file
$(ZIP_WIN_OUTPUT): $(ZIP_WIN_FILES) | $(ZIP_WIN_DIR)
	@echo "Copying files to $(subst /,\, $(ZIP_WIN_DIR))..."
	@for %%f in ($(subst /,\, $(ZIP_WIN_FILES))) do copy %%f $(subst /,\, $(ZIP_WIN_DIR)) >nul
	@echo "Creating zip archive $(subst /,\, $(ZIP_WIN_OUTPUT)) using 7-Zip..."
	@echo $(ZIP_EXEC) a -tzip "$(subst /,\, $(ZIP_WIN_OUTPUT))" "$(subst /,\, $(ZIP_WIN_DIR))\*"
	@cd $(subst /,\, $(ZIP_WIN_DIR)) && $(ZIP_EXEC) a -tzip "$(ZIP_WIN_NAME)" *
	@echo "Zip archive created at $(subst /,\, $(ZIP_WIN_OUTPUT))."

# Rule to ensure the zip directory exists
$(ZIP_WIN_DIR):
	@echo "Creating directory $(ZIP_WIN_DIR)..."
	@mkdir -p $(ZIP_WIN_DIR)



# ==========================
# Zip output files
# ==========================
zip_win: zip_win_clean $(ZIP_WIN_OUTPUT)

zip_win_clean:
	@echo "Cleaning up $(subst /,\, $(ZIP_WIN_DIR)), preserving manual..."
	@if exist $(subst /,\, $(ZIP_WIN_DIR)) ( \
	    for %%f in ($(subst /,\, $(ZIP_WIN_DIR))\*) do ( \
	        if /I not "%%~nxf"=="CoD2x Installation and uninstallation manual.txt" del /Q "%%f" \
	    ) \
	)

# ==========================
# Cleaning Up
# ==========================

clean: zip_win_clean
	@echo "Cleaning up build files..."
	@if exist $(subst /,\, $(WIN_MSS32_OBJ_DIR))\*.o del /Q $(subst /,\, $(WIN_MSS32_OBJ_DIR))\*.o
	@if exist $(subst /,\, $(WIN_MSS32_OBJ_DIR))\*.d del /Q $(subst /,\, $(WIN_MSS32_OBJ_DIR))\*.d
	@if exist $(subst /,\, $(LINUX_OBJ_DIR))\*.o del /Q $(subst /,\, $(LINUX_OBJ_DIR))\*.o
	@if exist $(subst /,\, $(LINUX_OBJ_DIR))\*.d del /Q $(subst /,\, $(LINUX_OBJ_DIR))\*.d
	@if exist $(subst /,\, $(WIN_MSS32_TARGET)) del /Q $(subst /,\, $(WIN_MSS32_TARGET))
	@if exist $(subst /,\, $(LINUX_TARGET)) del /Q $(subst /,\, $(LINUX_TARGET))
	@echo "Done."

# ==========================
# Phony Targets
# ==========================

.PHONY: all clean build_mss32_win build_cod2x_linux zip_win zip_win_clean