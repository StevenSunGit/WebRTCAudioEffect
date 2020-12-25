cmake_minimum_required(VERSION 3.4.1)
project(rnnoise)

include_directories(inc)
link_directories(${PROJECT_SOURCE_DIR}/libs/${ANDROID_ABI}/)
link_directories($ENV{EXTRA_LIB_DIR})

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log )

set(RN_NOISE_SRC
        src/denoise.c
        src/celt_lpc.c
        src/pitch.c
        src/rnn.c
        src/rnn_data.c
        src/Android_JNI.cpp)

set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")


add_library(rnnoise SHARED ${RN_NOISE_SRC})
add_library(rnnoise_static STATIC ${RN_NOISE_SRC})

set_target_properties(rnnoise_static PROPERTIES OUTPUT_NAME "rnnoise")

target_link_libraries( # Specifies the target library.
        ${PROJECT_NAME}

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})