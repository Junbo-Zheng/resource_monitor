cmake_minimum_required(VERSION 3.10)

project(resource_monitor)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS "build resource monitor library")

add_library(monitor STATIC monitor.c monitor.h)

target_compile_definitions(monitor PUBLIC -DCONFIG_MAX_BACKTRACE=16)

message(STATUS "build resource example target")

add_executable(resource_monitor resource_example.c)

target_link_libraries(resource_monitor PRIVATE monitor)

target_compile_options(resource_monitor PRIVATE -Wall -Wextra -g -rdynamic)

message(STATUS "build memory example target")

add_executable(memory_monitor memory_example.c)

target_link_libraries(memory_monitor PRIVATE monitor)

target_compile_options(memory_monitor PRIVATE -Wall -Wextra -g -rdynamic)
