cmake_minimum_required (VERSION 2.6)

SET(GCC_COMPILE_FLAGS "-Wall -o WebincTests tests.c -lcheck -lm -lrt -L /lib64 -lusb-1.0 -l pthread")
SET( CMAKE_EXE_LINKER_FLAGS  "${GCC_COMPILE_FLAGS}" )

project (WebincTests)

add_executable(WebincTests tests.c)
