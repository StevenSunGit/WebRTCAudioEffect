cmake_minimum_required(VERSION 3.5)

set(RN_NOISE_SRC
        src/denoise.c
        src/celt_lpc.c
        src/pitch.c
        src/rnn.c
        src/rnn_data.c)

set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")

add_library(rnnoise SHARED ${RN_NOISE_SRC})
add_library(rnnoise_static STATIC ${RN_NOISE_SRC})
set_target_properties(rnnoise_static PROPERTIES OUTPUT_NAME "rnnoise")
