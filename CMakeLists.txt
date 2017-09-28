cmake_minimum_required(VERSION 3.8)
project(plexDrive)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_FILE_OFFSET_BITS=64 -DSQLITE_ENABLE_EXPLAIN_COMMENTS")

add_subdirectory(googleDrive)

include_directories(googleDrive/googleDriveApi/include googleDrive/googleDriveApi/rapidjson/include/rapidjson googleDrive/googleDriveApi/curl/include googleDrive/sqlite googleDrive/include)
#include_directories(${GOOGLEDRIVEAPI_INCLUDE_DIR})

set(SOURCE_FILES main.cpp plexDrive.cpp plexDrive.h)
add_executable(plexDrive ${SOURCE_FILES})

if(APPLE)
    target_link_libraries(plexDrive googleDrive googleDriveApi osxfuse sqlite3)
endif()
if(UNIX AND NOT APPLE)
    target_link_libraries(plexDrive googleDrive googleDriveApi fuse sqlite3 pthread)
endif()