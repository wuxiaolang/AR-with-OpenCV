cmake_minimum_required(VERSION 3.8)
project(test0126)

set(CMAKE_CXX_STANDARD 11)

#寻找opencv库【new add】
find_package( OpenCV REQUIRED )
#添加头文件【new add】
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(SOURCE_FILES main.cpp cam.cpp myAr_surf.cpp v1.cpp v2.cpp v3.cpp v3.1.cpp v3.2.cpp v4.cpp v4.1.cpp v4.2.cpp)
add_executable(test0126 ${SOURCE_FILES})

#链接opencv库【new add】
target_link_libraries( test0126 ${OpenCV_LIBS} )