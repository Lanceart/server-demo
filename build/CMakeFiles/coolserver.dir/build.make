# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/lance/Desktop/server-demo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lance/Desktop/server-demo/build

# Include any dependencies generated for this target.
include CMakeFiles/coolserver.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/coolserver.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/coolserver.dir/flags.make

CMakeFiles/coolserver.dir/coolserver/log.cc.o: CMakeFiles/coolserver.dir/flags.make
CMakeFiles/coolserver.dir/coolserver/log.cc.o: ../coolserver/log.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lance/Desktop/server-demo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/coolserver.dir/coolserver/log.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/coolserver.dir/coolserver/log.cc.o -c /home/lance/Desktop/server-demo/coolserver/log.cc

CMakeFiles/coolserver.dir/coolserver/log.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/coolserver.dir/coolserver/log.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lance/Desktop/server-demo/coolserver/log.cc > CMakeFiles/coolserver.dir/coolserver/log.cc.i

CMakeFiles/coolserver.dir/coolserver/log.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/coolserver.dir/coolserver/log.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lance/Desktop/server-demo/coolserver/log.cc -o CMakeFiles/coolserver.dir/coolserver/log.cc.s

CMakeFiles/coolserver.dir/coolserver/util.cc.o: CMakeFiles/coolserver.dir/flags.make
CMakeFiles/coolserver.dir/coolserver/util.cc.o: ../coolserver/util.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lance/Desktop/server-demo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/coolserver.dir/coolserver/util.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/coolserver.dir/coolserver/util.cc.o -c /home/lance/Desktop/server-demo/coolserver/util.cc

CMakeFiles/coolserver.dir/coolserver/util.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/coolserver.dir/coolserver/util.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lance/Desktop/server-demo/coolserver/util.cc > CMakeFiles/coolserver.dir/coolserver/util.cc.i

CMakeFiles/coolserver.dir/coolserver/util.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/coolserver.dir/coolserver/util.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lance/Desktop/server-demo/coolserver/util.cc -o CMakeFiles/coolserver.dir/coolserver/util.cc.s

CMakeFiles/coolserver.dir/coolserver/config.cc.o: CMakeFiles/coolserver.dir/flags.make
CMakeFiles/coolserver.dir/coolserver/config.cc.o: ../coolserver/config.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lance/Desktop/server-demo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/coolserver.dir/coolserver/config.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/coolserver.dir/coolserver/config.cc.o -c /home/lance/Desktop/server-demo/coolserver/config.cc

CMakeFiles/coolserver.dir/coolserver/config.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/coolserver.dir/coolserver/config.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lance/Desktop/server-demo/coolserver/config.cc > CMakeFiles/coolserver.dir/coolserver/config.cc.i

CMakeFiles/coolserver.dir/coolserver/config.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/coolserver.dir/coolserver/config.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lance/Desktop/server-demo/coolserver/config.cc -o CMakeFiles/coolserver.dir/coolserver/config.cc.s

# Object files for target coolserver
coolserver_OBJECTS = \
"CMakeFiles/coolserver.dir/coolserver/log.cc.o" \
"CMakeFiles/coolserver.dir/coolserver/util.cc.o" \
"CMakeFiles/coolserver.dir/coolserver/config.cc.o"

# External object files for target coolserver
coolserver_EXTERNAL_OBJECTS =

../lib/libcoolserver.so: CMakeFiles/coolserver.dir/coolserver/log.cc.o
../lib/libcoolserver.so: CMakeFiles/coolserver.dir/coolserver/util.cc.o
../lib/libcoolserver.so: CMakeFiles/coolserver.dir/coolserver/config.cc.o
../lib/libcoolserver.so: CMakeFiles/coolserver.dir/build.make
../lib/libcoolserver.so: CMakeFiles/coolserver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lance/Desktop/server-demo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library ../lib/libcoolserver.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/coolserver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/coolserver.dir/build: ../lib/libcoolserver.so

.PHONY : CMakeFiles/coolserver.dir/build

CMakeFiles/coolserver.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/coolserver.dir/cmake_clean.cmake
.PHONY : CMakeFiles/coolserver.dir/clean

CMakeFiles/coolserver.dir/depend:
	cd /home/lance/Desktop/server-demo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lance/Desktop/server-demo /home/lance/Desktop/server-demo /home/lance/Desktop/server-demo/build /home/lance/Desktop/server-demo/build /home/lance/Desktop/server-demo/build/CMakeFiles/coolserver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/coolserver.dir/depend

