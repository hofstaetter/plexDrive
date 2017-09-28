cmake_minimum_required(VERSION 3.8)
project(googleDriveApi)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_VERBOSE_MAKEFILE ON)

#include dependencies
include_directories(include rapidjson/include/rapidjson curl/include/curl)

file(GLOB SOURCE_FILES
        include/*.h
        src/*.cpp)
add_library(googleDriveApi ${SOURCE_FILES})

if(APPLE)
    target_link_libraries(googleDriveApi /usr/local/lib/libcurl.dylib)
endif()
if(UNIX AND NOT APPLE)
    target_link_libraries(googleDriveApi curl)
endif()