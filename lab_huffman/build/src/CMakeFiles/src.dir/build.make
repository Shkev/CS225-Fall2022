# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /workspaces/CS225/CS225-Fall2022/lab_huffman

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspaces/CS225/CS225-Fall2022/lab_huffman/build

# Include any dependencies generated for this target.
include src/CMakeFiles/src.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/src.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/src.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/src.dir/flags.make

src/CMakeFiles/src.dir/binary_file_reader.cpp.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/binary_file_reader.cpp.o: ../src/binary_file_reader.cpp
src/CMakeFiles/src.dir/binary_file_reader.cpp.o: src/CMakeFiles/src.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/CS225/CS225-Fall2022/lab_huffman/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/src.dir/binary_file_reader.cpp.o"
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/src.dir/binary_file_reader.cpp.o -MF CMakeFiles/src.dir/binary_file_reader.cpp.o.d -o CMakeFiles/src.dir/binary_file_reader.cpp.o -c /workspaces/CS225/CS225-Fall2022/lab_huffman/src/binary_file_reader.cpp

src/CMakeFiles/src.dir/binary_file_reader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/binary_file_reader.cpp.i"
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/CS225/CS225-Fall2022/lab_huffman/src/binary_file_reader.cpp > CMakeFiles/src.dir/binary_file_reader.cpp.i

src/CMakeFiles/src.dir/binary_file_reader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/binary_file_reader.cpp.s"
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/CS225/CS225-Fall2022/lab_huffman/src/binary_file_reader.cpp -o CMakeFiles/src.dir/binary_file_reader.cpp.s

src/CMakeFiles/src.dir/binary_file_writer.cpp.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/binary_file_writer.cpp.o: ../src/binary_file_writer.cpp
src/CMakeFiles/src.dir/binary_file_writer.cpp.o: src/CMakeFiles/src.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/CS225/CS225-Fall2022/lab_huffman/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/src.dir/binary_file_writer.cpp.o"
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/src.dir/binary_file_writer.cpp.o -MF CMakeFiles/src.dir/binary_file_writer.cpp.o.d -o CMakeFiles/src.dir/binary_file_writer.cpp.o -c /workspaces/CS225/CS225-Fall2022/lab_huffman/src/binary_file_writer.cpp

src/CMakeFiles/src.dir/binary_file_writer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/binary_file_writer.cpp.i"
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/CS225/CS225-Fall2022/lab_huffman/src/binary_file_writer.cpp > CMakeFiles/src.dir/binary_file_writer.cpp.i

src/CMakeFiles/src.dir/binary_file_writer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/binary_file_writer.cpp.s"
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/CS225/CS225-Fall2022/lab_huffman/src/binary_file_writer.cpp -o CMakeFiles/src.dir/binary_file_writer.cpp.s

src/CMakeFiles/src.dir/decoder.cpp.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/decoder.cpp.o: ../src/decoder.cpp
src/CMakeFiles/src.dir/decoder.cpp.o: src/CMakeFiles/src.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/CS225/CS225-Fall2022/lab_huffman/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/src.dir/decoder.cpp.o"
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/src.dir/decoder.cpp.o -MF CMakeFiles/src.dir/decoder.cpp.o.d -o CMakeFiles/src.dir/decoder.cpp.o -c /workspaces/CS225/CS225-Fall2022/lab_huffman/src/decoder.cpp

src/CMakeFiles/src.dir/decoder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/decoder.cpp.i"
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/CS225/CS225-Fall2022/lab_huffman/src/decoder.cpp > CMakeFiles/src.dir/decoder.cpp.i

src/CMakeFiles/src.dir/decoder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/decoder.cpp.s"
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/CS225/CS225-Fall2022/lab_huffman/src/decoder.cpp -o CMakeFiles/src.dir/decoder.cpp.s

