cmake_minimum_required(VERSION 3.8)

project(flappycat VERSION 0.1 LANGUAGES CXX)

# configs

option(BUILD_TESTING "" OFF)

set(FLAPPYCAT_DESKTOP_PLATFORM TRUE)

# dependencies

if (FLAPPYCAT_DESKTOP_PLATFORM)
    find_package(Qt5 COMPONENTS Gui REQUIRED)
endif()

file(GLOB_RECURSE FLAPPYCAT_QT_CLIENT_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/qt/*.h")
file(GLOB_RECURSE FLAPPYCAT_QT_CLIENT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/qt/*.cpp")

file(GLOB_RECURSE FLAPPYCAT_CORE_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/engine/core/*.h")
file(GLOB_RECURSE FLAPPYCAT_CORE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/engine/core/*.cpp")

file(GLOB_RECURSE FLAPPYCAT_PROTOTYPE_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/engine/prototype/*.h")
file(GLOB_RECURSE FLAPPYCAT_PROTOTYPE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/engine/prototype/*.cpp")

file(GLOB_RECURSE FLAPPYCAT_PHYSICS_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/engine/physics/*.h")
file(GLOB_RECURSE FLAPPYCAT_PHYSICS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/engine/physics/*.cpp")

set(FLAPPYCAT_GAME_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/game/FlappyCatClock.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/game/FlappyCatColorScheme.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/game/FlappyCatGame.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/game/FlappyCatGameConstants.h"    
)

set(FLAPPYCAT_GAME_SOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/game/FlappyCatColorScheme.cpp"    
    "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/game/FlappyCatGame.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/game/FlappyCatGameConstants.cpp"    
)

file(GLOB_RECURSE FLAPPYCAT_GAME_ENTITY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/game/entity/*.h")
file(GLOB_RECURSE FLAPPYCAT_GAME_ENTITY_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/game/entity/*.cpp")

source_group("qt_client" FILES ${FLAPPYCAT_QT_CLIENT_HEADERS} ${FLAPPYCAT_QT_CLIENT_SOURCES})
source_group("engine" FILES ${FLAPPYCAT_CORE_HEADERS} ${FLAPPYCAT_CORE_SOURCES})
source_group("prototype" FILES ${FLAPPYCAT_PROTOTYPE_HEADERS} ${FLAPPYCAT_PROTOTYPE_SOURCES})
source_group("physics" FILES ${FLAPPYCAT_PHYSICS_HEADERS} ${FLAPPYCAT_PHYSICS_SOURCES})

source_group("game" FILES 
    ${FLAPPYCAT_GAME_HEADERS} 
    ${FLAPPYCAT_GAME_SOURCE} 
    ${FLAPPYCAT_GAME_ENTITY_HEADERS} 
    ${FLAPPYCAT_GAME_ENTITY_SOURCE}
)

# create flappycat object

add_executable(flappycat
    ${FLAPPYCAT_QT_CLIENT_HEADERS}
    ${FLAPPYCAT_QT_CLIENT_SOURCES}    
    
    ${FLAPPYCAT_CORE_HEADERS}
    ${FLAPPYCAT_CORE_SOURCES}
    
    ${FLAPPYCAT_PROTOTYPE_HEADERS}
    ${FLAPPYCAT_PROTOTYPE_SOURCES}
    
    ${FLAPPYCAT_PHYSICS_HEADERS}
    ${FLAPPYCAT_PHYSICS_SOURCES}

    ${FLAPPYCAT_GAME_HEADERS}
    ${FLAPPYCAT_GAME_SOURCE}

    ${FLAPPYCAT_GAME_ENTITY_HEADERS} 
    ${FLAPPYCAT_GAME_ENTITY_SOURCE}
)

# setup flappycat object

target_include_directories(flappycat PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/qt/")
target_include_directories(flappycat PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/engine/")
target_include_directories(flappycat PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/game/")
target_include_directories(flappycat PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/")

target_compile_options(flappycat PRIVATE -fno-rtti -Wall -Werror -Wno-unused-variable -Wno-unused-lambda-capture)
target_compile_features(flappycat PRIVATE cxx_std_17)

set_target_properties(flappycat PROPERTIES CXX_EXTENSIONS OFF)

if (FLAPPYCAT_DESKTOP_PLATFORM)
    target_link_libraries(flappycat PRIVATE Qt5::Gui)
    target_compile_definitions(flappycat PRIVATE FLAPPYCAT_QT TAG=\"FlappyCat\")
endif()
