cmake_minimum_required(VERSION 3.10)
project(dmx C)

set(CMAKE_C_FLAGS "--std-c99")

include_directories(/usr/share/sdcc/include)

add_executable(dmx main.c delay.c uart.c dip.c)