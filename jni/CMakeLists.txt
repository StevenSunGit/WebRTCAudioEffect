cmake_minimum_required(VERSION 3.4.1)
project(jni)

add_subdirectory(automatic-gain-control)
add_subdirectory(noise-suppression)
add_subdirectory(voice-activity-detection)
add_subdirectory(acoustic-echo-cancellation)
add_subdirectory(acoustic-echo-cancellion-mobile)
add_subdirectory(rnnoise)