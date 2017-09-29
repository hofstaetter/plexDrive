cmake_minimum_required(VERSION 3.8)
project(plexDrive)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_FILE_OFFSET_BITS=64")

#boost
find_package(Boost)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_subdirectory(googleDrive)

if(APPLE)
    include_directories(googleDrive/googleDriveApi/include googleDrive/googleDriveApi/rapidjson/include/rapidjson googleDrive/googleDriveApi/curl/include googleDrive/sqlite googleDrive/include /usr/local/include/osxfuse)
#include_directories(${GOOGLEDRIVEAPI_INCLUDE_DIR})
endif()
if(UNIX AND NOT APPLE)
    include_directories(googleDrive/googleDriveApi/include googleDrive/googleDriveApi/rapidjson/include/rapidjson googleDrive/googleDriveApi/curl/include googleDrive/sqlite googleDrive/include)
endif()

set(SOURCE_FILES PlexDrive.cpp PlexDrive.h)
add_executable(plexDrive ${SOURCE_FILES})

target_link_libraries(plexDrive googleDrive googleDriveApi sqlite3)
if(APPLE)
    target_link_libraries(plexDrive osxfuse)
endif()
if(UNIX AND NOT APPLE)
    target_link_libraries(plexDrive fuse)
endif()
if(Boost_FOUND)
    target_link_libraries(googleDriveApi ${Boost_LIBRARIES})
endif()