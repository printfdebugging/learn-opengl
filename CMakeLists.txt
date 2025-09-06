cmake_minimum_required(VERSION 4.0)
project(executable)

set(C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

ADD_SUBDIRECTORY(libs/glad)
ADD_SUBDIRECTORY(libs/glfw)

ADD_EXECUTABLE(
    learngl
    src/main.c
    src/shader.c
    src/window.c
    src/renderer.c
    src/mesh.c
)

TARGET_COMPILE_OPTIONS(executable PRIVATE
    -std=c11
    -g
    -Wall
    -Wextra
    -static
)

TARGET_LINK_LIBRARIES(executable PRIVATE
    glad
    glfw
)

TARGET_INCLUDE_DIRECTORIES(executable PRIVATE
    include
)

TARGET_COMPILE_DEFINITIONS(executable PRIVATE
    GLFW_INCLUDE_NONE
)

add_custom_target(run
    COMMAND learngl
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    DEPENDS learngl
    COMMENT "Running learngl from root directory"
)
