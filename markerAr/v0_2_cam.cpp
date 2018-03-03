///*
// * 此程序用于读取相机图像
// *
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
//    Mat image;
//
//    if(!capture.isOpened())
//    {
//        std::cout << "读取相机失败" << std::endl;
//        return -1;
//    }
//
//    while(capture.grab())
//    {
//        capture >> image;
//        resize(image, image, Size(960, 720));
//        std::cout << "图像大小：" << image.cols << "*" << image.rows << std::endl;
//        imshow("相机", image);
//        waitKey(1);
//    }
//
//    return 0;
//}
