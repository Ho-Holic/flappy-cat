cmake_minimum_required(VERSION 3.8)
project(flappycat LANGUAGES CXX)

file(GLOB_RECURSE FLAPPYCAT_GAME_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/game/*.hpp")
file(GLOB_RECURSE FLAPPYCAT_GAME_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/game/*.cpp")

file(GLOB_RECURSE FLAPPYCAT_ENGINE_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/engine/*.hpp")
file(GLOB_RECURSE FLAPPYCAT_ENGINE_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/engine/*.cpp")

file(GLOB_RECURSE FLAPPYCAT_ANDROID_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/android/*.hpp")
file(GLOB_RECURSE FLAPPYCAT_ANDROID_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/android/*.cpp")

add_library(flappycat SHARED
    ${FLAPPYCAT_GAME_HEADERS}
    ${FLAPPYCAT_GAME_SOURCE}
    
    ${FLAPPYCAT_ENGINE_HEADERS}
    ${FLAPPYCAT_ENGINE_SOURCE}

    ${FLAPPYCAT_ANDROID_HEADERS}
    ${FLAPPYCAT_ANDROID_SOURCE}        
)

target_include_directories(flappycat PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/game/")
target_include_directories(flappycat PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/engine/")
target_include_directories(flappycat PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/")

#
# NOTE: -Wno-format-security
#
# disable formatted printf warning rises at 'Log::i(TAG, "some string");
# when we pass rvalue of a 'const char*' as argument and compiler
# thinks it can contain some unmatched format specifiers and can lead to
# security issues, but we are know what are we doing

target_compile_options(flappycat PRIVATE -fno-rtti -Wall -Werror -Wno-unused-variable -Wno-unused-lambda-capture -Wno-format-security)
target_compile_features(flappycat PRIVATE cxx_std_17)

target_link_libraries(flappycat PRIVATE EGL GLESv2 android log)

target_compile_definitions(flappycat PRIVATE FLAPPYCAT_ANDROID TAG=\"FlappyCat\")
