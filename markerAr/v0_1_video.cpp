/**
 * @file 	v0_1_video.cpp，对应与可执行文件v0_1_video
 * @brief 	此程序用于测试用Opencv读取本地视频中的每一帧图像.
 * @author	wuyanminmax@gmail.com
 * @date 	2018.01.29
 */

#include <opencv2/core/core.hpp>        //openCV核心库
#include <opencv2/imgproc/imgproc.hpp>  //openCV图像处理库
#include <opencv2/highgui/highgui.hpp>  //用户界面库，播视频要用
#include <opencv2/calib3d/calib3d.hpp>  //相机校准，姿态估计用
#include <iostream>

using namespace cv;

//所使用的marker的边大小，可自定义.
const int marker_width = 200;

int main(int argc, char** argv) 
{
   std::cout << "【v0_1_video】 is running ……" << std::endl;

   //定义图像帧.
   Mat image;

   //捕捉视频用的对象，参数改为0或1（电脑相机的编号）会使用摄像头输入。
   VideoCapture cap("/home/wuxiaolang/视频/demo.mp4");

   // 判断是否读取成功.
   if(!cap.isOpened())
       return -1;

   //cap.grab()即抓取下一帧
   while (cap.grab())
   {
       //解码抓取的帧并放入image中
       cap.retrieve(image);

       //新建窗口并显示捕捉到的图片，第一个参数为窗口名。
       cv::imshow("image", image);

       //延迟100ms 自己机子上做就设置1
       cv::waitKey(1);
   }
   return 0;
}