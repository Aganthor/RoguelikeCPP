# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.11

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
CMAKE_SOURCE_DIR = /home/lucb/Programming/cpp/RogueLikeCPP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lucb/Programming/cpp/RogueLikeCPP/build

# Include any dependencies generated for this target.
include ecs/CMakeFiles/ecs.dir/depend.make

# Include the progress variables for this target.
include ecs/CMakeFiles/ecs.dir/progress.make

# Include the compile flags for this target's objects.
include ecs/CMakeFiles/ecs.dir/flags.make

ecs/CMakeFiles/ecs.dir/Entity.cpp.o: ecs/CMakeFiles/ecs.dir/flags.make
ecs/CMakeFiles/ecs.dir/Entity.cpp.o: ../ecs/Entity.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lucb/Programming/cpp/RogueLikeCPP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object ecs/CMakeFiles/ecs.dir/Entity.cpp.o"
	cd /home/lucb/Programming/cpp/RogueLikeCPP/build/ecs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ecs.dir/Entity.cpp.o -c /home/lucb/Programming/cpp/RogueLikeCPP/ecs/Entity.cpp

ecs/CMakeFiles/ecs.dir/Entity.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ecs.dir/Entity.cpp.i"
	cd /home/lucb/Programming/cpp/RogueLikeCPP/build/ecs && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lucb/Programming/cpp/RogueLikeCPP/ecs/Entity.cpp > CMakeFiles/ecs.dir/Entity.cpp.i

ecs/CMakeFiles/ecs.dir/Entity.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ecs.dir/Entity.cpp.s"
	cd /home/lucb/Programming/cpp/RogueLikeCPP/build/ecs && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lucb/Programming/cpp/RogueLikeCPP/ecs/Entity.cpp -o CMakeFiles/ecs.dir/Entity.cpp.s

# Object files for target ecs
ecs_OBJECTS = \
"CMakeFiles/ecs.dir/Entity.cpp.o"

# External object files for target ecs
ecs_EXTERNAL_OBJECTS =

ecs/libecs.a: ecs/CMakeFiles/ecs.dir/Entity.cpp.o
ecs/libecs.a: ecs/CMakeFiles/ecs.dir/build.make
ecs/libecs.a: ecs/CMakeFiles/ecs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lucb/Programming/cpp/RogueLikeCPP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libecs.a"
	cd /home/lucb/Programming/cpp/RogueLikeCPP/build/ecs && $(CMAKE_COMMAND) -P CMakeFiles/ecs.dir/cmake_clean_target.cmake
	cd /home/lucb/Programming/cpp/RogueLikeCPP/build/ecs && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ecs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ecs/CMakeFiles/ecs.dir/build: ecs/libecs.a

.PHONY : ecs/CMakeFiles/ecs.dir/build

ecs/CMakeFiles/ecs.dir/clean:
	cd /home/lucb/Programming/cpp/RogueLikeCPP/build/ecs && $(CMAKE_COMMAND) -P CMakeFiles/ecs.dir/cmake_clean.cmake
.PHONY : ecs/CMakeFiles/ecs.dir/clean

ecs/CMakeFiles/ecs.dir/depend:
	cd /home/lucb/Programming/cpp/RogueLikeCPP/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lucb/Programming/cpp/RogueLikeCPP /home/lucb/Programming/cpp/RogueLikeCPP/ecs /home/lucb/Programming/cpp/RogueLikeCPP/build /home/lucb/Programming/cpp/RogueLikeCPP/build/ecs /home/lucb/Programming/cpp/RogueLikeCPP/build/ecs/CMakeFiles/ecs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ecs/CMakeFiles/ecs.dir/depend

