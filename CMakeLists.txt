cmake_minimum_required(VERSION 3.10.0)
project(helloworld VERSION 0.1.0 LANGUAGES C)

add_executable(helloworld helloworld.c)

install(TARGETS helloworld DESTINATION bin)
