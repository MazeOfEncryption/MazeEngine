# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = C:/dev/msys64/mingw64/bin/cmake.exe

# The command to remove a file.
RM = C:/dev/msys64/mingw64/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:/David/Programming/Github/MazeEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:/David/Programming/Github/MazeEngine/build

# Utility rule file for Nightly.

# Include the progress variables for this target.
include CMakeFiles/Nightly.dir/progress.make

CMakeFiles/Nightly:
	cd C:/David/Programming/Github/MazeEngine/build && C:/dev/msys64/mingw64/bin/ctest.exe -D Nightly

Nightly: CMakeFiles/Nightly
Nightly: CMakeFiles/Nightly.dir/build.make

.PHONY : Nightly

# Rule to build all files generated by this target.
CMakeFiles/Nightly.dir/build: Nightly

.PHONY : CMakeFiles/Nightly.dir/build

CMakeFiles/Nightly.dir/clean:
	cd C:/David/Programming/Github/MazeEngine/build && $(CMAKE_COMMAND) -P CMakeFiles/Nightly.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Nightly.dir/clean

CMakeFiles/Nightly.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" C:/David/Programming/Github/MazeEngine C:/David/Programming/Github/MazeEngine C:/David/Programming/Github/MazeEngine/build C:/David/Programming/Github/MazeEngine/build C:/David/Programming/Github/MazeEngine/build/CMakeFiles/Nightly.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Nightly.dir/depend

