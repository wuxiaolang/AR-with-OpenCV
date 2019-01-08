/**
 * @file 	v4_coordinate.cpp， 对应与可执行文件 v4_coordinate
 * @brief 	三维到二维空间转换,内外参数的获取,3D——2D投影,坐标轴绘制
 * @author	wuyanminmax@gmail.com
 * @date 	2018.01.29
 */

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <iostream>

using namespace cv;
using namespace std;

const int marker_width = 200;
//连接四边形四个点的函数声明.
void linkPoint(Mat image, vector<Point2f> points, Scalar color);
//sort函数用于对四边形的四个点进行排序.
void sort(vector<Point2f>& square);

int main()
{
    std::cout << "【v4_coordinate】 is running ……" << std::endl;

    //读取相机视频.
    VideoCapture capture(0);

    //变量定义.
    Mat image, grayImage, blurImage, threshImage;
    vector<vector<Point>> contours;             //图像轮廓contours.
    Scalar green = Scalar(0, 255, 0);
    Scalar red = Scalar(0, 0, 255);
    Scalar blue = Scalar(255, 0, 0);

    //检测相机是否调用或者占用.
    if(!capture.isOpened())
    {
        std::cout << "读取相机失败" << std::endl;
        return -1;
    }

    while(capture.grab())
    {
        //获取相机图像.
        capture >> image;

        //isFind用于判断是否发现了四边形.
        int isFind = 0;

        //图像处理.
        cvtColor(image, grayImage, CV_BGR2GRAY);
        blur(grayImage, blurImage, Size(5, 5));
        threshold(blurImage, threshImage, 100, 255, THRESH_OTSU);

        //提取图像的轮廓contours.
        findContours(threshImage, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
//        //遍历图像的所有轮廓并描绘出来.
//        for(int i = 0; i != contours.size(); ++i)
//        {
//            for(int j = 0; j != contours[i].size(); ++j)      //contours[i]是图像的第i条轮廓
//                circle(image, contours[i][j], 1, color, -1);  //contours[i][j]是图像第i条轮廓中的第j个点.
//        }

        //定义多边形轮廓contours_poly和四边形轮廓squares.
        //不要定义在外面，因为每一帧都要开辟一个新的空间.！！！！！！！！
        vector<vector<Point> > contours_poly(contours.size());  //逼近之后的多边形轮廓contours_poly.
        vector<vector<Point2f> > squares;

        //遍历处理每一个轮廓.
        for (unsigned int i = 0; i != contours.size(); ++i)
        {
            //使用多边形近似将轮廓近似为更简单的多边形存储在contours_poly中.
            approxPolyDP(contours[i], contours_poly[i], arcLength(Mat(contours[i]), true)*0.02, true);

            //取面积足够大且为凸包的四边形作为Marker
            if( contours_poly[i].size() == 4 && fabs(contourArea(Mat(contours_poly[i]))) > 10000 && isContourConvex(Mat(contours_poly[i])))
            {
                vector<Point2f> square;         //square记录【单个】四边形轮廓的四个顶点.
                for (int j = 0; j < 4; ++j)
                {
                    square.push_back(Point2f(contours_poly[i][j].x,contours_poly[i][j].y));
                }
//                //标记出矩形的四个顶点
//                for(int j = 0; j != square.size(); ++j)
//                    circle(image, square[j], 5, color, -1);

                squares.push_back(square);      //squares记录多组四边形轮廓.

                isFind = 1;                     //将isFind置为1.
            }
        }

        if(isFind == 1)
        {
            //取第一个检测到的四边形轮廓作为跟踪目标.
            vector<Point2f> square = squares[0];
            linkPoint(image, square, green);

            //绘出目标第一个点（左上角）以作为方向判断的依据.
            //circle(image, square[0], 5, red, 3);
            //对四边形的四个点进行顺时针排序.
            sort(square);

            //++++++++++++++++++++++++++【对轮廓进行仿射变换】+++++++++++++++++++++++++++++START.
            Mat marker;
            //marker_square为标记的形状，一个正方形.
            vector<Point2f> marker_square;
            marker_square.push_back(Point(0,0));                //记录下四个顶点的位置.
            marker_square.push_back(Point(marker_width-1, 0));
            marker_square.push_back(Point(marker_width-1,marker_width-1));
            marker_square.push_back(Point(0, marker_width-1));
            //返回相应四对点的变换矩阵H.
            Mat H = getPerspectiveTransform(square, marker_square);
            //原图像通过仿射变换之后得到marker.
            warpPerspective(grayImage, marker,H, Size(marker_width,marker_width));
            //对变换之后的图进行二值化.
            threshold(marker, marker, 125, 255, THRESH_BINARY|THRESH_OTSU);
            //查看仿射变换的效果.
            //imshow("仿射变换", marker);
            //++++++++++++++++++++++++++【对轮廓进行仿射变换】+++++++++++++++++++++++++++++END.

            //+++++++++++++++++++++++++++++【标记的定位】+++++++++++++++++++++++++++++++START.
            //从左上角开始顺时针绘制一个正方形区域作为追踪目标.
            vector<Point> direction_point = {{50, 50} ,{150, 50},{150, 150},{50,150}};
            int direction;
            for (int i = 0; i < 4; ++i)
            {
                Point p = direction_point[i];
                //countNonZero计算非零元素的个数.以（p.x-25,p.y-25）为左上角坐标，marker_width/4为长宽的矩形.
                if (countNonZero(marker(Rect(p.x-25,p.y-25,marker_width/4,marker_width/4))) > 20)
                {   //如果符合，则该位置为白块的位置.
                    direction = i;
                    break;
                }
            }
            for (int i = 0; i < direction; ++i)
            {
                //根据方位左旋转数组.
                rotate(square.begin(), square.begin() + 1, square.end());
            }
            circle(image, square[0], 5, red, 3);
            //+++++++++++++++++++++++++++++【标记的定位】+++++++++++++++++++++++++++++++END.

            //NOTE ++++++++++++++++++++++++++++【获取内外参数】+++++++++++++++++++++++++++++START.
            //获取相机内参.
            FileStorage fs("/home/wu/github/WarpPerspective_MakerArDemo_wu/calibrate/out_camera_data.xml", FileStorage::READ);
            Mat intrinsics, distortion;
            fs["Camera_Matrix"] >> intrinsics;              //读取相机内参intrinsics.
            fs["Distortion_Coefficients"] >> distortion;    //畸变五元组distortion.
            //4个顶点对应的3D坐标.
            vector<Point3f> objectPoints;
            //由于opencv中y轴向下（x轴在y轴前），为了便于观察视觉效果，这里y都取负.
            objectPoints.push_back(Point3f(-1, 1, 0));
            objectPoints.push_back(Point3f(1, 1, 0));
            objectPoints.push_back(Point3f(1, -1, 0));
            objectPoints.push_back(Point3f(-1, -1, 0));
            Mat objectPointsMat(objectPoints);
            //求解外参.
            Mat rvec;       //旋转矩阵rvec.
            Mat tvec;       //平移向量tvec.
            solvePnP(objectPointsMat, square, intrinsics, distortion, rvec, tvec);
            //输出外参.
            //cout << "rvec: " << rvec << endl;
            //cout << "tvec: " << tvec << endl;
            //++++++++++++++++++++++++++++【获取内外参数】+++++++++++++++++++++++++++++END.

            //NOTE +++++++++++++++++++++++++++++【绘制坐标轴】+++++++++++++++++++++++++++++START.
            //3D坐标.
            vector<Point3f> line3dx = {{0, 0, 0}, {2, 0, 0}};      //x轴从{0, 0, 0}到{2, 0, 0}
            vector<Point3f> line3dy = {{0, 0, 0}, {0, 2, 0}};
            vector<Point3f> line3dz = {{0, 0, 0}, {0, 0, 2}};
            //映射后的点坐标.
            vector<Point2f> line2dx;
            vector<Point2f> line2dy;
            vector<Point2f> line2dz;
            //做点映射3D—>2D.
            projectPoints(line3dx, rvec, tvec, intrinsics, distortion, line2dx);
            projectPoints(line3dy, rvec, tvec, intrinsics, distortion, line2dy);
            projectPoints(line3dz, rvec, tvec, intrinsics, distortion, line2dz);
            //绘制坐标.
            line(image, line2dx[0], line2dx[1], red, 3);
            line(image, line2dy[0], line2dy[1], blue, 3);
            line(image, line2dz[0], line2dz[1], green, 3);
            //+++++++++++++++++++++++++++++【绘制坐标轴】+++++++++++++++++++++++++++++END.
        }
        imshow("相机", image);
        waitKey(1);
    }

    return 0;
}

//连接四个点构成轮廓
void linkPoint(Mat image, vector<Point2f> points, Scalar color)
{
    line(image, points[0], points[1], color, 3);
    line(image, points[1], points[2], color, 3);
    line(image, points[2], points[3], color, 3);
    line(image, points[3], points[0], color, 3);
}

//对顶点进行顺时针排序.
void sort(vector<Point2f>& square)
{
    Point2f v1 = square[1] - square[0];
    Point2f v2 = square[2] - square[0];

    double o = (v1.x * v2.y) - (v1.y * v2.x);

    if (o < 0.0)
        std::swap(square[1],square[3]);
}