src/CMakeFiles/src.dir/encoder.cpp.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/encoder.cpp.o: ../src/encoder.cpp
src/CMakeFiles/src.dir/encoder.cpp.o: src/CMakeFiles/src.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/CS225/CS225-Fall2022/lab_huffman/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/src.dir/encoder.cpp.o"
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/src.dir/encoder.cpp.o -MF CMakeFiles/src.dir/encoder.cpp.o.d -o CMakeFiles/src.dir/encoder.cpp.o -c /workspaces/CS225/CS225-Fall2022/lab_huffman/src/encoder.cpp

src/CMakeFiles/src.dir/encoder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/encoder.cpp.i"
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/CS225/CS225-Fall2022/lab_huffman/src/encoder.cpp > CMakeFiles/src.dir/encoder.cpp.i

src/CMakeFiles/src.dir/encoder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/encoder.cpp.s"
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/CS225/CS225-Fall2022/lab_huffman/src/encoder.cpp -o CMakeFiles/src.dir/encoder.cpp.s

src/CMakeFiles/src.dir/frequency.cpp.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/frequency.cpp.o: ../src/frequency.cpp
src/CMakeFiles/src.dir/frequency.cpp.o: src/CMakeFiles/src.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/CS225/CS225-Fall2022/lab_huffman/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/src.dir/frequency.cpp.o"
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/src.dir/frequency.cpp.o -MF CMakeFiles/src.dir/frequency.cpp.o.d -o CMakeFiles/src.dir/frequency.cpp.o -c /workspaces/CS225/CS225-Fall2022/lab_huffman/src/frequency.cpp

src/CMakeFiles/src.dir/frequency.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/frequency.cpp.i"
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/CS225/CS225-Fall2022/lab_huffman/src/frequency.cpp > CMakeFiles/src.dir/frequency.cpp.i

src/CMakeFiles/src.dir/frequency.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/frequency.cpp.s"
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/CS225/CS225-Fall2022/lab_huffman/src/frequency.cpp -o CMakeFiles/src.dir/frequency.cpp.s

src/CMakeFiles/src.dir/huffman_tree.cpp.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/huffman_tree.cpp.o: ../src/huffman_tree.cpp
src/CMakeFiles/src.dir/huffman_tree.cpp.o: src/CMakeFiles/src.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/CS225/CS225-Fall2022/lab_huffman/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/CMakeFiles/src.dir/huffman_tree.cpp.o"
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/src.dir/huffman_tree.cpp.o -MF CMakeFiles/src.dir/huffman_tree.cpp.o.d -o CMakeFiles/src.dir/huffman_tree.cpp.o -c /workspaces/CS225/CS225-Fall2022/lab_huffman/src/huffman_tree.cpp

src/CMakeFiles/src.dir/huffman_tree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/huffman_tree.cpp.i"
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/CS225/CS225-Fall2022/lab_huffman/src/huffman_tree.cpp > CMakeFiles/src.dir/huffman_tree.cpp.i

src/CMakeFiles/src.dir/huffman_tree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/huffman_tree.cpp.s"
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/CS225/CS225-Fall2022/lab_huffman/src/huffman_tree.cpp -o CMakeFiles/src.dir/huffman_tree.cpp.s

src/CMakeFiles/src.dir/print_as_ascii.cpp.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/print_as_ascii.cpp.o: ../src/print_as_ascii.cpp
src/CMakeFiles/src.dir/print_as_ascii.cpp.o: src/CMakeFiles/src.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/CS225/CS225-Fall2022/lab_huffman/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/CMakeFiles/src.dir/print_as_ascii.cpp.o"
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/src.dir/print_as_ascii.cpp.o -MF CMakeFiles/src.dir/print_as_ascii.cpp.o.d -o CMakeFiles/src.dir/print_as_ascii.cpp.o -c /workspaces/CS225/CS225-Fall2022/lab_huffman/src/print_as_ascii.cpp

src/CMakeFiles/src.dir/print_as_ascii.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/print_as_ascii.cpp.i"
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/CS225/CS225-Fall2022/lab_huffman/src/print_as_ascii.cpp > CMakeFiles/src.dir/print_as_ascii.cpp.i

