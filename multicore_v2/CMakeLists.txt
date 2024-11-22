# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

set(MAIN main)
set(CORE0 core_0)
set(CORE1 core_1)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(main C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(${MAIN} ${MAIN}.c)

pico_set_program_name(${MAIN} "main")
pico_set_program_version(${MAIN} "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(${MAIN} 0)
pico_enable_stdio_usb(${MAIN} 1)

# Add extra custom library
add_library(${CORE0} ${CORE0}.c)
add_library(${CORE1} ${CORE1}.c)

# Add dependencies in library
target_link_libraries(${CORE0}
    pico_stdlib
    pico_multicore
    hardware_adc
)

target_link_libraries(${CORE1}
    pico_stdlib
    pico_multicore
)

# Add the standard library to the build
target_link_libraries(${MAIN}
    pico_stdlib
    ${CORE0}
    ${CORE1}
)

# Add the standard include files to the build
target_include_directories(${MAIN} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

pico_add_extra_outputs(${MAIN})

