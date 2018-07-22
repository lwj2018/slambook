cmake_minimum_required(VERSION 3.6)
project(feature_extraction)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(feature_extraction ${SOURCE_FILES})

# opencv
find_package( OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(feature_extraction ${OpenCV_LIBS})