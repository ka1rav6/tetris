cmake_minimum_required(VERSION 3.10)

project(Game)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC_FILES "src/*.cpp")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)


add_executable(app ${SRC_FILES})

target_include_directories(app PRIVATE include)

target_link_libraries(app
    SDL2::SDL2
    SDL2_image::SDL2_image
)

