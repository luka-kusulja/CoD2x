# ==========================
# Directories and Files
# ==========================

# Output directories
WIN_BIN_DIR = bin\windows
LINUX_BIN_DIR = bin\linux

# Targets
MSS32_WIN_TARGET = $(WIN_BIN_DIR)\mss32.dll
COD2X_WIN_TARGET = $(WIN_BIN_DIR)\CoD2x_v1_test1.dll
COD2X_LINUX_TARGET = $(LINUX_BIN_DIR)\libCoD2x.so

# Source and object directories
MSS32_SRC_DIR = src\mss32
MSS32_WIN_OBJ_DIR = obj\windows\mss32

COD2X_SRC_DIR = src\CoD2x
COD2X_WIN_OBJ_DIR = obj\windows\CoD2x
COD2X_LINUX_OBJ_DIR = obj\linux\CoD2x

# Source files
MSS32_C_SOURCES = $(wildcard $(MSS32_SRC_DIR)/*.c)
COD2X_C_SOURCES = $(wildcard $(COD2X_SRC_DIR)/*.c)

MSS32_ASM_SOURCES = $(wildcard $(MSS32_SRC_DIR)/*.asm)

# Platform-specific object files
MSS32_WIN_OBJECTS = $(patsubst $(MSS32_SRC_DIR)/%.c, $(MSS32_WIN_OBJ_DIR)/%.o, $(MSS32_C_SOURCES)) \
                    $(patsubst $(MSS32_SRC_DIR)/%.asm, $(MSS32_WIN_OBJ_DIR)/%.o, $(MSS32_ASM_SOURCES))
COD2X_WIN_OBJECTS = $(patsubst $(COD2X_SRC_DIR)/%.c, $(COD2X_WIN_OBJ_DIR)/%.o, $(COD2X_C_SOURCES))
COD2X_LINUX_OBJECTS = $(patsubst $(COD2X_SRC_DIR)/%.c, $(COD2X_LINUX_OBJ_DIR)/%.o, $(COD2X_C_SOURCES))

# ==========================
# Compilation Settings
# ==========================

CFLAGS = -Wall -Wextra -Wno-unused-parameter -g -m32 -shared -std=c99
# Flag explanations:
# -Wall: Enable all compiler warnings
# -Wextra: Enable extra compiler warnings
# -Wno-unused-parameter: Disable warnings for unused function parameters
# -g: Include debugging information
# -m32: Generate 32-bit code
# -shared: Create a shared library (windows: DLL, linux: SO)
# -std=c99: Use the C99 standard

# Windows toolchain
WIN_CC = gcc.exe
WIN_AS = nasm
WIN_CFLAGS = $(CFLAGS) -mwindows  -static
WIN_ASFLAGS = -f win32	# Output format for NASM (32-bit Windows)
WIN_LIBS = -lkernel32
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
all: build_mss32_win build_cod2x_win build_cod2x_linux
	@echo "Build completed for all targets."

# Build MSS32 and CoD2x for Windows
build_mss_cod2x_win: build_mss32_win build_cod2x_win
	@echo "Build completed for MSS32 and CoD2x (Windows)."

# MSS32 Windows target
build_mss32_win: $(MSS32_WIN_TARGET)
	@echo "MSS32 (Windows) build complete."

$(MSS32_WIN_TARGET): $(MSS32_WIN_OBJECTS)
	@echo "Linking $@..."
	$(WIN_CC) $(WIN_CFLAGS) -o $@ $^ $(WIN_LIBS) $(MSS32_SRC_DIR)/mss32.def

$(MSS32_WIN_OBJ_DIR)/%.o: $(MSS32_SRC_DIR)/%.c | $(MSS32_WIN_OBJ_DIR)
	@echo "Compiling $< for MSS32 (Windows)..."
	$(WIN_CC) $(WIN_CFLAGS) -MMD -MP -c -o $@ $<

$(MSS32_WIN_OBJ_DIR)/%.o: $(MSS32_SRC_DIR)/%.asm | $(MSS32_WIN_OBJ_DIR)
	@echo "Assembling $< for MSS32 (Windows)..."
	$(WIN_AS) $(WIN_ASFLAGS) $< -o $@

# CoD2x Windows target
build_cod2x_win: $(COD2X_WIN_TARGET)
	@echo "CoD2x (Windows) build complete."

$(COD2X_WIN_TARGET): $(COD2X_WIN_OBJECTS)
	@echo "Linking $@..."
	$(WIN_CC) $(WIN_CFLAGS) -o $@ $^ $(WIN_LIBS)

$(COD2X_WIN_OBJ_DIR)/%.o: $(COD2X_SRC_DIR)/%.c | $(COD2X_WIN_OBJ_DIR)
	@echo "Compiling $< for CoD2x (Windows)..."
	$(WIN_CC) $(WIN_CFLAGS) -MMD -MP -c -o $@ $<

# CoD2x Linux target
build_cod2x_linux: $(COD2X_LINUX_TARGET)
	@echo "CoD2x (Linux) build complete."

$(COD2X_LINUX_TARGET): $(COD2X_LINUX_OBJECTS) | $(LINUX_BIN_DIR)
	@echo "Linking $@..."
	$(LINUX_CC) $(LINUX_CFLAGS) -o $@ $^ $(LINUX_LIBS)

$(COD2X_LINUX_OBJ_DIR)/%.o: $(COD2X_SRC_DIR)/%.c | $(COD2X_LINUX_OBJ_DIR)
	@echo "Compiling $< for CoD2x (Linux)..."
	$(LINUX_CC) $(LINUX_CFLAGS) -MMD -MP -c -o $@ $<

# Include dependency files
-include $(MSS32_WIN_OBJ_DIR)/*.d
-include $(COD2X_WIN_OBJ_DIR)/*.d
-include $(COD2X_LINUX_OBJ_DIR)/*.d

# Create directories
$(MSS32_WIN_OBJ_DIR) $(COD2X_WIN_OBJ_DIR) $(COD2X_LINUX_OBJ_DIR) $(WIN_BIN_DIR) $(LINUX_BIN_DIR):
	@if not exist $@ mkdir $@

# ==========================
# Cleaning Up
# ==========================

clean:
	@echo "Cleaning up..."
	@if exist $(MSS32_WIN_OBJ_DIR)\*.o del /Q $(MSS32_WIN_OBJ_DIR)\*.o
	@if exist $(MSS32_WIN_OBJ_DIR)\*.d del /Q $(MSS32_WIN_OBJ_DIR)\*.d
	@if exist $(COD2X_WIN_OBJ_DIR)\*.o del /Q $(COD2X_WIN_OBJ_DIR)\*.o
	@if exist $(COD2X_WIN_OBJ_DIR)\*.d del /Q $(COD2X_WIN_OBJ_DIR)\*.d
	@if exist $(COD2X_LINUX_OBJ_DIR)\*.o del /Q $(COD2X_LINUX_OBJ_DIR)\*.o
	@if exist $(COD2X_LINUX_OBJ_DIR)\*.d del /Q $(COD2X_LINUX_OBJ_DIR)\*.d
	@if exist $(MSS32_WIN_TARGET) del /Q $(MSS32_WIN_TARGET)
	@if exist $(COD2X_WIN_TARGET) del /Q $(COD2X_WIN_TARGET)
	@if exist $(COD2X_LINUX_TARGET) del /Q $(COD2X_LINUX_TARGET)
	@echo "Done."

# ==========================
# Phony Targets
# ==========================

.PHONY: all clean build_mss32_win build_cod2x_win build_cod2x_linux
