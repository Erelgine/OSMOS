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
CMAKE_COMMAND = /opt/clion/bin/cmake/bin/cmake

# The command to remove a file.
RM = /opt/clion/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alexis/Bureau/OSMOS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alexis/Bureau/OSMOS/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/OSMOS.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/OSMOS.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OSMOS.dir/flags.make

CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/port.cpp.o: CMakeFiles/OSMOS.dir/flags.make
CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/port.cpp.o: ../src/i386/core-minimal/osmos/io/port.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexis/Bureau/OSMOS/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/port.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/port.cpp.o -c /home/alexis/Bureau/OSMOS/src/i386/core-minimal/osmos/io/port.cpp

CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/port.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/port.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexis/Bureau/OSMOS/src/i386/core-minimal/osmos/io/port.cpp > CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/port.cpp.i

CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/port.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/port.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexis/Bureau/OSMOS/src/i386/core-minimal/osmos/io/port.cpp -o CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/port.cpp.s

CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/port.cpp.o.requires:

.PHONY : CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/port.cpp.o.requires

CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/port.cpp.o.provides: CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/port.cpp.o.requires
	$(MAKE) -f CMakeFiles/OSMOS.dir/build.make CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/port.cpp.o.provides.build
.PHONY : CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/port.cpp.o.provides

CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/port.cpp.o.provides.build: CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/port.cpp.o


CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/serial.cpp.o: CMakeFiles/OSMOS.dir/flags.make
CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/serial.cpp.o: ../src/i386/core-minimal/osmos/io/serial.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexis/Bureau/OSMOS/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/serial.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/serial.cpp.o -c /home/alexis/Bureau/OSMOS/src/i386/core-minimal/osmos/io/serial.cpp

CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/serial.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/serial.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexis/Bureau/OSMOS/src/i386/core-minimal/osmos/io/serial.cpp > CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/serial.cpp.i

CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/serial.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/serial.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexis/Bureau/OSMOS/src/i386/core-minimal/osmos/io/serial.cpp -o CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/serial.cpp.s

CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/serial.cpp.o.requires:

.PHONY : CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/serial.cpp.o.requires

CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/serial.cpp.o.provides: CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/serial.cpp.o.requires
	$(MAKE) -f CMakeFiles/OSMOS.dir/build.make CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/serial.cpp.o.provides.build
.PHONY : CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/serial.cpp.o.provides

CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/serial.cpp.o.provides.build: CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/serial.cpp.o


CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/sys/memory.cpp.o: CMakeFiles/OSMOS.dir/flags.make
CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/sys/memory.cpp.o: ../src/i386/core-minimal/osmos/sys/memory.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexis/Bureau/OSMOS/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/sys/memory.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/sys/memory.cpp.o -c /home/alexis/Bureau/OSMOS/src/i386/core-minimal/osmos/sys/memory.cpp

CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/sys/memory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/sys/memory.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexis/Bureau/OSMOS/src/i386/core-minimal/osmos/sys/memory.cpp > CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/sys/memory.cpp.i

CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/sys/memory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/sys/memory.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexis/Bureau/OSMOS/src/i386/core-minimal/osmos/sys/memory.cpp -o CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/sys/memory.cpp.s

CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/sys/memory.cpp.o.requires:

.PHONY : CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/sys/memory.cpp.o.requires

CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/sys/memory.cpp.o.provides: CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/sys/memory.cpp.o.requires
	$(MAKE) -f CMakeFiles/OSMOS.dir/build.make CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/sys/memory.cpp.o.provides.build
.PHONY : CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/sys/memory.cpp.o.provides

CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/sys/memory.cpp.o.provides.build: CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/sys/memory.cpp.o


