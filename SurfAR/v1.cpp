/*
* 【v1用SURF算法检测目标图像的特征点】
* 涉及到的函数：
* 特征检测函数：detectAndCompute()
* 特征点绘制函数：drawKeypoints()
*/

#include <iostream>
#include <cmath>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace cv::xfeatures2d;

#define MIN_HESSIAN 1000

int main()
{
   //【1】读取目标图像.
   Mat img_object = imread("/home/wu/code/SurfAR/state.jpg");

   //【2】定义描述符和特征点向量.
   Mat descriptors_object;
   std::vector<KeyPoint> keypoints_object;

   // 【3】特征点检测
   Ptr<SURF> detector = SURF::create(MIN_HESSIAN, 4, 3);   //MIN_HESSIAN为最小的hessian矩阵的阈值，已定义为300.
   //等价于Ptr<SURF> detector ;  detector = SURF::create(300, 5, 4);
   //检测图像特征点并计算描述子，参数：目标图                特征点向量          描述子图像
   detector->detectAndCompute( img_object, Mat(), keypoints_object, descriptors_object );

   // 【4】特征点绘制.
   Mat out_object;
   drawKeypoints(img_object, keypoints_object, out_object, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

   // 【5】显示.
   imshow("SURF特征检测", out_object);
   waitKey(0);

   return 0;
}