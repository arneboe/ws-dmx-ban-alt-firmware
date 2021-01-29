cmake_minimum_required(VERSION 3.10)
project(dmx)


include_directories(/usr/share/sdcc/include)

add_executable(dmx main.c delay.c)