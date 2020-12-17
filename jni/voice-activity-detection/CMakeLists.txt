cmake_minimum_required(VERSION 3.4.1)
project(voice-activity-detection)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -std=c++11 -fexceptions -fpermissive -fpic")

include_directories(inc)
link_directories(${PROJECT_SOURCE_DIR}/libs/${ANDROID_ABI}/)
link_directories($ENV{EXTRA_LIB_DIR})

file(GLOB_RECURSE FILES_SOURCES *.cpp)
file(GLOB_RECURSE FILES_INCLUDE *.hpp)

ADD_LIBRARY(${PROJECT_NAME} STATIC ${FILES_INCLUDE} ${FILES_SOURCES})

target_link_libraries( # 目标库
        ${PROJECT_NAME}

        # 目标库需要链接的库
        # log-lib 是上面 find_library 指定的变量名
        ${log-lib} )