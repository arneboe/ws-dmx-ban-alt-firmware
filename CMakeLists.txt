cmake_minimum_required(VERSION 3.10)
project(dmx C)

set(BOARD_VERSION "" CACHE STRING "Select which of the dmx boards you want to use")

message(STATUS "Board version: ${BOARD_VERSION}")


if("${BOARD_VERSION}" STREQUAL "WS_DMX_3CH_BAN_V2")
set(LED_SRC leds_3ch_ban_v2.c)

elseif("${BOARD_VERSION}" STREQUAL "WS_DMX_8CH_BAN_V4.1")
set(LED_SRC leds_8ch_ban_41.c)
else()

message(FATAL_ERROR "BOARD_VERSION unknown or unset")

endif()



set(CMAKE_C_FLAGS "--std-c99 --opt-code-speed")

include_directories(/usr/share/sdcc/include)




add_executable(dmx main.c delay.c uart.c dip.c ${LED_SRC})