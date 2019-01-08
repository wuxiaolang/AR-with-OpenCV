cmake_minimum_required(VERSION 2.8)
project(WarpPerspective_MakerArDemo_wu)

set(CMAKE_CXX_STANDARD 11)
# 设置编译模式Release.
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release)
ENDIF()
MESSAGE("Build type: " ${CMAKE_BUILD_TYPE})

#添加opencv库文件和头文件.
find_package( OpenCV 3.3.1 REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# 指定工程的可执行文件,并链接 ${OpenCV_LIBS} 库.
# v0_1_video.cpp
add_executable(v0_1_video v0_1_video.cpp)
target_link_libraries(v0_1_video ${OpenCV_LIBS})
# v0_2_cam.cpp
add_executable(v0_2_cam v0_2_cam.cpp)
target_link_libraries(v0_2_cam ${OpenCV_LIBS})
# v1_process.cpp
add_executable(v1_process v1_process.cpp)
target_link_libraries(v1_process ${OpenCV_LIBS})
# v2_outline.cpp
add_executable(v2_outline v2_outline.cpp)
target_link_libraries(v2_outline ${OpenCV_LIBS})
# v3_warpPerspective.cpp
add_executable(v3_warpPerspective v3_warpPerspective.cpp)
target_link_libraries(v3_warpPerspective ${OpenCV_LIBS})
# v4_coordinate.cpp
add_executable(v4_coordinate v4_coordinate.cpp)
target_link_libraries(v4_coordinate ${OpenCV_LIBS})
# v5_myWarpPerspective.cpp
add_executable(v5_myWarpPerspective v5_myWarpPerspective.cpp)
target_link_libraries(v5_myWarpPerspective ${OpenCV_LIBS})
