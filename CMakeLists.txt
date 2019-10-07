cmake_minimum_required(VERSION 3.0.0)
project(MazeEngine VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(OpenGL REQUIRED)

add_subdirectory(lib/glad)
add_subdirectory(lib/glfw)

add_executable(MazeEngine src/main.cpp src/shaders.cpp src/read.cpp src/main.hpp)

include_directories(lib/glm/glm/)
target_link_libraries(MazeEngine glad)
target_link_libraries(MazeEngine glfw)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)