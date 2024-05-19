cmake_minimum_required(VERSION 3.26)
project(Laba_18project C)

set(CMAKE_C_STANDARD 11)

add_executable(Laba_18project
        libs/data_struct/string/string.c
        libs/data_struct/string/string.h
        main.c)
add_subdirectory(libs)

target_link_libraries(data_struct)



