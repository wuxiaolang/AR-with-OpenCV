//#include <stdio.h>
//#include <iostream>
//#include <cmath>
//#include <opencv2/core.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/features2d.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/calib3d.hpp>
//#include <opencv2/xfeatures2d.hpp>
//using namespace cv;
//using namespace cv::xfeatures2d;
//
//#define MIN_HESSIAN 300
//
//int main()
//{
//    //开启相机读取视频帧cap.
//    VideoCapture cap(0);
//    //读取视频文件用于叠加显示vid.
//    VideoCapture vid("/home/wuxiaolang/code/AR/test0126/kendirck.mp4");
//
//    //定义目标图像   ，   场景图像   ，  目标描述子     ，   场景描述子      ，   匹配图像
//    Mat img_object, img_scene, descriptors_object, descriptors_scene, img_matches;
//    //定义                   目标特征点向量   ，    场景特征点向量
//    std::vector<KeyPoint> keypoints_object, keypoints_scene;
//    //定义一个特征描述的对象matcher，FlannBasedMatcher类位于xfeatures2d.hpp文件中.
//    FlannBasedMatcher matcher;
//
//    //加载目标图片img_object.
//    img_object = imread("/home/wuxiaolang/code/AR/test0126/temp.jpg", IMREAD_GRAYSCALE );
//    //resize()函数对目标图像大小进行调整.
//    resize(img_object, img_object, Size(400,400));
//    //img_scene = imread( "test.jpg", IMREAD_GRAYSCALE );
//
//    if( !img_object.data)
//    { std::cout<< " --(!) Error reading image " << std::endl; return -1; }
//
//    //【1】使用SURF特征检测与描述.
//    //创建并初始化SURF特征检测对象detector.
//    Ptr<SURF> detector = SURF::create(MIN_HESSIAN, 4, 3);   //MIN_HESSIAN为最小的hessian矩阵的阈值，已定义为300.
//    //等价于Ptr<SURF> detector ;  detector = SURF::create(300, 5, 4);
//    //检测图像特征点并计算描述子，参数：目标图    输出Mat矩阵    特征点向量        描述子图像
//    detector->detectAndCompute( img_object, Mat(), keypoints_object, descriptors_object );
//
//    Mat H_latest = Mat::eye(3, 3, CV_32F); //指定大小和类型的单位矩阵H_latest，可对其进行缩放操作.
//    Mat scene_mask  = Mat::zeros(img_scene.rows, img_scene.cols, CV_8UC1);  //定义一个与场景图像大小一样的掩膜scene_mask.
//
//
//    while(1)
//    {
//        bool good_detection = false;
//
//        cap >> img_scene;
//        if(!img_scene.data)
//        { std::cout<< " --(!) Error reading camera " << std::endl; return -1; }
//
//        //初始化scene_mask
//        scene_mask = Mat::zeros(img_scene.rows, img_scene.cols, CV_8UC1);
//
//        //对场景图像进行surf检测，生成                        场景特征点    和     场景描述子
//        detector->detectAndCompute( img_scene, Mat(), keypoints_scene, descriptors_scene );
//
//        //【2】通过快速最近邻算法FLANN进行描述子向量匹配.
//        std::vector< DMatch > matches;      //定义匹配向量matches
//        matcher.match( descriptors_object, descriptors_scene, matches, 2);      //match()函数为描述符查找最佳的匹配
//
////        FlannBasedMatcher matcher;
////        vector< vector< DMatch > > matches;
////        //matcher.match(descriptors_object, descriptors_scene, matches);
////        matcher.knnMatch(descriptors_object, descriptors_scene, matches,2);
//
//        double max_dist = 0;
//        double min_dist = 100;
//        //-- 计算特征点之间的最大最小距离
//        for( int i = 0; i < descriptors_object.rows; i++ )
//        {
//            double dist = matches[i].distance;
//            if( dist < min_dist ) min_dist = dist;
//            if( dist > max_dist ) max_dist = dist;
//        }
//        printf("-- Max dist : %f \n", max_dist );
//        printf("-- Min dist : %f \n", min_dist );
//
//        //绘制出良好的匹配（距离小于三倍的最小距离）
//        std::vector< DMatch > good_matches;
//        for( int i = 0; i < descriptors_object.rows; i++ )
//        {
//            if( matches[i].distance < 3*min_dist )
//            {
//                good_matches.push_back( matches[i]);
//            }
//        }
//
//        //在目标图像上绘制特征点img_matches.
//        drawMatches( img_object, keypoints_object, img_scene, keypoints_scene,
//                     good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
//                     std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
//
//        if(img_matches.data) //check if there are any matches, if so then continue
//        {
//            // 获取两幅图像特征点信息
//            std::vector<Point2f> obj;
//            std::vector<Point2f> scene;
//            for( size_t i = 0; i < good_matches.size(); i++ )
//            {
//                //-- Get the keypoints from the good matches
//                //good_matches[i].queryIdx保存目标图像匹配点的序号
//                //good_matches[i].trainIdx保存相机获取图像的匹配点的序号
//                obj.push_back( keypoints_object[ good_matches[i].queryIdx ].pt );   //～.pt 为该序号对应的点的坐标，～.pt.x为该点的x坐标.
//                scene.push_back( keypoints_scene[ good_matches[i].trainIdx ].pt );  //
//            }
//
//            //Homography就是一个变换（3*3矩阵），将一张图中的点映射到另一张图中对应的点
//            Mat H = findHomography( obj, scene, RANSAC );
//            if (!H.data)
//            {
//                continue;
//            }
//
//            // 获取目标图像的四个角的坐标，存放在向量obj_corners中.
//            std::vector<Point2f> obj_corners(4);
//            obj_corners[0] = cvPoint(0, 0);
//            obj_corners[1] = cvPoint( img_object.cols, 0 );
//            obj_corners[2] = cvPoint( img_object.cols, img_object.rows );
//            obj_corners[3] = cvPoint( 0, img_object.rows );
//
//            std::vector<Point2f> scene_corners(4);
//            //scene_corners与输入obj_corners大小相同，H时3*3的浮点型变换矩阵.
//            perspectiveTransform( obj_corners, scene_corners, H);
//
//            // 检查转换矩阵，变换是否
//            float hDet = abs(determinant(H));       //determinant()返回矩阵H的行列式.
//            if (hDet < 100 && hDet > 0.05)
//            { // Good detection, reasonable transform
//                H_latest = H;
//                good_detection = true;
//            }
//
//            //-- Draw lines between the corners (the mapped object in the scene - image_2 )
//
//            std::vector<Point2f> match_corners(4);
//            match_corners[0] = scene_corners[0] + Point2f( img_object.cols, 0);
//            match_corners[1] = scene_corners[1] + Point2f( img_object.cols, 0);
//            match_corners[2] = scene_corners[1] + Point2f( img_object.cols, 0);
//            match_corners[3] = scene_corners[2] + Point2f( img_object.cols, 0);
//
//            //line( img_matches, scene_corners[0] + Point2f( img_object.cols, 0), scene_corners[1] + Point2f( img_object.cols, 0), Scalar(0, 255, 0), 4 );
//            line( img_matches, scene_corners[1] + Point2f( img_object.cols, 0), scene_corners[2] + Point2f( img_object.cols, 0), Scalar( 0, 255, 0), 4 );
//            line( img_matches, scene_corners[2] + Point2f( img_object.cols, 0), scene_corners[3] + Point2f( img_object.cols, 0), Scalar( 0, 255, 0), 4 );
//            line( img_matches, scene_corners[3] + Point2f( img_object.cols, 0), scene_corners[0] + Point2f( img_object.cols, 0), Scalar( 0, 255, 0), 4 );
//            //-- Show detected matches
//            //imshow( "SURF", img_matches );
//
//            Mat img_video;
//            vid >> img_video;
//
//
//            // Create the mask for the video in the scene veiw
//            std::vector<Point2f> vid_corners(4);
//            vid_corners[0] = cvPoint( 0, 0 );
//            vid_corners[1] = cvPoint( img_video.cols, 0 );
//            vid_corners[2] = cvPoint( img_video.cols, img_video.rows );
//            vid_corners[3] = cvPoint( 0, img_video.rows );
//
//            cv::Point nonfloat_corners[4];
//            for(int i=0; i<4; i++){
//                nonfloat_corners[i] = vid_corners[i];
//            }
//            fillConvexPoly(scene_mask, nonfloat_corners, 4, cv::Scalar(255));
//            warpPerspective( scene_mask, scene_mask, H_latest, Size(img_scene.cols,img_scene.rows));
//
//            //Apply transformation to video image and copy with mask
//            warpPerspective( img_video, img_video, H_latest, Size(img_scene.cols,img_scene.rows));
//
//            if(   good_detection )
//            {
//                img_video.copyTo(img_scene, scene_mask);
//            }
//
//            imshow( "Test", img_scene);
//
//            waitKey(1);
//        }
//    }
//    return 0;
//}