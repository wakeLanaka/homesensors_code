cmake_minimum_required(VERSION 3.14)
project(AirLog VERSION 0.1.0 LANGUAGES CXX)
cmake_policy(SET CMP0135 NEW)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_library(SQLITE3_LIB sqlite3 REQUIRED)

include_directories(include)

file(GLOB_RECURSE SOURCES
        "src/app/*.cpp"
        "src/domain/*.cpp"
        "src/drivers/*.cpp"
        "src/main.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${SQLITE3_LIB})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)

add_subdirectory(tests)