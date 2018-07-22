cmake_minimum_required(VERSION 3.5.1)
project(imageBasics)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(imageBasics ${SOURCE_FILES})

# 寻找 OpenCV 库
find_package( OpenCV REQUIRED )
# 添加头文件
include_directories( ${OpenCV_INCLUDE_DIRS} )
# 链接 OpenCV 库
target_link_libraries( imageBasics ${OpenCV_LIBS})