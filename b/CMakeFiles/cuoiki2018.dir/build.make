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
CMAKE_SOURCE_DIR = /home/phungson/hyouteisan

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/phungson/hyouteisan/b

# Include any dependencies generated for this target.
include CMakeFiles/cuoiki2018.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cuoiki2018.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cuoiki2018.dir/flags.make

CMakeFiles/cuoiki2018.dir/ex/cuoiki2018.c.o: CMakeFiles/cuoiki2018.dir/flags.make
CMakeFiles/cuoiki2018.dir/ex/cuoiki2018.c.o: ../ex/cuoiki2018.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/phungson/hyouteisan/b/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cuoiki2018.dir/ex/cuoiki2018.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cuoiki2018.dir/ex/cuoiki2018.c.o   -c /home/phungson/hyouteisan/ex/cuoiki2018.c

CMakeFiles/cuoiki2018.dir/ex/cuoiki2018.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cuoiki2018.dir/ex/cuoiki2018.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/phungson/hyouteisan/ex/cuoiki2018.c > CMakeFiles/cuoiki2018.dir/ex/cuoiki2018.c.i

CMakeFiles/cuoiki2018.dir/ex/cuoiki2018.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cuoiki2018.dir/ex/cuoiki2018.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/phungson/hyouteisan/ex/cuoiki2018.c -o CMakeFiles/cuoiki2018.dir/ex/cuoiki2018.c.s

CMakeFiles/cuoiki2018.dir/ex/cuoiki2018.c.o.requires:

.PHONY : CMakeFiles/cuoiki2018.dir/ex/cuoiki2018.c.o.requires

CMakeFiles/cuoiki2018.dir/ex/cuoiki2018.c.o.provides: CMakeFiles/cuoiki2018.dir/ex/cuoiki2018.c.o.requires
	$(MAKE) -f CMakeFiles/cuoiki2018.dir/build.make CMakeFiles/cuoiki2018.dir/ex/cuoiki2018.c.o.provides.build
.PHONY : CMakeFiles/cuoiki2018.dir/ex/cuoiki2018.c.o.provides

CMakeFiles/cuoiki2018.dir/ex/cuoiki2018.c.o.provides.build: CMakeFiles/cuoiki2018.dir/ex/cuoiki2018.c.o


# Object files for target cuoiki2018
cuoiki2018_OBJECTS = \
"CMakeFiles/cuoiki2018.dir/ex/cuoiki2018.c.o"

# External object files for target cuoiki2018
cuoiki2018_EXTERNAL_OBJECTS =

cuoiki2018: CMakeFiles/cuoiki2018.dir/ex/cuoiki2018.c.o
cuoiki2018: CMakeFiles/cuoiki2018.dir/build.make
cuoiki2018: ../binaries/libigraph.a
cuoiki2018: libfdr/libfdr.a
cuoiki2018: DebugPrintf/libdebug_printf.a
cuoiki2018: CMakeFiles/cuoiki2018.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/phungson/hyouteisan/b/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable cuoiki2018"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cuoiki2018.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cuoiki2018.dir/build: cuoiki2018

.PHONY : CMakeFiles/cuoiki2018.dir/build

CMakeFiles/cuoiki2018.dir/requires: CMakeFiles/cuoiki2018.dir/ex/cuoiki2018.c.o.requires

.PHONY : CMakeFiles/cuoiki2018.dir/requires

CMakeFiles/cuoiki2018.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cuoiki2018.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cuoiki2018.dir/clean

CMakeFiles/cuoiki2018.dir/depend:
	cd /home/phungson/hyouteisan/b && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/phungson/hyouteisan /home/phungson/hyouteisan /home/phungson/hyouteisan/b /home/phungson/hyouteisan/b /home/phungson/hyouteisan/b/CMakeFiles/cuoiki2018.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cuoiki2018.dir/depend

