cmake_minimum_required(VERSION 3.7)
project(imgui)

SET(GCC_COVERAGE_LINK_FLAGS    "-lSDL2 -lSDL2_ttf")

find_package(SDL2 REQUIRED)
include_directories(imgui ${SDL2_INCLUDE_DIRS})

add_executable(imgui ./src/main.c ./src/button.c ./src/color.c ./src/scene.c ./src/label.c)
target_link_libraries(imgui ${SDL2_LIBRARIES} SDL2_ttf)

