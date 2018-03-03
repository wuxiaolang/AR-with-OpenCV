cmake_minimum_required(VERSION 3.8)
project(markerAr)

set(CMAKE_CXX_STANDARD 11)
#寻找opencv库【new add】
find_package( OpenCV REQUIRED )
#添加头文件【new add】
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(SOURCE_FILES v0_1_video.cpp v0_2_cam.cpp v1.0.cpp v2.0.cpp main.cpp v3.0.cpp v4.0.cpp)
add_executable(markerAr ${SOURCE_FILES})

#链接opencv库【new add】
target_link_libraries( markerAr ${OpenCV_LIBS} )