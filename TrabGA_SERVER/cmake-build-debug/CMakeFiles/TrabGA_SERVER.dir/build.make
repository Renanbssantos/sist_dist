# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /opt/Clion/clion-2018.2.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/Clion/clion-2018.2.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /sapmnt/home/I866982/CLionProjects/TrabGA_SERVER

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /sapmnt/home/I866982/CLionProjects/TrabGA_SERVER/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TrabGA_SERVER.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TrabGA_SERVER.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TrabGA_SERVER.dir/flags.make

CMakeFiles/TrabGA_SERVER.dir/main.c.o: CMakeFiles/TrabGA_SERVER.dir/flags.make
CMakeFiles/TrabGA_SERVER.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/sapmnt/home/I866982/CLionProjects/TrabGA_SERVER/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/TrabGA_SERVER.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TrabGA_SERVER.dir/main.c.o   -c /sapmnt/home/I866982/CLionProjects/TrabGA_SERVER/main.c

CMakeFiles/TrabGA_SERVER.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TrabGA_SERVER.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /sapmnt/home/I866982/CLionProjects/TrabGA_SERVER/main.c > CMakeFiles/TrabGA_SERVER.dir/main.c.i

CMakeFiles/TrabGA_SERVER.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TrabGA_SERVER.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /sapmnt/home/I866982/CLionProjects/TrabGA_SERVER/main.c -o CMakeFiles/TrabGA_SERVER.dir/main.c.s

# Object files for target TrabGA_SERVER
TrabGA_SERVER_OBJECTS = \
"CMakeFiles/TrabGA_SERVER.dir/main.c.o"

# External object files for target TrabGA_SERVER
TrabGA_SERVER_EXTERNAL_OBJECTS =

TrabGA_SERVER: CMakeFiles/TrabGA_SERVER.dir/main.c.o
TrabGA_SERVER: CMakeFiles/TrabGA_SERVER.dir/build.make
TrabGA_SERVER: CMakeFiles/TrabGA_SERVER.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/sapmnt/home/I866982/CLionProjects/TrabGA_SERVER/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable TrabGA_SERVER"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TrabGA_SERVER.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TrabGA_SERVER.dir/build: TrabGA_SERVER

.PHONY : CMakeFiles/TrabGA_SERVER.dir/build

CMakeFiles/TrabGA_SERVER.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TrabGA_SERVER.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TrabGA_SERVER.dir/clean

CMakeFiles/TrabGA_SERVER.dir/depend:
	cd /sapmnt/home/I866982/CLionProjects/TrabGA_SERVER/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /sapmnt/home/I866982/CLionProjects/TrabGA_SERVER /sapmnt/home/I866982/CLionProjects/TrabGA_SERVER /sapmnt/home/I866982/CLionProjects/TrabGA_SERVER/cmake-build-debug /sapmnt/home/I866982/CLionProjects/TrabGA_SERVER/cmake-build-debug /sapmnt/home/I866982/CLionProjects/TrabGA_SERVER/cmake-build-debug/CMakeFiles/TrabGA_SERVER.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TrabGA_SERVER.dir/depend
