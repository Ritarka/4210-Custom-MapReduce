# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /home/ritarka/.local/lib/python3.10/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/ritarka/.local/lib/python3.10/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ritarka/cs4210/4210-proj4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ritarka/cs4210/4210-proj4

# Include any dependencies generated for this target.
include src/CMakeFiles/p4protolib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/p4protolib.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/p4protolib.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/p4protolib.dir/flags.make

src/masterworker.pb.cc: src/masterworker.proto
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ritarka/cs4210/4210-proj4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating proto messages ..."
	cd /home/ritarka/cs4210/4210-proj4/src && /home/ritarka/.local/bin/protoc --proto_path=/home/ritarka/cs4210/4210-proj4/src --cpp_out=/home/ritarka/cs4210/4210-proj4/src --plugin=protoc-gen-grpc=/home/ritarka/.local/bin/grpc_cpp_plugin --grpc_out=/home/ritarka/cs4210/4210-proj4/src /home/ritarka/cs4210/4210-proj4/src/masterworker.proto

src/masterworker.grpc.pb.cc: src/masterworker.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate src/masterworker.grpc.pb.cc

src/masterworker.pb.h: src/masterworker.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate src/masterworker.pb.h

src/masterworker.grpc.pb.h: src/masterworker.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate src/masterworker.grpc.pb.h

src/CMakeFiles/p4protolib.dir/masterworker.pb.cc.o: src/CMakeFiles/p4protolib.dir/flags.make
src/CMakeFiles/p4protolib.dir/masterworker.pb.cc.o: src/masterworker.pb.cc
src/CMakeFiles/p4protolib.dir/masterworker.pb.cc.o: src/CMakeFiles/p4protolib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ritarka/cs4210/4210-proj4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/p4protolib.dir/masterworker.pb.cc.o"
	cd /home/ritarka/cs4210/4210-proj4/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/p4protolib.dir/masterworker.pb.cc.o -MF CMakeFiles/p4protolib.dir/masterworker.pb.cc.o.d -o CMakeFiles/p4protolib.dir/masterworker.pb.cc.o -c /home/ritarka/cs4210/4210-proj4/src/masterworker.pb.cc

src/CMakeFiles/p4protolib.dir/masterworker.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/p4protolib.dir/masterworker.pb.cc.i"
	cd /home/ritarka/cs4210/4210-proj4/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ritarka/cs4210/4210-proj4/src/masterworker.pb.cc > CMakeFiles/p4protolib.dir/masterworker.pb.cc.i

src/CMakeFiles/p4protolib.dir/masterworker.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/p4protolib.dir/masterworker.pb.cc.s"
	cd /home/ritarka/cs4210/4210-proj4/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ritarka/cs4210/4210-proj4/src/masterworker.pb.cc -o CMakeFiles/p4protolib.dir/masterworker.pb.cc.s

src/CMakeFiles/p4protolib.dir/masterworker.grpc.pb.cc.o: src/CMakeFiles/p4protolib.dir/flags.make
src/CMakeFiles/p4protolib.dir/masterworker.grpc.pb.cc.o: src/masterworker.grpc.pb.cc
src/CMakeFiles/p4protolib.dir/masterworker.grpc.pb.cc.o: src/CMakeFiles/p4protolib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ritarka/cs4210/4210-proj4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/p4protolib.dir/masterworker.grpc.pb.cc.o"
	cd /home/ritarka/cs4210/4210-proj4/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/p4protolib.dir/masterworker.grpc.pb.cc.o -MF CMakeFiles/p4protolib.dir/masterworker.grpc.pb.cc.o.d -o CMakeFiles/p4protolib.dir/masterworker.grpc.pb.cc.o -c /home/ritarka/cs4210/4210-proj4/src/masterworker.grpc.pb.cc

src/CMakeFiles/p4protolib.dir/masterworker.grpc.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/p4protolib.dir/masterworker.grpc.pb.cc.i"
	cd /home/ritarka/cs4210/4210-proj4/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ritarka/cs4210/4210-proj4/src/masterworker.grpc.pb.cc > CMakeFiles/p4protolib.dir/masterworker.grpc.pb.cc.i

src/CMakeFiles/p4protolib.dir/masterworker.grpc.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/p4protolib.dir/masterworker.grpc.pb.cc.s"
	cd /home/ritarka/cs4210/4210-proj4/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ritarka/cs4210/4210-proj4/src/masterworker.grpc.pb.cc -o CMakeFiles/p4protolib.dir/masterworker.grpc.pb.cc.s

# Object files for target p4protolib
p4protolib_OBJECTS = \
"CMakeFiles/p4protolib.dir/masterworker.pb.cc.o" \
"CMakeFiles/p4protolib.dir/masterworker.grpc.pb.cc.o"

# External object files for target p4protolib
p4protolib_EXTERNAL_OBJECTS =

src/libp4protolib.a: src/CMakeFiles/p4protolib.dir/masterworker.pb.cc.o
src/libp4protolib.a: src/CMakeFiles/p4protolib.dir/masterworker.grpc.pb.cc.o
src/libp4protolib.a: src/CMakeFiles/p4protolib.dir/build.make
src/libp4protolib.a: src/CMakeFiles/p4protolib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ritarka/cs4210/4210-proj4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libp4protolib.a"
	cd /home/ritarka/cs4210/4210-proj4/src && $(CMAKE_COMMAND) -P CMakeFiles/p4protolib.dir/cmake_clean_target.cmake
	cd /home/ritarka/cs4210/4210-proj4/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/p4protolib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/p4protolib.dir/build: src/libp4protolib.a
.PHONY : src/CMakeFiles/p4protolib.dir/build

src/CMakeFiles/p4protolib.dir/clean:
	cd /home/ritarka/cs4210/4210-proj4/src && $(CMAKE_COMMAND) -P CMakeFiles/p4protolib.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/p4protolib.dir/clean

src/CMakeFiles/p4protolib.dir/depend: src/masterworker.grpc.pb.cc
src/CMakeFiles/p4protolib.dir/depend: src/masterworker.grpc.pb.h
src/CMakeFiles/p4protolib.dir/depend: src/masterworker.pb.cc
src/CMakeFiles/p4protolib.dir/depend: src/masterworker.pb.h
	cd /home/ritarka/cs4210/4210-proj4 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ritarka/cs4210/4210-proj4 /home/ritarka/cs4210/4210-proj4/src /home/ritarka/cs4210/4210-proj4 /home/ritarka/cs4210/4210-proj4/src /home/ritarka/cs4210/4210-proj4/src/CMakeFiles/p4protolib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/p4protolib.dir/depend

