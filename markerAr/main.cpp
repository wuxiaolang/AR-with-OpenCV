//#include <opencv2/core/core.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/calib3d/calib3d.hpp>
//
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
//const int marker_width = 200;
//
//Scalar blue(255, 0, 0);
//Scalar green(0, 255, 0);
//Scalar red(0, 0, 255);
//
//void drawQuad(Mat image, vector<Point2f> points, Scalar color) {
//    line(image, points[0], points[1], color);
//    line(image, points[1], points[2], color);
//    line(image, points[2], points[3], color);
//    line(image, points[3], points[0], color);
//}
//
//
//void clockwise(vector<Point2f>& square){
//    Point2f v1 = square[1] - square[0];
//    Point2f v2 = square[2] - square[0];
//
//    double o = (v1.x * v2.y) - (v1.y * v2.x);
//
//    if (o < 0.0){
//        std::swap(square[1],square[3]);
//    }
//}
//
//int main(int argc, char** argv)
//{
//
//    Mat image;
//    VideoCapture cap(0);
//
//    if(!cap.isOpened())
//        return -1;
//
//    while (cap.grab())
//    {
//        cap.retrieve(image);
//        int mark = 0;
//        Mat grayImage;
//        cvtColor(image, grayImage, CV_RGB2GRAY);
//        Mat blurredImage;
//        blur(grayImage, blurredImage, Size(5, 5));
//        Mat threshImage;
//        threshold(blurredImage, threshImage, 128.0, 255.0, THRESH_OTSU);
//
//        vector<vector<Point> > contours;
//        findContours(threshImage, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
//
//        vector<vector<Point2f> > squares;
//        for (int i = 0; i < contours.size(); i++)
//        {
//            vector<Point> contour = contours[i];
//            vector<Point> approx;
//            approxPolyDP(contour, approx, arcLength(Mat(contour), true)*0.02, true);
//            if( approx.size() == 4 &&
//                fabs(contourArea(Mat(approx))) > 1000 &&
//                isContourConvex(Mat(approx)) )
//            {
//                vector<Point2f> square;
//
//                for (int i = 0; i < 4; ++i)
//                {
//                    square.push_back(Point2f(approx[i].x,approx[i].y));
//                }
//                squares.push_back(square);
//
//                mark = 1;
//            }
//        }
//
//        if(mark == 1)
//        {
//            vector<Point2f> square = squares[0];
//            drawQuad(image, square, green);
//
//            clockwise(square);
//
//            Mat marker;
//            vector<Point2f> marker_square;
//
//            marker_square.push_back(Point(0,0));
//            marker_square.push_back(Point(marker_width-1, 0));
//            marker_square.push_back(Point(marker_width-1,marker_width-1));
//            marker_square.push_back(Point(0, marker_width-1));
//
//
//            Mat transform = getPerspectiveTransform(square, marker_square);
//            warpPerspective(grayImage, marker,transform, Size(marker_width,marker_width));
//            threshold(marker, marker, 125, 255, THRESH_BINARY|THRESH_OTSU);
//
//            vector<Point> direction_point = {{50, 50} ,{150, 50},{150, 150},{50,150}};
//            int direction;
//            for (int i = 0; i < 4; ++i){
//                Point p = direction_point[i];
//                if (countNonZero(marker(Rect(p.x-25,p.y-25,marker_width/4,marker_width/4))) >20){
//                    direction = i;
//                    break;
//                }
//            }
//            for (int i = 0; i < direction; ++i)
//            {
//                rotate(square.begin(), square.begin() + 1, square.end());
//            }
//
//            circle(image, square[0], 5, red);
//        }
//
//        cv::imshow("image", image);
//        cv::waitKey(100);
//    }
//    return 0;
//}