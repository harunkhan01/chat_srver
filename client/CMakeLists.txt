cmake_minimum_required(VERSION 3.22)

project(Client)

add_executable(ClientScratch)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

target_sources(ClientScratch
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/client.c
)