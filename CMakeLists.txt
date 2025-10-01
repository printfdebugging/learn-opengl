cmake_minimum_required(VERSION 4.0)
project(learngl)

set(C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

ADD_SUBDIRECTORY(libs/glad)
ADD_SUBDIRECTORY(libs/glfw)

ADD_EXECUTABLE(
    learngl
    src/main.c
    src/stb.c
)

TARGET_COMPILE_OPTIONS(learngl PRIVATE
    -std=c11
    -g
    -Wall
    -Wextra
    -static
)

TARGET_LINK_LIBRARIES(learngl PRIVATE
    glad
    glfw
)

TARGET_COMPILE_DEFINITIONS(learngl PRIVATE
    GLFW_INCLUDE_NONE
)

TARGET_INCLUDE_DIRECTORIES(learngl PRIVATE
    ${CMAKE_SOURCE_DIR}/libs/stb
)

add_custom_target(run
    COMMAND learngl
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    DEPENDS learngl
    COMMENT "Running learngl from root directory"
)
