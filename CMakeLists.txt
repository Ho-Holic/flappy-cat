cmake_minimum_required(VERSION 3.8)

project(flappycat VERSION 0.1 LANGUAGES CXX)

# configs

option(BUILD_TESTING "" OFF)

set(FLAPPYCAT_DESKTOP_PLATFORM TRUE)

# dependencies

if (FLAPPYCAT_DESKTOP_PLATFORM)
    find_package(Qt5 COMPONENTS Gui REQUIRED)
endif()

file(GLOB_RECURSE FLAPPYCAT_GAME_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/game/*.hpp")
file(GLOB_RECURSE FLAPPYCAT_GAME_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/game/*.cpp")

file(GLOB_RECURSE FLAPPYCAT_ENGINE_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/engine/*.hpp")
file(GLOB_RECURSE FLAPPYCAT_ENGINE_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/engine/*.cpp")

file(GLOB_RECURSE FLAPPYCAT_QT_CLIENT_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/qt/*.hpp")
file(GLOB_RECURSE FLAPPYCAT_QT_CLIENT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/qt/*.cpp")

source_group("game" FILES ${FLAPPYCAT_GAME_HEADERS} ${FLAPPYCAT_GAME_SOURCE})
source_group("engine" FILES ${FLAPPYCAT_ENGINE_HEADERS} ${FLAPPYCAT_ENGINE_SOURCE})
source_group("qt_client" FILES ${FLAPPYCAT_QT_CLIENT_HEADERS} ${FLAPPYCAT_QT_CLIENT_SOURCES})

# create flappycat object

add_executable(flappycat

    ${FLAPPYCAT_GAME_HEADERS}
    ${FLAPPYCAT_GAME_SOURCE}

    ${FLAPPYCAT_ENGINE_HEADERS}
    ${FLAPPYCAT_ENGINE_SOURCE}

    ${FLAPPYCAT_QT_CLIENT_HEADERS}
    ${FLAPPYCAT_QT_CLIENT_SOURCES}        
)

# setup flappycat object

target_include_directories(flappycat PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/game/")
target_include_directories(flappycat PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/engine/")
target_include_directories(flappycat PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/")

target_compile_options(flappycat PRIVATE -fno-rtti -Wall -Werror -Wno-unused-variable -Wno-unused-lambda-capture)
target_compile_features(flappycat PRIVATE cxx_std_17)

set_target_properties(flappycat PROPERTIES CXX_EXTENSIONS OFF)

if (FLAPPYCAT_DESKTOP_PLATFORM)
    target_link_libraries(flappycat PRIVATE Qt5::Gui)
    target_compile_definitions(flappycat PRIVATE FLAPPYCAT_QT TAG=\"FlappyCat\")
endif()
