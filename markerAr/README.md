# WarpPerspective_MakerArDemo_wu
> A demo for Affine transformation and perspective transformation

![](https://github.com/wuxiaolang/WarpPerspective_MakerArDemo_wu/blob/master/pic/tf.gif?raw=true)   
<font face =宋体>
<font size =2>

# <center>机器人技术与应用作业选题一：编程实现透视变换</center>
    
<font size =4>**<center>工程代码：[https://github.com/wuxiaolang/WarpPerspective_MakerArDemo_wu](https://github.com/wuxiaolang/WarpPerspective_MakerArDemo_wu)</center>**</font>
     

<font size = 1>    



</font>

## 1. 原理介绍
### 1.1 透视变换
    
+ **概念**：    
透视变换是将图片投影到一个新的视平面，也称作投影映射．它是**二维（x,y）到三维(X,Y,Z)，再到另一个二维(x’,y’)空间的映射**     
    
+ **变换公式**：
<center>
    <img src="https://camo.githubusercontent.com/a7fc03be39168275e465f39384ff4b1b4512ffd3/68747470733a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f353335373839332d303965626339656139356332346334382e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f3239372f666f726d61742f77656270" width="200" >
</center>

+ **示意图**：
<center>
    <img src="https://camo.githubusercontent.com/8720129fa46059b9ba25970008db8e57a02cb17a/68747470733a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f353335373839332d333731633130303030386638613063662e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f3235392f666f726d61742f77656270">
</center>

### 1.2 仿射变换
+ **概念**：    
仿射变换是一种二维坐标到二维坐标之间的线性变换，它**保持了二维图形的“平直性”（直线经过变换之后依然是直线）和“平行性”（二维图形之间的相对位置关系保持不变，平行线依然是平行线，且直线上点的位置顺序不变）** 

+ 变换公式：
<center>
    <img src="https://camo.githubusercontent.com/7350259281319897d1ad42574316f64107831350/68747470733a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f353335373839332d343137313661326334316330643335352e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f3239362f666f726d61742f77656270">
</center>

+ **示意图**：
<center>
    <img src="https://camo.githubusercontent.com/028ab12eeba2bb0e9ccfd0ea49b65b362944d4e9/68747470733a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f353335373839332d373936656164393161626564303332632e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f3235392f666f726d61742f77656270">
</center>

---

## 2.编程
### 2.1 方法一：调用OpenCV透视变换函数  
调用 Opencv 的 `warpPerspective()` 函数实现

+  **`warpPerspective()` 的参数说明:**


```cpp
void warpPerspective
(InputArray src,                   /*输入图像*/
OutputArray dst,                   /*输出图像*/
InputArray M,                      /*3x3 变换矩阵*/
Size dsize,                        /*目标图像大小*/
int flags=INTER_LINEAR,            /*插值方法*/
int borderMode=BORDER_CONSTANT,    /*外推方法*/
const Scalar& borderValue=Scalar() /*常量边界时使用*/
)
```
    
+ **调用部分的代码**   
    + **完整代码**见工程中的 [**v3_warpPerspective.cpp**](https://github.com/wuxiaolang/WarpPerspective_MakerArDemo_wu/blob/master/v3_warpPerspective.cpp?1541162382516)
    
```cpp
//返回相应四对点的变换矩阵H.
Mat H = getPerspectiveTransform(square, marker_square);
//原图像通过透视变换之后得到marker.
warpPerspective(grayImage, marker,H, Size(marker_width,marker_width));
//对变换之后的图进行二值化.
threshold(marker, marker, 125, 255, THRESH_BINARY|THRESH_OTSU);
//查看透视变换的效果.
imshow("透视变换", marker);
```

### 2.2 方法二：自编写透视变换函数
+ **自定义透视变换函数 mywarpPerspective()**
    + 完整代码见工程中的 [**v5_myWarpPerspective.cpp**](https://github.com/wuxiaolang/WarpPerspective_MakerArDemo_wu/blob/master/v5_myWarpPerspective.cpp?1541162516954)

```cpp
void mywarpPerspective(Mat src,Mat &dst,Mat T,Size dsize)
{
   //此处注意计算模型的坐标系与Mat的不同
   //图像以左上点为（0,0），向左为x轴，向下为y轴，所以前期搜索到的特征点 存的格式是（图像x，图像y）---（rows，cols）
   //而Mat矩阵的是向下为x轴，向左为y轴，所以存的方向为（图像y，图像x）----（cols，rows）----（width，height）
   //这个是计算的时候容易弄混的

   //创建原图的四个顶点的3*4矩阵（此处我的顺序为左上，右上，左下，右下）
       Mat tmp(3, 4, CV_64FC1, 1);
       tmp.at < double >(0, 0) = 0;
       tmp.at < double >(1, 0) = 0;
       tmp.at < double >(0, 1) = src.cols;
       tmp.at < double >(1, 1) = 0;
       tmp.at < double >(0, 2) = 0;
       tmp.at < double >(1, 2) = src.rows;
       tmp.at < double >(0, 3) = src.cols;
       tmp.at < double >(1, 3) = src.rows;

   //获得原图四个顶点变换后的坐标，计算变换后的图像尺寸
       Mat corner = T * tmp;      //corner=(x,y)=(cols,rows)
       int width = 0, height = 0;
       double maxw = corner.at < double >(0, 0)/ corner.at < double >(2,0);
       double minw = corner.at < double >(0, 0)/ corner.at < double >(2,0);
       double maxh = corner.at < double >(1, 0)/ corner.at < double >(2,0);
       double minh = corner.at < double >(1, 0)/ corner.at < double >(2,0);

       for (int i = 1; i < 4; i++) {
           maxw = max(maxw, corner.at < double >(0, i)  /  corner.at < double >(2, i));
           minw  = min (minw,  corner.at < double >(0, i)  /  corner.at < double >(2, i));
           maxh  = max(maxh, corner.at < double >(1, i)  /  corner.at < double >(2, i));
           minh  = min (minh,   corner.at < double >(1, i)  /  corner.at < double >(2, i));
       }

   //创建向前映射矩阵 map_x, map_y
         //size(height,width)
       dst.create(int(maxh - minh), int(maxw - minw), src.type());
       Mat map_x(dst.size(), CV_32FC1);
       Mat map_y(dst.size(), CV_32FC1);

       Mat proj(3,1, CV_32FC1,1);

       Mat point(3,1, CV_32FC1,1);

      T.convertTo(T, CV_32FC1);
   //本句是为了令T与point同类型（同类型才可以相乘，否则报错，也可以使用T.convertTo(T, point.type() );）
   Mat Tinv=T.inv();

       for (int i = 0; i < dst.rows; i++) 
	 {
           for (int j = 0; j < dst.cols; j++) 
	     {
               point.at<float>(0) = j + minw ;
               point.at<float>(1) = i + minh ;
               proj = Tinv * point;
		   //NOTE dst(x,y) = src((M11x+M12y+M13)/(M31x+M32y+M33), (M21x+M22y+M23)/(M31x+M32y+M33))
               map_x.at<float>(i, j) = proj.at<float>(0)/ proj.at<float>(2) ;
               map_y.at<float>(i, j) = proj.at<float>(1) / proj.at<float>(2) ;
           }
       }
       remap(src,dst,map_x,map_y, CV_INTER_LINEAR);
}
```
---

## 3.实验
    
<font color = red>**实验目的**：    
相机从各个角度拍摄**正方形会出现变形**，通过**透视变换**将其转换成**仍然是正方形显示**。</font>

### 3.1 图像处理
分别进行**灰度化 ——> 滤波 ——> 二值化**       
> **对应文件：**[**v1_process.cpp**](https://github.com/wuxiaolang/WarpPerspective_MakerArDemo_wu/blob/master/v1_process.cpp)
    
<center>
    <img src="https://github.com/wuxiaolang/WarpPerspective_MakerArDemo_wu/blob/master/pic/001.png?raw=tru" width="700" />
</center>

### 3.2 提取轮廓
提取相机中物体的**轮廓**，并**绘制正方形的四个点**
> **对应文件：**[**v2_outline.cpp**](https://github.com/wuxiaolang/WarpPerspective_MakerArDemo_wu/blob/master/v2_outline.cpp)

<center>
    <img src="https://github.com/wuxiaolang/WarpPerspective_MakerArDemo_wu/blob/master/pic/002.png?raw=tru">
</center>


### 3.3 用 OpenCV 函数实现透视变换
调用 **OpenCV 自带的 warpPerspective() 函数实现透视变换**
> **对应文件：**[**v3_warpPerspective.cpp**](https://github.com/wuxiaolang/WarpPerspective_MakerArDemo_wu/blob/master/v3_warpPerspective.cpp)
    
<center>
    <img src="https://github.com/wuxiaolang/WarpPerspective_MakerArDemo_wu/blob/master/pic/003.png?raw=tru">
</center>


### 3.3 在四边形上叠加空间坐标系

三维到二维空间转换,**3D——2D投影,坐标轴绘制**
> **对应文件：**[**v4_coordinate.cpp**](https://github.com/wuxiaolang/WarpPerspective_MakerArDemo_wu/blob/master/v4_coordinate.cpp?1541164206796)
    
<center>
    <img src="https://github.com/wuxiaolang/WarpPerspective_MakerArDemo_wu/blob/master/pic/004.png?raw=tru">
</center>


### 3.4 自编写放射变换函数实现
利用**自己编写的放射变换函数 mywarpPerspective()** 实现放射变换

> **对应文件：**[**v5_myWarpPerspective.cpp**](https://github.com/wuxiaolang/WarpPerspective_MakerArDemo_wu/blob/master/v5_myWarpPerspective.cpp?15411642480536)
    
<center>
    <img src="https://github.com/wuxiaolang/WarpPerspective_MakerArDemo_wu/blob/master/pic/005.png?raw=tru">
</center>
    
---
2018.10.12    
wuyanminmax@gmail.com
