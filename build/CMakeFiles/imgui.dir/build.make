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
CMAKE_SOURCE_DIR = /home/alek/Desktop/projects/imgui

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alek/Desktop/projects/imgui/build

# Include any dependencies generated for this target.
include CMakeFiles/imgui.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/imgui.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/imgui.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/imgui.dir/flags.make

CMakeFiles/imgui.dir/src/main.c.o: CMakeFiles/imgui.dir/flags.make
CMakeFiles/imgui.dir/src/main.c.o: ../src/main.c
CMakeFiles/imgui.dir/src/main.c.o: CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alek/Desktop/projects/imgui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/imgui.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/imgui.dir/src/main.c.o -MF CMakeFiles/imgui.dir/src/main.c.o.d -o CMakeFiles/imgui.dir/src/main.c.o -c /home/alek/Desktop/projects/imgui/src/main.c

CMakeFiles/imgui.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/imgui.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alek/Desktop/projects/imgui/src/main.c > CMakeFiles/imgui.dir/src/main.c.i

CMakeFiles/imgui.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/imgui.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alek/Desktop/projects/imgui/src/main.c -o CMakeFiles/imgui.dir/src/main.c.s

CMakeFiles/imgui.dir/src/button.c.o: CMakeFiles/imgui.dir/flags.make
CMakeFiles/imgui.dir/src/button.c.o: ../src/button.c
CMakeFiles/imgui.dir/src/button.c.o: CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alek/Desktop/projects/imgui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/imgui.dir/src/button.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/imgui.dir/src/button.c.o -MF CMakeFiles/imgui.dir/src/button.c.o.d -o CMakeFiles/imgui.dir/src/button.c.o -c /home/alek/Desktop/projects/imgui/src/button.c

CMakeFiles/imgui.dir/src/button.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/imgui.dir/src/button.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alek/Desktop/projects/imgui/src/button.c > CMakeFiles/imgui.dir/src/button.c.i

CMakeFiles/imgui.dir/src/button.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/imgui.dir/src/button.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alek/Desktop/projects/imgui/src/button.c -o CMakeFiles/imgui.dir/src/button.c.s

CMakeFiles/imgui.dir/src/color.c.o: CMakeFiles/imgui.dir/flags.make
CMakeFiles/imgui.dir/src/color.c.o: ../src/color.c
CMakeFiles/imgui.dir/src/color.c.o: CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alek/Desktop/projects/imgui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/imgui.dir/src/color.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/imgui.dir/src/color.c.o -MF CMakeFiles/imgui.dir/src/color.c.o.d -o CMakeFiles/imgui.dir/src/color.c.o -c /home/alek/Desktop/projects/imgui/src/color.c

CMakeFiles/imgui.dir/src/color.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/imgui.dir/src/color.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alek/Desktop/projects/imgui/src/color.c > CMakeFiles/imgui.dir/src/color.c.i

CMakeFiles/imgui.dir/src/color.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/imgui.dir/src/color.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alek/Desktop/projects/imgui/src/color.c -o CMakeFiles/imgui.dir/src/color.c.s

CMakeFiles/imgui.dir/src/scene.c.o: CMakeFiles/imgui.dir/flags.make
CMakeFiles/imgui.dir/src/scene.c.o: ../src/scene.c
CMakeFiles/imgui.dir/src/scene.c.o: CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alek/Desktop/projects/imgui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/imgui.dir/src/scene.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/imgui.dir/src/scene.c.o -MF CMakeFiles/imgui.dir/src/scene.c.o.d -o CMakeFiles/imgui.dir/src/scene.c.o -c /home/alek/Desktop/projects/imgui/src/scene.c

CMakeFiles/imgui.dir/src/scene.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/imgui.dir/src/scene.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alek/Desktop/projects/imgui/src/scene.c > CMakeFiles/imgui.dir/src/scene.c.i

CMakeFiles/imgui.dir/src/scene.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/imgui.dir/src/scene.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alek/Desktop/projects/imgui/src/scene.c -o CMakeFiles/imgui.dir/src/scene.c.s

CMakeFiles/imgui.dir/src/label.c.o: CMakeFiles/imgui.dir/flags.make
CMakeFiles/imgui.dir/src/label.c.o: ../src/label.c
CMakeFiles/imgui.dir/src/label.c.o: CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alek/Desktop/projects/imgui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/imgui.dir/src/label.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/imgui.dir/src/label.c.o -MF CMakeFiles/imgui.dir/src/label.c.o.d -o CMakeFiles/imgui.dir/src/label.c.o -c /home/alek/Desktop/projects/imgui/src/label.c