src/CMakeFiles/src.dir/print_as_ascii.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/print_as_ascii.cpp.s"
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/CS225/CS225-Fall2022/lab_huffman/src/print_as_ascii.cpp -o CMakeFiles/src.dir/print_as_ascii.cpp.s

src/CMakeFiles/src.dir/view_tree.cpp.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/view_tree.cpp.o: ../src/view_tree.cpp
src/CMakeFiles/src.dir/view_tree.cpp.o: src/CMakeFiles/src.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/CS225/CS225-Fall2022/lab_huffman/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/CMakeFiles/src.dir/view_tree.cpp.o"
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/src.dir/view_tree.cpp.o -MF CMakeFiles/src.dir/view_tree.cpp.o.d -o CMakeFiles/src.dir/view_tree.cpp.o -c /workspaces/CS225/CS225-Fall2022/lab_huffman/src/view_tree.cpp

src/CMakeFiles/src.dir/view_tree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/view_tree.cpp.i"
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/CS225/CS225-Fall2022/lab_huffman/src/view_tree.cpp > CMakeFiles/src.dir/view_tree.cpp.i

src/CMakeFiles/src.dir/view_tree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/view_tree.cpp.s"
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/CS225/CS225-Fall2022/lab_huffman/src/view_tree.cpp -o CMakeFiles/src.dir/view_tree.cpp.s

# Object files for target src
src_OBJECTS = \
"CMakeFiles/src.dir/binary_file_reader.cpp.o" \
"CMakeFiles/src.dir/binary_file_writer.cpp.o" \
"CMakeFiles/src.dir/decoder.cpp.o" \
"CMakeFiles/src.dir/encoder.cpp.o" \
"CMakeFiles/src.dir/frequency.cpp.o" \
"CMakeFiles/src.dir/huffman_tree.cpp.o" \
"CMakeFiles/src.dir/print_as_ascii.cpp.o" \
"CMakeFiles/src.dir/view_tree.cpp.o"

# External object files for target src
src_EXTERNAL_OBJECTS =

src/libsrc.a: src/CMakeFiles/src.dir/binary_file_reader.cpp.o
src/libsrc.a: src/CMakeFiles/src.dir/binary_file_writer.cpp.o
src/libsrc.a: src/CMakeFiles/src.dir/decoder.cpp.o
src/libsrc.a: src/CMakeFiles/src.dir/encoder.cpp.o
src/libsrc.a: src/CMakeFiles/src.dir/frequency.cpp.o
src/libsrc.a: src/CMakeFiles/src.dir/huffman_tree.cpp.o
src/libsrc.a: src/CMakeFiles/src.dir/print_as_ascii.cpp.o
src/libsrc.a: src/CMakeFiles/src.dir/view_tree.cpp.o
src/libsrc.a: src/CMakeFiles/src.dir/build.make
src/libsrc.a: src/CMakeFiles/src.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/CS225/CS225-Fall2022/lab_huffman/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX static library libsrc.a"
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src && $(CMAKE_COMMAND) -P CMakeFiles/src.dir/cmake_clean_target.cmake
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/src.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/src.dir/build: src/libsrc.a
.PHONY : src/CMakeFiles/src.dir/build

src/CMakeFiles/src.dir/clean:
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src && $(CMAKE_COMMAND) -P CMakeFiles/src.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/src.dir/clean

src/CMakeFiles/src.dir/depend:
	cd /workspaces/CS225/CS225-Fall2022/lab_huffman/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/CS225/CS225-Fall2022/lab_huffman /workspaces/CS225/CS225-Fall2022/lab_huffman/src /workspaces/CS225/CS225-Fall2022/lab_huffman/build /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src /workspaces/CS225/CS225-Fall2022/lab_huffman/build/src/CMakeFiles/src.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/src.dir/depend

