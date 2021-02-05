cmake_minimum_required(VERSION 3.8)
project(flappycat_android LANGUAGES CXX)

file(GLOB_RECURSE FLAPPYCAT_ANDROID_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/android/*.hpp")
file(GLOB_RECURSE FLAPPYCAT_ANDROID_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/android/*.cpp")

source_group("android_client" FILES ${FLAPPYCAT_ANDROID_HEADERS} ${FLAPPYCAT_ANDROID_SOURCE})

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/jni/")

add_library(flappycat_android SHARED

    ${FLAPPYCAT_ANDROID_HEADERS}
    ${FLAPPYCAT_ANDROID_SOURCE}        
)

target_compile_features(flappycat_android PRIVATE cxx_std_17)
target_link_libraries(flappycat_android PRIVATE EGL GLESv2 android log flappycat)
target_compile_definitions(flappycat_android PRIVATE FLAPPYCAT_ANDROID)

