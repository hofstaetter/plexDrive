cmake_minimum_required(VERSION 3.8)
project(googleDrive)

set(CMAKE_CXX_STANDARD 11)

include_directories(include googleDriveApi/include googleDriveApi/rapidjson/include/rapidjson googleDriveApi/curl/include/curl)

add_subdirectory(googleDriveApi)

set(SOURCE_FILES src/googleDrive.cpp include/googleDrive.h)
add_library(googleDrive ${SOURCE_FILES})

target_link_libraries(googleDrive googleDriveApi)