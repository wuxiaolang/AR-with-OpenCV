///*
// * 【v4.1绘制了目标图像在场景中的轮廓】
// * 投影问题
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
//    Mat out_matches;     //定义匹配图像用于输出.
//    Mat H_latest = Mat::eye(3, 3, CV_32F); //指定大小和类型的单位矩阵H_latest，可对其进行缩放操作.
//    Mat scene_mask  = Mat::zeros(img_scene.rows, img_scene.cols, CV_8UC1);  //定义一个与场景图像大小一样的掩膜scene_mask.
//
//    // 【3】特征点检测
//    Ptr<SURF> detector = SURF::create(MIN_HESSIAN, 4, 3);   //MIN_HESSIAN为最小的hessian矩阵的阈值，已定义为300.
//    //检测图像特征点并计算描述子，参数：目标图                特征点向量          描述子图像
//    detector->detectAndCompute( img_object, Mat(), keypoints_object, descriptors_object );      //目标图像
//
//    while(1)
//    {
//        bool good_detection = false;
//        capture >> img_scene;
//        if (!img_scene.empty())
//        {
//            //检测视频帧的特征，得到特征点keypoints_scene和描述符descriptors_scene.
//            detector->detectAndCompute(img_scene, Mat(), keypoints_scene, descriptors_scene);
////            Mat out_1, out_2;
////            drawKeypoints(img_object, keypoints_object, out_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);    //目标图像
////            drawKeypoints(img_scene, keypoints_scene, out_2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);      //相机图像
////            imshow("1", out_1);
////            imshow("相机图像", out_2);
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
//
//            //保存良好的匹配结果在good_matches中（距离小于三倍的最小距离）
//            std::vector<DMatch> good_matches;
//            for (int i = 0; i < descriptors_object.rows; i++) {
//                if (matches[i].distance < 3 * min_dist) {
//                    good_matches.push_back(matches[i]);
//                }
//            }
//
//            // 【7】显示结果.
//            //当特征点太少时不调用drawMatches（否则会崩溃）.
//            if (keypoints_scene.size() < 10)
//                continue;
//            drawMatches(img_object, keypoints_object, img_scene, keypoints_scene, good_matches, out_matches);
//            //imshow("特征匹配", out_matches);
//
//            //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//            if(out_matches.data)
//            {
//                // ====================================【获取两幅图像特征点的坐标】======================================START
//                std::vector<Point2f> obj;
//                std::vector<Point2f> scene;
//                for( size_t i = 0; i < good_matches.size(); i++ )
//                {
//                    //-- Get the keypoints from the good matches
//                    //good_matches[i].queryIdx保存目标图像匹配点的序号
//                    //good_matches[i].trainIdx保存相机获取图像的匹配点的序号
//                    obj.push_back( keypoints_object[ good_matches[i].queryIdx ].pt );   //～.pt 为该序号对应的点的坐标，～.pt.x为该点的x坐标.
//                    scene.push_back( keypoints_scene[ good_matches[i].trainIdx ].pt );  //
//                }
////                //输出目标图像和特征点的坐标
////                for(auto o :obj)
////                    std::cout << o << " ";
////                std::cout << "++++++++" << std::endl;
//                // ====================================【获取两幅图像特征点的坐标】=======================================END
//
//                //Homography是一个变换（3*3矩阵），将一张图中的点映射到另一张图中对应的点.
//                //四对以上的匹配点即能够计算出变换矩阵H.
//                Mat H = findHomography( obj, scene, RANSAC );
//                if (!H.data)
//                {
//                    continue;
//                }
//
//                // 获取目标图像的四个角的坐标，存放在向量obj_corners中.
//                std::vector<Point2f> obj_corners(4);
//                obj_corners[0] = cvPoint(0, 0);
//                obj_corners[1] = cvPoint( img_object.cols, 0 );
//                obj_corners[2] = cvPoint( img_object.cols, img_object.rows );
//                obj_corners[3] = cvPoint( 0, img_object.rows );
////                //输出四个角的坐标分别为[0, 0] [671, 0] [671, 960] [0, 960]
////                for(auto o :obj_corners)
////                    std::cout << o << " ";
////                std::cout << "++++++++" << std::endl;
//
//                std::vector<Point2f> scene_corners(4);
//                //scene_corners与输入obj_corners大小相同，H时3*3的浮点型变换矩阵.
//                perspectiveTransform( obj_corners, scene_corners, H);
////                //输出场景的角点坐标[128.488, 4.11725] [415.675, -62.3487] [368.943, 441.185] [42.9645, 424.308]
////                for(auto s :scene_corners)
////                    std::cout << s << " ";
////                std::cout << "++++++++" << std::endl;
//
//                // 检查转换矩阵，变换是否合理.
//                float hDet = abs(determinant(H));       //determinant()返回矩阵H的行列式.
//                if (hDet < 100 && hDet > 0.05)
//                { // Good detection, reasonable transform
//                    H_latest = H;
//                    good_detection = true;
//                }
//
//                // 绘制目标图像在场景中的轮廓=========================================================
//                std::vector<Point2f> match_corners(4);
//                match_corners[0] = scene_corners[0] + Point2f( img_object.cols, 0);
//                match_corners[1] = scene_corners[1] + Point2f( img_object.cols, 0);
//                match_corners[2] = scene_corners[2] + Point2f( img_object.cols, 0);
//                match_corners[3] = scene_corners[3] + Point2f( img_object.cols, 0);
//
//                line( out_matches, scene_corners[0] + Point2f( img_object.cols, 0), scene_corners[1] + Point2f( img_object.cols, 0), Scalar(0, 255, 0), 4 );
//                line( out_matches, scene_corners[1] + Point2f( img_object.cols, 0), scene_corners[2] + Point2f( img_object.cols, 0), Scalar( 0, 255, 0), 4 );
//                line( out_matches, scene_corners[2] + Point2f( img_object.cols, 0), scene_corners[3] + Point2f( img_object.cols, 0), Scalar( 0, 255, 0), 4 );
//                line( out_matches, scene_corners[3] + Point2f( img_object.cols, 0), scene_corners[0] + Point2f( img_object.cols, 0), Scalar( 0, 255, 0), 4 );
//                // 绘制目标图像在场景中的轮廓=========================================================
//                //-- Show detected matches
//                imshow( "SURF", out_matches );
////
////                Mat img_video;
////                vid >> img_video;
////
////
////                // Create the mask for the video in the scene veiw
////                std::vector<Point2f> vid_corners(4);
////                vid_corners[0] = cvPoint( 0, 0 );
////                vid_corners[1] = cvPoint( img_video.cols, 0 );
////                vid_corners[2] = cvPoint( img_video.cols, img_video.rows );
////                vid_corners[3] = cvPoint( 0, img_video.rows );
////
////                cv::Point nonfloat_corners[4];
////                for(int i=0; i<4; i++){
////                    nonfloat_corners[i] = vid_corners[i];
////                }
////                fillConvexPoly(scene_mask, nonfloat_corners, 4, cv::Scalar(255));
////                warpPerspective( scene_mask, scene_mask, H_latest, Size(img_scene.cols,img_scene.rows));
////
////                //Apply transformation to video image and copy with mask
////                warpPerspective( img_video, img_video, H_latest, Size(img_scene.cols,img_scene.rows));
////
////                if(   good_detection )
////                {
////                    img_video.copyTo(img_scene, scene_mask);
////                }
////
////                imshow( "Test", img_scene);
//
//                waitKey(1);
//            }
//
//            waitKey(30);
//        }
//    }
//    return 0;
//}