CMakeFiles/OSMOS.dir/src/i386/core-minimal/boot.cpp.o: CMakeFiles/OSMOS.dir/flags.make
CMakeFiles/OSMOS.dir/src/i386/core-minimal/boot.cpp.o: ../src/i386/core-minimal/boot.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexis/Bureau/OSMOS/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/OSMOS.dir/src/i386/core-minimal/boot.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OSMOS.dir/src/i386/core-minimal/boot.cpp.o -c /home/alexis/Bureau/OSMOS/src/i386/core-minimal/boot.cpp

CMakeFiles/OSMOS.dir/src/i386/core-minimal/boot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OSMOS.dir/src/i386/core-minimal/boot.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexis/Bureau/OSMOS/src/i386/core-minimal/boot.cpp > CMakeFiles/OSMOS.dir/src/i386/core-minimal/boot.cpp.i

CMakeFiles/OSMOS.dir/src/i386/core-minimal/boot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OSMOS.dir/src/i386/core-minimal/boot.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexis/Bureau/OSMOS/src/i386/core-minimal/boot.cpp -o CMakeFiles/OSMOS.dir/src/i386/core-minimal/boot.cpp.s

CMakeFiles/OSMOS.dir/src/i386/core-minimal/boot.cpp.o.requires:

.PHONY : CMakeFiles/OSMOS.dir/src/i386/core-minimal/boot.cpp.o.requires

CMakeFiles/OSMOS.dir/src/i386/core-minimal/boot.cpp.o.provides: CMakeFiles/OSMOS.dir/src/i386/core-minimal/boot.cpp.o.requires
	$(MAKE) -f CMakeFiles/OSMOS.dir/build.make CMakeFiles/OSMOS.dir/src/i386/core-minimal/boot.cpp.o.provides.build
.PHONY : CMakeFiles/OSMOS.dir/src/i386/core-minimal/boot.cpp.o.provides

CMakeFiles/OSMOS.dir/src/i386/core-minimal/boot.cpp.o.provides.build: CMakeFiles/OSMOS.dir/src/i386/core-minimal/boot.cpp.o


# Object files for target OSMOS
OSMOS_OBJECTS = \
"CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/port.cpp.o" \
"CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/serial.cpp.o" \
"CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/sys/memory.cpp.o" \
"CMakeFiles/OSMOS.dir/src/i386/core-minimal/boot.cpp.o"

# External object files for target OSMOS
OSMOS_EXTERNAL_OBJECTS =

OSMOS: CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/port.cpp.o
OSMOS: CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/serial.cpp.o
OSMOS: CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/sys/memory.cpp.o
OSMOS: CMakeFiles/OSMOS.dir/src/i386/core-minimal/boot.cpp.o
OSMOS: CMakeFiles/OSMOS.dir/build.make
OSMOS: CMakeFiles/OSMOS.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alexis/Bureau/OSMOS/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable OSMOS"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OSMOS.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OSMOS.dir/build: OSMOS

.PHONY : CMakeFiles/OSMOS.dir/build

CMakeFiles/OSMOS.dir/requires: CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/port.cpp.o.requires
CMakeFiles/OSMOS.dir/requires: CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/io/serial.cpp.o.requires
CMakeFiles/OSMOS.dir/requires: CMakeFiles/OSMOS.dir/src/i386/core-minimal/osmos/sys/memory.cpp.o.requires
CMakeFiles/OSMOS.dir/requires: CMakeFiles/OSMOS.dir/src/i386/core-minimal/boot.cpp.o.requires

.PHONY : CMakeFiles/OSMOS.dir/requires

CMakeFiles/OSMOS.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OSMOS.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OSMOS.dir/clean

CMakeFiles/OSMOS.dir/depend:
	cd /home/alexis/Bureau/OSMOS/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alexis/Bureau/OSMOS /home/alexis/Bureau/OSMOS /home/alexis/Bureau/OSMOS/cmake-build-debug /home/alexis/Bureau/OSMOS/cmake-build-debug /home/alexis/Bureau/OSMOS/cmake-build-debug/CMakeFiles/OSMOS.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OSMOS.dir/depend

