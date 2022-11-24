cmake_minimum_required(VERSION 3.4)
project(Slinky3D)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRCS src/Slinky/*.cpp)
add_library(${PROJECT_NAME} ${SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC include)

add_subdirectory(3rdparty/glfw)
add_subdirectory(3rdparty/glad)
add_subdirectory(3rdparty/glm)

add_executable(Particles examples/Particles/main.cpp)
target_link_libraries(Particles ${PROJECT_NAME} glfw glad glm)