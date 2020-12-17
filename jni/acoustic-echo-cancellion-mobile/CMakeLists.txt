cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_STANDARD 14)

project(acoustic-echo-cancellion-mobile)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -std=c++11 -fexceptions -fpermissive -fpic")

if (MSVC)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")
    else ()
        set(CMAKE_BUILD_TYPE "Release")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  /fp:fast /Gy /Oi /Oy /O2 /Ot /Zi /EHsc ")
    endif ()
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
else ()
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wno-unused-variable")
    else (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_BUILD_TYPE "Release")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")
    endif (CMAKE_BUILD_TYPE STREQUAL "Debug")
endif ()

file(GLOB AECM_SRC
        ${CMAKE_CURRENT_LIST_DIR}/src/*.c
        ${CMAKE_CURRENT_LIST_DIR}/src/*.cc
        ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
#list(FILTER AECM_SRC EXCLUDE REGEX ".*aecm_core_c.cc$")
list(FILTER AECM_SRC EXCLUDE REGEX ".*aecm_core_neon.cc$")
list(FILTER AECM_SRC EXCLUDE REGEX ".*aecm_core_mips.cc$")
set(AECM_COMPILE_CODE ${AECM_SRC})

add_library(${PROJECT_NAME} SHARED ${AECM_COMPILE_CODE})

# Searches for a specified prebuilt library and stores the path as a
# variable. Because system libraries are included in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in the
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       ${PROJECT_NAME}

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib})