# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /workspaces/testproject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspaces/testproject/cmake

# Include any dependencies generated for this target.
include CMakeFiles/energyManager.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/energyManager.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/energyManager.dir/flags.make

CMakeFiles/energyManager.dir/main.c.o: CMakeFiles/energyManager.dir/flags.make
CMakeFiles/energyManager.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/testproject/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/energyManager.dir/main.c.o"
	/usr/xcc/arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/energyManager.dir/main.c.o   -c /workspaces/testproject/main.c

CMakeFiles/energyManager.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/energyManager.dir/main.c.i"
	/usr/xcc/arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /workspaces/testproject/main.c > CMakeFiles/energyManager.dir/main.c.i

CMakeFiles/energyManager.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/energyManager.dir/main.c.s"
	/usr/xcc/arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /workspaces/testproject/main.c -o CMakeFiles/energyManager.dir/main.c.s

CMakeFiles/energyManager.dir/main.c.o.requires:

.PHONY : CMakeFiles/energyManager.dir/main.c.o.requires

CMakeFiles/energyManager.dir/main.c.o.provides: CMakeFiles/energyManager.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/energyManager.dir/build.make CMakeFiles/energyManager.dir/main.c.o.provides.build
.PHONY : CMakeFiles/energyManager.dir/main.c.o.provides

CMakeFiles/energyManager.dir/main.c.o.provides.build: CMakeFiles/energyManager.dir/main.c.o


CMakeFiles/energyManager.dir/cJSON.c.o: CMakeFiles/energyManager.dir/flags.make
CMakeFiles/energyManager.dir/cJSON.c.o: ../cJSON.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/testproject/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/energyManager.dir/cJSON.c.o"
	/usr/xcc/arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/energyManager.dir/cJSON.c.o   -c /workspaces/testproject/cJSON.c

CMakeFiles/energyManager.dir/cJSON.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/energyManager.dir/cJSON.c.i"
	/usr/xcc/arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /workspaces/testproject/cJSON.c > CMakeFiles/energyManager.dir/cJSON.c.i

CMakeFiles/energyManager.dir/cJSON.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/energyManager.dir/cJSON.c.s"
	/usr/xcc/arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /workspaces/testproject/cJSON.c -o CMakeFiles/energyManager.dir/cJSON.c.s

CMakeFiles/energyManager.dir/cJSON.c.o.requires:

.PHONY : CMakeFiles/energyManager.dir/cJSON.c.o.requires

CMakeFiles/energyManager.dir/cJSON.c.o.provides: CMakeFiles/energyManager.dir/cJSON.c.o.requires
	$(MAKE) -f CMakeFiles/energyManager.dir/build.make CMakeFiles/energyManager.dir/cJSON.c.o.provides.build
.PHONY : CMakeFiles/energyManager.dir/cJSON.c.o.provides

CMakeFiles/energyManager.dir/cJSON.c.o.provides.build: CMakeFiles/energyManager.dir/cJSON.c.o


# Object files for target energyManager
energyManager_OBJECTS = \
"CMakeFiles/energyManager.dir/main.c.o" \
"CMakeFiles/energyManager.dir/cJSON.c.o"

# External object files for target energyManager
energyManager_EXTERNAL_OBJECTS =

energyManager: CMakeFiles/energyManager.dir/main.c.o
energyManager: CMakeFiles/energyManager.dir/cJSON.c.o
energyManager: CMakeFiles/energyManager.dir/build.make
energyManager: /work/vcpkg/installed/arm-linux-custom/lib/libprov_auth_client.a
energyManager: /work/vcpkg/installed/arm-linux-custom/debug/lib/libaziotsharedutil.a
energyManager: /work/vcpkg/installed/arm-linux-custom/debug/lib/libumqtt.a
energyManager: /work/vcpkg/installed/arm-linux-custom/debug/lib/libcurl-d.a
energyManager: /work/vcpkg/installed/arm-linux-custom/debug/lib/libz.a
energyManager: /work/vcpkg/installed/arm-linux-custom/lib/libhsm_security_client.a
energyManager: /work/vcpkg/installed/arm-linux-custom/debug/lib/libparson.a
energyManager: /work/vcpkg/installed/arm-linux-custom/debug/lib/libaziotsharedutil.a
energyManager: /work/vcpkg/installed/arm-linux-custom/debug/lib/libcurl-d.a
energyManager: /work/vcpkg/installed/arm-linux-custom/debug/lib/libz.a
energyManager: /work/vcpkg/installed/arm-linux-custom/debug/lib/libssl.a
energyManager: /work/vcpkg/installed/arm-linux-custom/debug/lib/libcrypto.a
energyManager: /work/vcpkg/installed/arm-linux-custom/debug/lib/libssl.a
energyManager: /work/vcpkg/installed/arm-linux-custom/debug/lib/libcrypto.a
energyManager: CMakeFiles/energyManager.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/testproject/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable energyManager"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/energyManager.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/energyManager.dir/build: energyManager

.PHONY : CMakeFiles/energyManager.dir/build

CMakeFiles/energyManager.dir/requires: CMakeFiles/energyManager.dir/main.c.o.requires
CMakeFiles/energyManager.dir/requires: CMakeFiles/energyManager.dir/cJSON.c.o.requires

.PHONY : CMakeFiles/energyManager.dir/requires

CMakeFiles/energyManager.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/energyManager.dir/cmake_clean.cmake
.PHONY : CMakeFiles/energyManager.dir/clean

CMakeFiles/energyManager.dir/depend:
	cd /workspaces/testproject/cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/testproject /workspaces/testproject /workspaces/testproject/cmake /workspaces/testproject/cmake /workspaces/testproject/cmake/CMakeFiles/energyManager.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/energyManager.dir/depend

