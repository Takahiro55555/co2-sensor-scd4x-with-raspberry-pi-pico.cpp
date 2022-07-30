cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(scd4x C CXX ASM)  # プロジェクト名?を `my_project` に設定
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(scd4x  # 生成ファイル名?
  src/main.cpp  # ソースコード
)

pico_enable_stdio_usb(scd4x 1)  # 生成ファイル名? と同じ文字列を設定する
pico_enable_stdio_uart(scd4x 1)  # 生成ファイル名? と同じ文字列を設定する

pico_add_extra_outputs(scd4x)  # 生成ファイル名? と同じ文字列を設定する

target_link_libraries(scd4x pico_stdlib)  # 生成ファイル名? と同じ文字列を設定する
