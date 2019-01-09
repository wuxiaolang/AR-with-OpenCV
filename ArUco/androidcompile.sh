#!/bin/bash

if [ $# -ne 2 ]
then
  echo "usage: OpenCV_JAVA_ROOT_DIR NDK [mode]"
  exit
fi


APILEVEL=19
OPENCV_DIR=$1/sdk/native/jni
NDK=$2
mkdir build_android -p
cd build_android
echo "cmake ..  -DCMAKE_TOOLCHAIN_FILE=$NDK/build/cmake/android.toolchain.cmake  -DANDROID_NDK=$NDK -DANDROID_NATIVE_API_LEVEL=$APILEVEL -DANDROID_ABI="armeabi-v7a with NEON" -DOpenCV_DIR=$OPENCV_DIR  -DBUILD_UTILS=OFF  -DANDROID_STL=gnustl_shared -DCMAKE_BUILD_TYPE=Release && make VERBOSE=1"

cmake ..  -DCMAKE_TOOLCHAIN_FILE=$NDK/build/cmake/android.toolchain.cmake  -DANDROID_NDK=$NDK -DANDROID_NATIVE_API_LEVEL=$APILEVEL -DANDROID_ABI="armeabi-v7a with NEON" -DOpenCV_DIR=$OPENCV_DIR  -DBUILD_UTILS=OFF  -DANDROID_STL=gnustl_shared  -DCMAKE_BUILD_TYPE=Release&& make VERBOSE=1 

#check https://developer.android.com/ndk/guides/cmake.html#variables
