cmake_minimum_required(VERSION 3.8)
project(googleDrive)

set(CMAKE_CXX_STANDARD 11)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

#boost
find_package(Boost)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()
#curl
find_package(curl)
if(CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    set(CMAKE_CXX_FLAGS "-DSQLITE_DEBUG")
endif()

include_directories(include googleDriveApi/include googleDriveApi/rapidjson/include/rapidjson)

add_subdirectory(googleDriveApi)

set(SOURCE_FILES src/GoogleDrive.cpp include/GoogleDrive.h GoogleDriveCache.cpp GoogleDriveCache.h)
add_library(googleDrive ${SOURCE_FILES})

target_link_libraries(googleDrive googleDriveApi curl ${CMAKE_THREAD_LIBS_INIT})

if(Boost_FOUND)
    target_link_libraries(googleDriveApi ${Boost_LIBRARIES})
endif()