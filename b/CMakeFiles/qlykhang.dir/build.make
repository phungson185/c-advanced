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
include CMakeFiles/qlykhang.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/qlykhang.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/qlykhang.dir/flags.make

CMakeFiles/qlykhang.dir/ex/quan_ly_kho_hang/quanlykhachhang.c.o: CMakeFiles/qlykhang.dir/flags.make
CMakeFiles/qlykhang.dir/ex/quan_ly_kho_hang/quanlykhachhang.c.o: ../ex/quan_ly_kho_hang/quanlykhachhang.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/phungson/hyouteisan/b/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/qlykhang.dir/ex/quan_ly_kho_hang/quanlykhachhang.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/qlykhang.dir/ex/quan_ly_kho_hang/quanlykhachhang.c.o   -c /home/phungson/hyouteisan/ex/quan_ly_kho_hang/quanlykhachhang.c

CMakeFiles/qlykhang.dir/ex/quan_ly_kho_hang/quanlykhachhang.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/qlykhang.dir/ex/quan_ly_kho_hang/quanlykhachhang.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/phungson/hyouteisan/ex/quan_ly_kho_hang/quanlykhachhang.c > CMakeFiles/qlykhang.dir/ex/quan_ly_kho_hang/quanlykhachhang.c.i

CMakeFiles/qlykhang.dir/ex/quan_ly_kho_hang/quanlykhachhang.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/qlykhang.dir/ex/quan_ly_kho_hang/quanlykhachhang.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/phungson/hyouteisan/ex/quan_ly_kho_hang/quanlykhachhang.c -o CMakeFiles/qlykhang.dir/ex/quan_ly_kho_hang/quanlykhachhang.c.s

CMakeFiles/qlykhang.dir/ex/quan_ly_kho_hang/quanlykhachhang.c.o.requires:

.PHONY : CMakeFiles/qlykhang.dir/ex/quan_ly_kho_hang/quanlykhachhang.c.o.requires

CMakeFiles/qlykhang.dir/ex/quan_ly_kho_hang/quanlykhachhang.c.o.provides: CMakeFiles/qlykhang.dir/ex/quan_ly_kho_hang/quanlykhachhang.c.o.requires
	$(MAKE) -f CMakeFiles/qlykhang.dir/build.make CMakeFiles/qlykhang.dir/ex/quan_ly_kho_hang/quanlykhachhang.c.o.provides.build
.PHONY : CMakeFiles/qlykhang.dir/ex/quan_ly_kho_hang/quanlykhachhang.c.o.provides

CMakeFiles/qlykhang.dir/ex/quan_ly_kho_hang/quanlykhachhang.c.o.provides.build: CMakeFiles/qlykhang.dir/ex/quan_ly_kho_hang/quanlykhachhang.c.o


# Object files for target qlykhang
qlykhang_OBJECTS = \
"CMakeFiles/qlykhang.dir/ex/quan_ly_kho_hang/quanlykhachhang.c.o"

# External object files for target qlykhang
qlykhang_EXTERNAL_OBJECTS =

qlykhang: CMakeFiles/qlykhang.dir/ex/quan_ly_kho_hang/quanlykhachhang.c.o
qlykhang: CMakeFiles/qlykhang.dir/build.make
qlykhang: ../binaries/libigraph.a
qlykhang: libfdr/libfdr.a
qlykhang: DebugPrintf/libdebug_printf.a
qlykhang: CMakeFiles/qlykhang.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/phungson/hyouteisan/b/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable qlykhang"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/qlykhang.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/qlykhang.dir/build: qlykhang

.PHONY : CMakeFiles/qlykhang.dir/build

CMakeFiles/qlykhang.dir/requires: CMakeFiles/qlykhang.dir/ex/quan_ly_kho_hang/quanlykhachhang.c.o.requires

.PHONY : CMakeFiles/qlykhang.dir/requires

CMakeFiles/qlykhang.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/qlykhang.dir/cmake_clean.cmake
.PHONY : CMakeFiles/qlykhang.dir/clean

CMakeFiles/qlykhang.dir/depend:
	cd /home/phungson/hyouteisan/b && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/phungson/hyouteisan /home/phungson/hyouteisan /home/phungson/hyouteisan/b /home/phungson/hyouteisan/b /home/phungson/hyouteisan/b/CMakeFiles/qlykhang.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/qlykhang.dir/depend

