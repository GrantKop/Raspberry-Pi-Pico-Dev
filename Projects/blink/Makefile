# Simple Makefile wrapper for Pico C++ project

# Where to put CMake's build files
BUILD_DIR := build

# Default target: build the UF2
all: $(BUILD_DIR)/blink.uf2

# Configure + build using CMake
$(BUILD_DIR)/blink.uf2: CMakeLists.txt main.cpp
	@echo "==> Configuring build directory: $(BUILD_DIR)"
	cmake -B $(BUILD_DIR) -S .
	@echo "==> Building project"
	cmake --build $(BUILD_DIR) --config Release

# Clean build directory
clean:
	@echo "==> Cleaning build directory"
	rm -rf $(BUILD_DIR)

# Just builds without forcing reconfigure
build:
	@echo "==> Building (no reconfigure)"
	cmake --build $(BUILD_DIR) --config Release

.PHONY: all clean build
