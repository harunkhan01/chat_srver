cmake_minimum_required(VERSION 3.22)

project(Server)

add_executable(ServerScratch)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

target_sources(ServerScratch
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/server.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/thread_handler.c
)