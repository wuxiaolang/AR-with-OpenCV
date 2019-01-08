/**
 * @file 	v0_2_cam.cpp  对应与可执行文件 v0_2_cam
 * @brief 	此程序用于测试用Opencv读取相机图像.
 * @author	wuyanminmax@gmail.com
 * @date 	2018.01.29
 */

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <iostream>

using namespace cv;

int main()
{
   std::cout << "【v0_2_cam】 is running ……" << std::endl;

   // 读取并定义相机图像.
   VideoCapture capture(0);
   Mat image;

   if(!capture.isOpened())
   {
       std::cout << "读取相机失败" << std::endl;
       return -1;
   }

   while(capture.grab())
   {
       capture >> image;
       resize(image, image, Size(960, 720));
       std::cout << "图像大小：" << image.cols << "*" << image.rows << std::endl;
       imshow("相机", image);
       waitKey(1);
   }

   return 0;
}
