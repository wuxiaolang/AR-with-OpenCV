///*
// *【v2.0】提取轮廓、绘制顶点
// * 主要涉及轮廓提取的内容
// */
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/calib3d/calib3d.hpp>
//#include <iostream>
//#include <vector>
//
//using namespace cv;
//using namespace std;
//
////连接四边形四个点的函数声明.
//void linkPoint(Mat image, vector<Point2f> points, Scalar color);
//
//int main()
//{
//    //读取相机视频.
//    VideoCapture capture(0);
//
//    //变量定义.
//    Mat image, grayImage, blurImage, threshImage;
//    vector<vector<Point>> contours;             //图像轮廓contours.
//    Scalar color = Scalar(0, 255, 0);           //颜色为绿色.
//
//    //检测相机是否调用或者占用.
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
//
//        //isFind用于判断是否发现了四边形.
//        int isFind = 0;
//
//        //图像处理.
//        cvtColor(image, grayImage, CV_BGR2GRAY);
//        blur(grayImage, blurImage, Size(5, 5));
//        threshold(blurImage, threshImage, 100, 255, THRESH_OTSU);
//
//        //提取图像的轮廓contours.
//        findContours(threshImage, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
////        //遍历图像的所有轮廓并描绘出来.
////        for(int i = 0; i != contours.size(); ++i)
////        {
////            for(int j = 0; j != contours[i].size(); ++j)      //contours[i]是图像的第i条轮廓
////                circle(image, contours[i][j], 1, color, -1);  //contours[i][j]是图像第i条轮廓中的第j个点.
////        }
//
//        //定义多边形轮廓contours_poly和四边形轮廓squares.
//        //不要定义在外面，因为每一帧都要开辟一个新的空间.！！！！！！！！
//        vector<vector<Point> > contours_poly(contours.size());  //逼近之后的多边形轮廓contours_poly.
//        vector<vector<Point2f> > squares;
//
//        //遍历处理每一个轮廓.
//        for (unsigned int i = 0; i != contours.size(); ++i)
//        {
//            //使用多边形近似将轮廓近似为更简单的多边形存储在contours_poly中.
//            approxPolyDP(contours[i], contours_poly[i], arcLength(Mat(contours[i]), true)*0.02, true);
//
//            //取面积足够大且为凸包的四边形作为Marker
//            if( contours_poly[i].size() == 4 && fabs(contourArea(Mat(contours_poly[i]))) > 1000 && isContourConvex(Mat(contours_poly[i])) )
//            {
//                vector<Point2f> square;         //square记录【单个】四边形轮廓的四个顶点.
//                for (int j = 0; j < 4; ++j)
//                {
//                    square.push_back(Point2f(contours_poly[i][j].x,contours_poly[i][j].y));
//                }
////                //标记出矩形的四个顶点
////                for(int j = 0; j != square.size(); ++j)
////                    circle(image, square[j], 5, color, -1);
//
//                squares.push_back(square);      //squares记录多组四边形轮廓.
//
//                isFind = 1;                     //将isFind置为1.
//            }
//        }
//
//        if(isFind == 1)
//        {
//            //取第一个检测到的四边形轮廓作为跟踪目标.
//            vector<Point2f> square = squares[0];
//            linkPoint(image, square, color);
//        }
//
//        imshow("相机", image);
//        waitKey(1);
//    }
//
//    return 0;
//}
//
////连接四个点构成轮廓
//void linkPoint(Mat image, vector<Point2f> points, Scalar color)
//{
//    line(image, points[0], points[1], color, 3);
//    line(image, points[1], points[2], color, 3);
//    line(image, points[2], points[3], color, 3);
//    line(image, points[3], points[0], color, 3);
//}