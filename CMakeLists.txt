cmake_minimum_required(VERSION 3.4)
project(Slinky3D)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRCS src/Slinky/*.cpp)
add_library(${PROJECT_NAME} ${SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC include)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/modules/" ${CMAKE_MODULE_PATH})

# Add Corrade as a subproject
add_subdirectory(3rdparty/corrade EXCLUDE_FROM_ALL)

# Add Magnum as a subproject, enable Sdl2Application
set(MAGNUM_WITH_SDL2APPLICATION ON CACHE BOOL "" FORCE)
add_subdirectory(3rdparty/magnum EXCLUDE_FROM_ALL)

find_package(Magnum REQUIRED
        GL
        MeshTools
        Primitives
        Shaders
        Trade
        Sdl2Application)
set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

# examples
add_executable(Particles examples/Particles/main.cpp)
target_link_libraries(Particles
        PRIVATE
        ${PROJECT_NAME}
        Magnum::Application
        Magnum::GL
        Magnum::Magnum
        Magnum::MeshTools
        Magnum::Primitives
        Magnum::Shaders
        Magnum::Trade)