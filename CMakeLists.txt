cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(scd4x C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

# ソースファイルのリストを取得
file(GLOB SRC_FILES
  ${PROJECT_SOURCE_DIR}/src/*.cpp
)
add_executable(scd4x ${SRC_FILES})

pico_enable_stdio_usb(scd4x 1)
pico_enable_stdio_uart(scd4x 1)

pico_add_extra_outputs(scd4x)

target_link_libraries(scd4x pico_stdlib hardware_i2c)
