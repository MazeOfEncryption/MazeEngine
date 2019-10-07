cmake_minimum_required(VERSION 3.0.0)
project(MazeEngine VERSION 0.1.0)

include(CTest)
enable_testing()


find_package(OpenGL REQUIRED)

find_package(GLEW 2.0 REQUIRED)
target_link_libraries(Starting GLEW::GLEW)

add_subdirectory(lib/glew/build/cmake)
add_subdirectory(lib/glfw)

add_executable(MazeEngine src/main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)