CMakeFiles/imgui.dir/src/label.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/imgui.dir/src/label.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alek/Desktop/projects/imgui/src/label.c > CMakeFiles/imgui.dir/src/label.c.i

CMakeFiles/imgui.dir/src/label.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/imgui.dir/src/label.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alek/Desktop/projects/imgui/src/label.c -o CMakeFiles/imgui.dir/src/label.c.s

CMakeFiles/imgui.dir/src/stack.c.o: CMakeFiles/imgui.dir/flags.make
CMakeFiles/imgui.dir/src/stack.c.o: ../src/stack.c
CMakeFiles/imgui.dir/src/stack.c.o: CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alek/Desktop/projects/imgui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/imgui.dir/src/stack.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/imgui.dir/src/stack.c.o -MF CMakeFiles/imgui.dir/src/stack.c.o.d -o CMakeFiles/imgui.dir/src/stack.c.o -c /home/alek/Desktop/projects/imgui/src/stack.c

CMakeFiles/imgui.dir/src/stack.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/imgui.dir/src/stack.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alek/Desktop/projects/imgui/src/stack.c > CMakeFiles/imgui.dir/src/stack.c.i

CMakeFiles/imgui.dir/src/stack.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/imgui.dir/src/stack.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alek/Desktop/projects/imgui/src/stack.c -o CMakeFiles/imgui.dir/src/stack.c.s

CMakeFiles/imgui.dir/src/scrollview.c.o: CMakeFiles/imgui.dir/flags.make
CMakeFiles/imgui.dir/src/scrollview.c.o: ../src/scrollview.c
CMakeFiles/imgui.dir/src/scrollview.c.o: CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alek/Desktop/projects/imgui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/imgui.dir/src/scrollview.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/imgui.dir/src/scrollview.c.o -MF CMakeFiles/imgui.dir/src/scrollview.c.o.d -o CMakeFiles/imgui.dir/src/scrollview.c.o -c /home/alek/Desktop/projects/imgui/src/scrollview.c

CMakeFiles/imgui.dir/src/scrollview.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/imgui.dir/src/scrollview.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alek/Desktop/projects/imgui/src/scrollview.c > CMakeFiles/imgui.dir/src/scrollview.c.i

CMakeFiles/imgui.dir/src/scrollview.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/imgui.dir/src/scrollview.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alek/Desktop/projects/imgui/src/scrollview.c -o CMakeFiles/imgui.dir/src/scrollview.c.s

# Object files for target imgui
imgui_OBJECTS = \
"CMakeFiles/imgui.dir/src/main.c.o" \
"CMakeFiles/imgui.dir/src/button.c.o" \
"CMakeFiles/imgui.dir/src/color.c.o" \
"CMakeFiles/imgui.dir/src/scene.c.o" \
"CMakeFiles/imgui.dir/src/label.c.o" \
"CMakeFiles/imgui.dir/src/stack.c.o" \
"CMakeFiles/imgui.dir/src/scrollview.c.o"

# External object files for target imgui
imgui_EXTERNAL_OBJECTS =

imgui: CMakeFiles/imgui.dir/src/main.c.o
imgui: CMakeFiles/imgui.dir/src/button.c.o
imgui: CMakeFiles/imgui.dir/src/color.c.o
imgui: CMakeFiles/imgui.dir/src/scene.c.o
imgui: CMakeFiles/imgui.dir/src/label.c.o
imgui: CMakeFiles/imgui.dir/src/stack.c.o
imgui: CMakeFiles/imgui.dir/src/scrollview.c.o
imgui: CMakeFiles/imgui.dir/build.make
imgui: CMakeFiles/imgui.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alek/Desktop/projects/imgui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C executable imgui"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/imgui.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/imgui.dir/build: imgui
.PHONY : CMakeFiles/imgui.dir/build

CMakeFiles/imgui.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/imgui.dir/cmake_clean.cmake
.PHONY : CMakeFiles/imgui.dir/clean

CMakeFiles/imgui.dir/depend:
	cd /home/alek/Desktop/projects/imgui/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alek/Desktop/projects/imgui /home/alek/Desktop/projects/imgui /home/alek/Desktop/projects/imgui/build /home/alek/Desktop/projects/imgui/build /home/alek/Desktop/projects/imgui/build/CMakeFiles/imgui.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/imgui.dir/depend

