# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/actuday/dev/pixel3D

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/actuday/dev/pixel3D/build

# Include any dependencies generated for this target.
include CMakeFiles/application3D.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/application3D.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/application3D.dir/flags.make

CMakeFiles/application3D.dir/include/A1/application3D.cpp.o: CMakeFiles/application3D.dir/flags.make
CMakeFiles/application3D.dir/include/A1/application3D.cpp.o: ../include/A1/application3D.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/actuday/dev/pixel3D/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/application3D.dir/include/A1/application3D.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/application3D.dir/include/A1/application3D.cpp.o -c /home/actuday/dev/pixel3D/include/A1/application3D.cpp

CMakeFiles/application3D.dir/include/A1/application3D.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/application3D.dir/include/A1/application3D.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/actuday/dev/pixel3D/include/A1/application3D.cpp > CMakeFiles/application3D.dir/include/A1/application3D.cpp.i

CMakeFiles/application3D.dir/include/A1/application3D.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/application3D.dir/include/A1/application3D.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/actuday/dev/pixel3D/include/A1/application3D.cpp -o CMakeFiles/application3D.dir/include/A1/application3D.cpp.s

# Object files for target application3D
application3D_OBJECTS = \
"CMakeFiles/application3D.dir/include/A1/application3D.cpp.o"

# External object files for target application3D
application3D_EXTERNAL_OBJECTS =

libapplication3D.a: CMakeFiles/application3D.dir/include/A1/application3D.cpp.o
libapplication3D.a: CMakeFiles/application3D.dir/build.make
libapplication3D.a: CMakeFiles/application3D.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/actuday/dev/pixel3D/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libapplication3D.a"
	$(CMAKE_COMMAND) -P CMakeFiles/application3D.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/application3D.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/application3D.dir/build: libapplication3D.a

.PHONY : CMakeFiles/application3D.dir/build

CMakeFiles/application3D.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/application3D.dir/cmake_clean.cmake
.PHONY : CMakeFiles/application3D.dir/clean

CMakeFiles/application3D.dir/depend:
	cd /home/actuday/dev/pixel3D/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/actuday/dev/pixel3D /home/actuday/dev/pixel3D /home/actuday/dev/pixel3D/build /home/actuday/dev/pixel3D/build /home/actuday/dev/pixel3D/build/CMakeFiles/application3D.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/application3D.dir/depend
