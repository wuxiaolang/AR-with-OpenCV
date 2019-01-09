/*
* 【v2两张图像之间的特征匹配】
* 涉及到的知识：
* 特征匹配器：FlannBasedMatcher
* 匹配点筛选
* 匹配点绘制drawMatches()
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
   Mat img_object = imread("/home/wu/code/SurfAR/state.jpg");     //目标图像
   Mat img_2 = imread("/home/wu/code/SurfAR/state2.jpg");         //待检测图像

   //【2】定义描述符和特征点向量.
   Mat descriptors_object;                     //目标图像
   std::vector<KeyPoint> keypoints_object;     //目标图像
   Mat descriptors_2;                          //待检测图像
   std::vector<KeyPoint> keypoints_2;          //待检测图像

   // 【3】特征点检测
   Ptr<SURF> detector = SURF::create(MIN_HESSIAN, 4, 3);   //MIN_HESSIAN为最小的hessian矩阵的阈值，已定义为300.
   //检测图像特征点并计算描述子，参数：目标图                特征点向量          描述子图像
   detector->detectAndCompute( img_object, Mat(), keypoints_object, descriptors_object );      //目标图像
   detector->detectAndCompute( img_2, Mat(), keypoints_2, descriptors_2 );                     //待检测图像


   // 【4】特征点绘制.
   Mat out_object, out_2;
   drawKeypoints(img_object, keypoints_object, out_object, Scalar::all(-1), DrawMatchesFlags::DEFAULT);    //目标图像
   drawKeypoints(img_2, keypoints_2, out_2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);                   //待检测图像

   // 【5】实例化一个匹配器.
   FlannBasedMatcher matcher;
   std::vector<DMatch> matches;      //定义匹配向量matches
   matcher.match( descriptors_object, descriptors_2, matches, 2);      //match()函数为描述符查找最佳的匹配

   // 【6】筛选出优良的匹配点
   double max_dist = 0;
   double min_dist = 100;
   // 计算特征点之间的最大最小距离
   for( int i = 0; i < descriptors_object.rows; i++ )
   {
       double dist = matches[i].distance;
       if( dist < min_dist )
           min_dist = dist;
       if( dist > max_dist )
           max_dist = dist;
   }
   //printf("-- Max dist : %f \n", max_dist );
   //printf("-- Min dist : %f \n", min_dist );
   //保存良好的匹配结果在good_matches中（距离小于三倍的最小距离）
   std::vector< DMatch > good_matches;
   for( int i = 0; i < descriptors_object.rows; i++ )
   {
       if( matches[i].distance < 4*min_dist )
       {
           good_matches.push_back( matches[i]);
       }
   }

   // 【7】显示结果.
   imshow("目标图特征点", out_object);
   imshow("检测图特征点", out_2);
   Mat img_matches, good_img;     //定义匹配图像用于输出.
   drawMatches(img_object, keypoints_object, img_2, keypoints_2, matches, img_matches);
   drawMatches(img_object, keypoints_object, img_2, keypoints_2, good_matches, good_img);
   imshow("未经筛选的匹配", img_matches);
   imshow("筛选之后的匹配", good_img);

   waitKey(0);

   return 0;
}