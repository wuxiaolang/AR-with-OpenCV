////#include <opencv2/core/core.hpp>        //openCV核心库
//#include <opencv2/imgproc/imgproc.hpp>  //openCV图像处理库
//#include <opencv2/highgui/highgui.hpp>  //用户界面库，播视频要用
//#include <opencv2/calib3d/calib3d.hpp>  //相机校准，姿态估计用
//
//using namespace std;
//using namespace cv;
//
////Scalar是一个四元组,这里对应bgra
////Scalar blue(255, 0, 0);
////Scalar green(0, 255, 0);
////Scalar red(0, 0, 255);
//
////所使用的marker的边大小，可自定义
//const int marker_width = 200;
//
//int main(int argc, char** argv) {
//
//    //Mat即矩阵，常常用Mat存储图像
//    Mat image;
//
//    //捕捉视频用的对象，参数改为0会使用摄像头输入。
//    VideoCapture cap("/home/wuxiaolang/视频/demo.mp4");
//
//    if(!cap.isOpened())
//        return -1;
//
//    //cap.grab()即抓取下一帧
//    while (cap.grab())
//    {
//        //解码抓取的帧并放入image中
//        cap.retrieve(image);
//
//        //新建窗口并显示捕捉到的图片，第一个参数为窗口名。
//        cv::imshow("image", image);
//
//        //延迟100ms 自己机子上做就设置1
//        cv::waitKey(1);
//    }
//    return 0;
//}