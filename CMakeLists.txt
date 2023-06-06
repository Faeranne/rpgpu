cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(rpgpu C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()


add_executable(rpgpu
  rpgpu.c
)

pico_enable_stdio_usb(rpgpu 1)
pico_enable_stdio_uart(rpgpu 1)

pico_add_extra_outputs(rpgpu)

pico_set_program_name(rpgpu "RP GPU")
pico_set_program_description(rpgpu "GPU program for handling tile based drawing.")
pico_set_program_version(rpgpu "0.00001a")
pico_set_program_url(rpgpu "www.nextlab.dev/projects/RPGPU")

target_link_libraries(rpgpu
  pico_stdlib
)
