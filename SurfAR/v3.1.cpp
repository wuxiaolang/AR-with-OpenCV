///*
// * 【v3.1视频帧与目标图像匹配】
// * 实现了特征提取与匹配，未进行筛选
// * 问题：当相机画面太黑或者太亮时奔溃
// */
//
//#include <iostream>
//#include <cmath>
//#include <opencv2/core.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/features2d.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/calib3d.hpp>
//#include <opencv2/xfeatures2d.hpp>
//
//using namespace cv;
//using namespace cv::xfeatures2d;
//
//#define MIN_HESSIAN 1000
//
//int main()
//{
//    //【1】读取图像.
//    Mat img_object = imread("/home/wuxiaolang/code/AR/test0126/SLAM.jpeg");     //目标图像
//    VideoCapture capture(0);
//    Mat img_scene;  //用于读取视频帧.
//
//    //【2】定义描述符和特征点向量.
//    Mat descriptors_object;                     //目标图像
//    std::vector<KeyPoint> keypoints_object;     //目标图像
//    Mat descriptors_scene;                          //待检测图像
//    std::vector<KeyPoint> keypoints_scene;          //待检测图像
//    FlannBasedMatcher matcher;
//    Mat out_matches;                                //定义匹配图像用于输出.
//
//    // 【3】特征点检测
//    Ptr<SURF> detector = SURF::create(MIN_HESSIAN, 4, 3);   //MIN_HESSIAN为最小的hessian矩阵的阈值，已定义为300.
//    //检测图像特征点并计算描述子，参数：目标图                特征点向量          描述子图像
//    detector->detectAndCompute( img_object, Mat(), keypoints_object, descriptors_object );      //目标图像
//
//    while(1)
//    {
//        capture >> img_scene;
//        if(!img_scene.empty())
//        {
//            //检测视频帧的特征，得到特征点keypoints_scene和描述符descriptors_scene.
//            detector->detectAndCompute( img_scene, Mat(), keypoints_scene, descriptors_scene );
//
//            Mat out_1, out_2;
//            drawKeypoints(img_object, keypoints_object, out_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);    //目标图像
//            drawKeypoints(img_scene, keypoints_scene, out_2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);      //相机图像
//            imshow("1", out_1);
//            imshow("相机图像", out_2);
//
//            //【5】实例化一个匹配器.
//            std::vector<DMatch> matches;      //定义匹配向量matches
//            matcher.match( descriptors_object, descriptors_scene, matches, 2);      //match()函数为描述符查找最佳的匹配
//
//            // 【7】显示结果.
//            //当特征点太少时不调用drawMatches（否则会崩溃）.
//            if(keypoints_scene.size() < 10)
//                continue;
//            drawMatches(img_object, keypoints_object, img_scene, keypoints_scene, matches, out_matches);
//            imshow("特征匹配", out_matches);
//
//            waitKey(30);
//        }
//    }
//    return 0;
//}