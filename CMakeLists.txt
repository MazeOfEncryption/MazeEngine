cmake_minimum_required(VERSION 3.0.0)
project(MazeEngine VERSION 0.1.0)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

include(CTest)
enable_testing()

find_package(OpenGL REQUIRED)

add_subdirectory(lib/glad)
add_subdirectory(lib/glfw)

include_directories(lib/glm/glm/)
# include_directories(lib/FreeImage/Dist/x64)

# link_directories(lib/FreeImage/Dist/x64/)

add_executable(MazeEngine src/main.cpp src/Dep.hpp src/Read.cpp src/Read.hpp src/Window.cpp src/Window.hpp src/MazeEngine.hpp src/Shader.cpp src/Shader.hpp)

target_link_libraries(MazeEngine glad)
target_link_libraries(MazeEngine glfw)
# target_link_libraries(MazeEngine freeimage.lib)
# target_link_libraries(MazeEngine -mwindows)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)

# add_custom_command(TARGET MazeEngine POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#         "${PROJECT_SOURCE_DIR}/lib/FreeImage/Dist/x64/FreeImage.dll"
# 		"$<TARGET_FILE_DIR:MazeEngine>"
# )
add_custom_command(TARGET MazeEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/shaders/"
		"$<TARGET_FILE_DIR:MazeEngine>/shaders/"
)
add_custom_command(TARGET MazeEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/meshes/"
		"$<TARGET_FILE_DIR:MazeEngine>/meshes/"
)