///*
// * 【v3.1】
// * 加入了筛选
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
//
//    // 【3】特征点检测
//    Ptr<SURF> detector = SURF::create(MIN_HESSIAN, 4, 3);   //MIN_HESSIAN为最小的hessian矩阵的阈值，已定义为300.
//    //检测图像特征点并计算描述子，参数：目标图                特征点向量          描述子图像
//    detector->detectAndCompute( img_object, Mat(), keypoints_object, descriptors_object );      //目标图像
//
//    // 【4】特征点绘制.
//    //Mat out_object, out_2;
//    //drawKeypoints(img_object, keypoints_object, out_object, Scalar::all(-1), DrawMatchesFlags::DEFAULT);    //目标图像
//    //drawKeypoints(img_2, keypoints_2, out_2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);                   //待检测图像
//
//    while(1)
//    {
//        capture >> img_scene;
//        if(!img_scene.empty())
//        {
//            //检测视频帧的特征，得到特征点keypoints_scene和描述符descriptors_scene.
//            detector->detectAndCompute(img_scene, Mat(), keypoints_scene, descriptors_scene);
//            Mat out_1, out_2;
//            drawKeypoints(img_object, keypoints_object, out_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);    //目标图像
//            drawKeypoints(img_scene, keypoints_scene, out_2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);      //相机图像
//            imshow("1", out_1);
//            imshow("相机图像", out_2);
//
//            //【5】实例化一个匹配器.
//            std::vector<DMatch> matches;      //定义匹配向量matches
//            matcher.match(descriptors_object, descriptors_scene, matches, 2);      //match()函数为描述符查找最佳的匹配
//
//            // 【6】筛选出优良的匹配点
//            double max_dist = 0;
//            double min_dist = 100;
//            // 计算特征点之间的最大最小距离
//            for (int i = 0; i < descriptors_object.rows; i++) {
//                double dist = matches[i].distance;
//                if (dist < min_dist)
//                    min_dist = dist;
//                if (dist > max_dist)
//                    max_dist = dist;
//            }
//            printf("-- Max dist : %f \n", max_dist );
//            printf("-- Min dist : %f \n", min_dist );
//
//            //保存良好的匹配结果在good_matches中（距离小于三倍的最小距离）
//            std::vector< DMatch > good_matches;
//            for( int i = 0; i < descriptors_object.rows; i++ )
//            {
//                if( matches[i].distance < 4*min_dist )
//                {
//                    good_matches.push_back( matches[i]);
//                }
//            }
//
//            // 【7】显示结果.
//            Mat out_matches;     //定义匹配图像用于输出.
//            drawMatches(img_object, keypoints_object, img_scene, keypoints_scene, good_matches, out_matches);
//            imshow("特征匹配", out_matches);
//
//            //imshow("cam", img_scene);
//            waitKey(30);
//        }
//    }
//    return 0;
//}