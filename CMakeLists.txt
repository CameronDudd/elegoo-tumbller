# CMakeLists.txt

cmake_minimum_required(VERSION 3.30)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/toolchain.cmake)

project(elegoo_tumbller VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

include_directories(/usr/avr/include)
include_directories(${CMAKE_SOURCE_DIR}/include)

set(TARGET_NAME main)

add_executable(${TARGET_NAME}.elf src/main.cpp src/motor.cpp src/interrupts.cpp src/serial.cpp)

target_include_directories(${TARGET_NAME}.elf PRIVATE /usr/avr/include)

add_custom_target(${TARGET_NAME}.hex
    DEPENDS ${TARGET_NAME}.elf
    COMMAND avr-objcopy -O ihex -R .eeprom ${TARGET_NAME}.elf ${TARGET_NAME}.hex
)

add_custom_target(flash
    DEPENDS ${TARGET_NAME}.hex
    COMMAND avrdude -c arduino -p m328p -P /dev/ttyUSB0 -b 115200 -U flash:w:${TARGET_NAME}.hex
)

add_custom_target(flash-original
    COMMAND avrdude -c arduino -p m328p -P /dev/ttyUSB0 -b 115200 -U flash:w:${CMAKE_SOURCE_DIR}/backup/original_backup.hex 
)
