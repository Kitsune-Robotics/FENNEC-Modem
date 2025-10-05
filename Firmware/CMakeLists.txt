cmake_minimum_required(VERSION 3.13)

# Include the Pico SDK
include(pico_sdk_import.cmake)

# Set project name and language
project(pico_project C CXX ASM)

# Set C/C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the Pico SDK
pico_sdk_init()

# Create the executable
add_executable(pico_project
    main.c
    lib/shift_register_lcd/shift_register_display.c
)

# Include directories
target_include_directories(pico_project PRIVATE lib/shift_register_lcd)

# Link the Pico libraries
target_link_libraries(pico_project
    pico_stdlib
    hardware_gpio
)

# Enable USB output, disable UART output
pico_enable_stdio_usb(pico_project 1)
pico_enable_stdio_uart(pico_project 0)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(pico_project)
