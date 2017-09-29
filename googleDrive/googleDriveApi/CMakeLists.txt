cmake_minimum_required(VERSION 3.8)
project(googleDriveApi)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_VERBOSE_MAKEFILE ON)

#boost
find_package(Boost COMPONENTS iostreams)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()
#curl
find_package(curl)
if(CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
endif()

#include dependencies
include_directories(include rapidjson/include/rapidjson)

file(GLOB SOURCE_FILES include/files/File.h
        include/*.h
        src/*.cpp)
add_library(googleDriveApi ${SOURCE_FILES} )

target_link_libraries(googleDriveApi curl)
if(Boost_FOUND)
    target_link_libraries(googleDriveApi ${Boost_LIBRARIES})
endif()