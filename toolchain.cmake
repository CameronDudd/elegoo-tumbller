# avr-toolchain.cmake

set(MCU atmega328p)
set(F_CPU 16000000UL)

set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)

set(CMAKE_C_FLAGS "-mmcu=${MCU} -DF_CPU=${F_CPU} -Os")
set(CMAKE_CXX_FLAGS "-mmcu=${MCU} -DF_CPU=${F_CPU} -Os")
set(CMAKE_EXE_LINKER_FLAGS "-mmcu=${MCU}")

add_compile_definitions(F_CPU=${F_CPU})

set(CMAKE_C_LINK_EXECUTABLE "avr-gcc -mmcu=${MCU} <OBJECTS> -o <TARGET>")
set(CMAKE_CXX_LINK_EXECUTABLE "avr-g++ -mmcu=${MCU} <OBJECTS> -o <TARGET>")
