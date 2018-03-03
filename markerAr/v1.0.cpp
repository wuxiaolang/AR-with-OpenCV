///*
// *【v1.0】处理相机图像
// * 灰度化——>滤波——>二值化
// */
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/calib3d/calib3d.hpp>
//#include <iostream>
//
//using namespace cv;
//
//int main()
//{
//    VideoCapture capture(0);
//    Mat image, grayImage, blurImage, threshImage;
//
//    if(!capture.isOpened())
//    {
//        std::cout << "读取相机失败" << std::endl;
//        return -1;
//    }
//
//    while(capture.grab())
//    {
//        //获取相机图像.
//        capture >> image;
////        resize(image, image, Size(960, 720));
////        std::cout << "图像大小：" << image.cols << "*" << image.rows << std::endl;
//
//        //转换成灰度图.
//        cvtColor(image, grayImage, CV_BGR2GRAY);
//
//        //图像均值滤波处理.
//        blur(grayImage, blurImage, Size(5, 5));
//
//        //图像二值化处理.
//        threshold(blurImage, threshImage, 100, 255, THRESH_OTSU);
//
//        imshow("相机", image);
////        imshow("灰度化", grayImage);
////        imshow("滤波图", blurImage);
////        imshow("二值化", threshImage);
//        waitKey(1);
//    }
//
//    return 0;
//}
