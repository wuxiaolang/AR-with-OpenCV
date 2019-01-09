cmake_minimum_required(VERSION 2.8)
project(SurfAR)

set(CMAKE_CXX_STANDARD 11)
# 设置编译模式Release.
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release)
ENDIF()
MESSAGE("Build type: " ${CMAKE_BUILD_TYPE})

#寻找opencv库【new add】
find_package( OpenCV REQUIRED )
#添加头文件【new add】
include_directories( ${OpenCV_INCLUDE_DIRS} )

#set(SOURCE_FILES main.cpp cam.cpp myAr_surf.cpp v1.cpp v2.cpp v3.cpp v3.1.cpp v3.2.cpp v4.cpp v4.1.cpp v4.2.cpp)
add_executable(v1 v1.cpp)
target_link_libraries(v1 ${OpenCV_LIBS})

add_executable(v2 v2.cpp)
target_link_libraries(v2 ${OpenCV_LIBS})

add_executable(v3 v3.cpp)
target_link_libraries(v3 ${OpenCV_LIBS})

add_executable(v4 v4.cpp)
target_link_libraries(v4 ${OpenCV_LIBS})
