cmake_minimum_required(VERSION 3.10)
project(helloworld VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GPIODCXX REQUIRED IMPORTED_TARGET libgpiodcxx)

file(GLOB_RECURSE LIB_SOURCES "src/*.cpp" "lib/*.cpp")
add_library(project_lib ${LIB_SOURCES})
target_include_directories(project_lib PUBLIC include)

add_executable(homesensors homesensors.cpp)
target_link_libraries(project_lib PRIVATE PkgConfig::GPIODCXX)
target_link_libraries(homesensors PRIVATE project_lib)

install(TARGETS homesensors DESTINATION bin)
