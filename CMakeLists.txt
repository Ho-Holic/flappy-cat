cmake_minimum_required(VERSION 3.8)

project(flappycat_qt VERSION 0.1 LANGUAGES CXX)

# configs
option(BUILD_TESTING "" OFF)

# dependencies
find_package(Qt5 COMPONENTS Gui REQUIRED)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/")

file(GLOB_RECURSE FLAPPYCAT_QT_CLIENT_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/qt/*.hpp")
file(GLOB_RECURSE FLAPPYCAT_QT_CLIENT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/jni/qt/*.cpp")

source_group("qt_client" FILES ${FLAPPYCAT_QT_CLIENT_HEADERS} ${FLAPPYCAT_QT_CLIENT_SOURCES})

# create flappycat object

add_executable(flappycat_qt    

    ${FLAPPYCAT_QT_CLIENT_HEADERS}
    ${FLAPPYCAT_QT_CLIENT_SOURCES}        
)

target_compile_features(flappycat_qt PRIVATE cxx_std_17)
target_compile_definitions(flappycat_qt PUBLIC FLAPPYCAT_QT)
target_link_libraries(flappycat_qt PUBLIC flappycat)
target_link_libraries(flappycat_qt PRIVATE Qt5::Gui)


