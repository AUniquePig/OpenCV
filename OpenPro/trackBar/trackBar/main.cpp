//---------------------------------------------------------- 第 3 章 图形用户界面 -----------------------------------------------------------
//滑动条----这个程序的问题是滑动条上的值不能动态改变
/*
 #include <opencv2/opencv.hpp>
 #include <opencv2/highgui/highgui.hpp>
 #include <iostream>
 
 
 using namespace cv;
 
 #define WINDOW_NAME "LineWindows"
 const int g_nMaxAlphaValue = 100;
 int g_nAlphaValueSlider=70;
 double g_dAlphaValue;
 double g_dBetaValue;
 
 
 Mat g_srcImage1;
 Mat g_srcImage2;
 Mat g_dstImage;
 
 void on_Trackbar(int,void*) //响应滑动条的回调函数
 {
 g_dAlphaValue = (double) g_nAlphaValueSlider/g_nMaxAlphaValue;
 g_dBetaValue = (1.0 - g_dAlphaValue);
 addWeighted(g_srcImage1,g_dAlphaValue, g_srcImage2, g_dBetaValue, 0.0, g_dstImage);
 
 //    printf("当前轨迹条的值： %d\n",g_nAlphaValueSlider);
 imshow(WINDOW_NAME, g_dstImage);
 }
 
 
 int main(int argc, const char * argv[]) {
 
 g_srcImage1 = imread("/Users/lichunxia/Desktop/opencvPic/picture1.jpg");
 g_srcImage2 = imread("/Users/lichunxia/Desktop/opencvPic/picture2.jpg");
 
 if(!g_srcImage1.data ){
 printf("读取第一张图片错误，请确定目录下是否有图片存在！");
 return -1;
 }
 if(!g_srcImage2.data ){
 printf("读取第二张图片错误，请确定目录下是否有图片存在！");
 return -1;
 }
 g_nAlphaValueSlider = 70;
 namedWindow(WINDOW_NAME,2);
 
 char TrackbarName[50];
 sprintf(TrackbarName,"T %d:%d ",g_nAlphaValueSlider,g_nMaxAlphaValue);
 createTrackbar(TrackbarName, WINDOW_NAME, &g_nAlphaValueSlider, g_nMaxAlphaValue,on_Trackbar);
 g_nAlphaValueSlider = getTrackbarPos(TrackbarName, WINDOW_NAME);
 
 on_Trackbar(g_nAlphaValueSlider, 0);
 waitKey(0);
 return 0;
 }
 */
//鼠标操作绘制矩形
/*
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>  //这句话在书中没有，我敲的时候也没在意，但是无法运行，小伙伴千万不要忘记

using namespace cv;

#define WINDOW_NAME "mouseOperate"

//全局函数声明部分
void on_MouseHandle(int event,int x,int y,int flags,void* param);
void DrawRectangle(Mat& img,Rect box);
void ShowHelpText(); //觉得这个函数没有用

//全局变量声明部分

Rect g_rectangle;
bool g_bDrawingBox = false;
RNG g_rng(12345);//随机数产生器


int main(int argc,char** argv)
{
    //【1】准备参数
    g_rectangle = Rect(-1,-1,0,0); //这四个参数的分别代表矩形的左上X，Y坐标和宽度，高度，不要弄混了
    Mat srcImage(300,400,CV_8UC3),tempImage;//窗口的size，CV_8UC3的含义，这个网站介绍的很详细 http://blog.csdn.net/maweifei/article/details/51221259
    srcImage.copyTo(tempImage);
    srcImage = Scalar::all(0);
    //【2】设置鼠标操作回调函数
    namedWindow(WINDOW_NAME);
    setMouseCallback(WINDOW_NAME, on_MouseHandle,(void*)&srcImage);
    //【3】程序主循环
    while(1)
    {
        srcImage.copyTo(tempImage);
        if(g_bDrawingBox)
            DrawRectangle(tempImage, g_rectangle);
        imshow(WINDOW_NAME, tempImage);
        if(waitKey(10) == 27)
            break;
    }
    return 0;
}
//鼠标回调函数
void on_MouseHandle(int event,int x,int y,int flags,void* param)
{
    Mat& image = *(Mat*)param;
    switch (event) {
        case EVENT_MOUSEMOVE:
        {
            if(g_bDrawingBox)
            {
                g_rectangle.width = x-g_rectangle.x;
//                printf("矩形宽：%d\n",g_rectangle.width);
                g_rectangle.height = y-g_rectangle.y;
//                printf("矩形高：%d\n",g_rectangle.height);   //小伙伴可以测一下 X，Y的值随鼠标的移动发生变化
            }
        }
            break;
        case EVENT_LBUTTONDOWN:
        {
            g_bDrawingBox = true;
            g_rectangle = Rect(x,y,0,0);
        }
            break;
        case EVENT_LBUTTONUP:
        {
            g_bDrawingBox = false;
            if(g_rectangle.width < 0)
            {
                g_rectangle.x += g_rectangle.width;
                g_rectangle.width *= -1;
            }
            if(g_rectangle.height < 0)
            {
                g_rectangle.y += g_rectangle.height;
                g_rectangle.height *= -1;
            }
            DrawRectangle(image, g_rectangle);
        }
            break;
    }
}

//矩形绘制函数
void DrawRectangle(Mat& img,Rect box)
{
    rectangle(img,box.tl(),box.br(),Scalar(g_rng.uniform(0,255),g_rng.uniform(0, 255),g_rng.uniform(0,255)));
}
*/
//------------------------------------------------------------第4章 OpenCV 数据结构与基本绘图------------------------------------------------------
//基础操作
/*基础操作
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc,char** argv)
{
    //【1】使用Mat（）构造函数
    Mat M(2,2,CV_8UC3,Scalar(0,0,255));
    cout<< "M = " << endl <<" "<< M <<endl<<endl;
    cout<<"------------------------------------"<<endl<<endl;
    //【2】输出风格
    Mat r = Mat(3,3,CV_8UC3);
    randu(r, Scalar::all(0), Scalar::all(255));
    cout<<"r = "<<endl<<" "<< r <<endl<<endl;
    cout<<"------------------------------------"<<endl<<endl;
    //【3】定义和输出二维点
    Point2f p(6,2);
    cout<<"二维点 p = "<< p << ";\n" <<endl;
    //【4】定义和输出三维点
    Point3f p3f(1,2,3);
    cout<<" 三维点 p3f = " << p3f << ";\n" <<endl;
    //【5】基于Mat的std::vector
    vector<float> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    cout<<"基于Mat的vector shortvec = " << Mat(v) << ";\n"<<endl;
    //【6】std::vector
    vector<Point2f> points(10);
    for(size_t i = 0; i < points.size(); ++i)
        points[i] = Point2f((float)(i*5),(float)(i%7));
    cout<<"二维向量点 points = "<<endl<<" "<< points<<endl;
    //【7】颜色空间转换
    Mat srcImage = imread("/Users/lichunxia/Desktop/opencvPic/picture1.jpg",1),dstImage;
    cvtColor(srcImage, dstImage, CV_RGB2GRAY);
    imshow("yansezhuanhuan", dstImage);
    waitKey();
    
    return 0 ;
}
*/
//基本绘图操作
/*基本图形的绘制
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;

#define  WINDOW_NAME1 "picture1"
#define  WINDOW_NAME2 "picture2"
#define WINDOW_WIDTH 600

void DrawEllipse(Mat img, double angle );
void DrawFilledCircle(Mat img ,Point center);
void DrawPolygon(Mat img);
void DrawLine(Mat img, Point start, Point end);

int main( void )
{
    Mat atomImage = Mat::zeros(WINDOW_WIDTH,WINDOW_WIDTH,CV_8UC3);
    Mat rootImage = Mat::zeros(WINDOW_WIDTH,WINDOW_WIDTH,CV_8UC3);
    
    //【1.1】先绘制出椭圆
    DrawEllipse(atomImage, 90);
    DrawEllipse(atomImage, 0);
    DrawEllipse(atomImage, 45);
    DrawEllipse(atomImage, -45);
    
    //【1.2】再绘制圆心
    DrawFilledCircle(atomImage, Point(WINDOW_WIDTH/2,WINDOW_WIDTH/2));
    
    //【2.1】先绘制出多边形
    DrawPolygon(rootImage);
    
    //【2.2】绘制矩形
    rectangle(rootImage, Point(0,7*WINDOW_WIDTH/8), Point(WINDOW_WIDTH,WINDOW_WIDTH), Scalar(0,255,255),-1,8);
    
    //【2.3】绘制一些线段
    DrawLine(rootImage, Point(0,15*WINDOW_WIDTH/16), Point(WINDOW_WIDTH,15*WINDOW_WIDTH/16));
    DrawLine(rootImage, Point(WINDOW_WIDTH/4,7*WINDOW_WIDTH/8), Point(WINDOW_WIDTH/4,WINDOW_WIDTH));
    DrawLine(rootImage, Point(WINDOW_WIDTH/2,7*WINDOW_WIDTH/8), Point(WINDOW_WIDTH/2,WINDOW_WIDTH));
    DrawLine(rootImage, Point(3*WINDOW_WIDTH/4,7*WINDOW_WIDTH/8), Point(3*WINDOW_WIDTH/4,WINDOW_WIDTH));
    
    imshow(WINDOW_NAME1, atomImage);
    moveWindow(WINDOW_NAME1, 10, 100);
    imshow(WINDOW_NAME2, rootImage);
    moveWindow(WINDOW_NAME2, WINDOW_WIDTH+20, 100);
    
    waitKey(0);
    return 0;
}
//画椭圆
void DrawEllipse(Mat img, double angle)
{
    int thickness = 2;
    int lineType = 8;
    
    ellipse(img, Point(WINDOW_WIDTH/2,WINDOW_WIDTH/2),Size(WINDOW_WIDTH/2,WINDOW_WIDTH/16), angle, 0, 360, Scalar(255,129,0),thickness,lineType);
}
//画实心圆
void DrawFilledCircle(Mat img, Point center)
{
    int thickness = -1;
    int lineType = 8;
    
    circle(img, center,WINDOW_WIDTH/32, Scalar(0,0,255),thickness,lineType);
}
// 画凹多边形
void DrawPolygon(Mat img)
{
    int lineType = 8;
    Point rootPoints[1][20];
   
    rootPoints[0][0] = Point(WINDOW_WIDTH/4, 7*WINDOW_WIDTH/8);
    rootPoints[0][1] = Point(3*WINDOW_WIDTH/4, 7*WINDOW_WIDTH/8);
    rootPoints[0][2] = Point(3*WINDOW_WIDTH/4, 13*WINDOW_WIDTH/16);
    rootPoints[0][3] = Point(11*WINDOW_WIDTH/16, 13*WINDOW_WIDTH/16);
    rootPoints[0][4] = Point(19*WINDOW_WIDTH/32, 3*WINDOW_WIDTH/8);
    rootPoints[0][5] = Point(3*WINDOW_WIDTH/4, 3*WINDOW_WIDTH/8);
    rootPoints[0][6] = Point(3*WINDOW_WIDTH/4, WINDOW_WIDTH/8);
    rootPoints[0][7] = Point(26*WINDOW_WIDTH/40, WINDOW_WIDTH/8);
    rootPoints[0][8] = Point(26*WINDOW_WIDTH/40, WINDOW_WIDTH/4);
    rootPoints[0][9] = Point(22*WINDOW_WIDTH/40, WINDOW_WIDTH/4);
    rootPoints[0][10] = Point(22*WINDOW_WIDTH/40, WINDOW_WIDTH/4);
    rootPoints[0][11] = Point(18*WINDOW_WIDTH/40, WINDOW_WIDTH/8);
    rootPoints[0][12] = Point(18*WINDOW_WIDTH/40, WINDOW_WIDTH/4);
    rootPoints[0][13] = Point(14*WINDOW_WIDTH/40, WINDOW_WIDTH/4);
    rootPoints[0][14] = Point(14*WINDOW_WIDTH/40, WINDOW_WIDTH/8);
    rootPoints[0][15] = Point(WINDOW_WIDTH/4, WINDOW_WIDTH/8);
    rootPoints[0][16] = Point(WINDOW_WIDTH/4, 3*WINDOW_WIDTH/8);
    rootPoints[0][17] = Point(13*WINDOW_WIDTH/32, 3*WINDOW_WIDTH/8);
    rootPoints[0][18] = Point(5*WINDOW_WIDTH/16, 3*WINDOW_WIDTH/8);
    rootPoints[0][19] = Point(WINDOW_WIDTH/4, 13*WINDOW_WIDTH/16);

    const Point* ppt[] = {rootPoints[0]};
    
    int npt[] = { 20 };
    
    
    fillPoly(img, ppt, npt, 1, Scalar(255,255,255),lineType);
}
//画线
void DrawLine(Mat img,Point start,Point end)
{
    int thickness = 2;
    int lineType = 8;
    line(img,start,end,Scalar(0,0,0),thickness,lineType);
}
*/
//----------------------------------------------------------第5章 core 组件进阶 --------------------------------------------------------------------
//访问像素的三种方法
/*访问像素的三种方法
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>



using namespace std;
using namespace cv;

//三种操作像素的方法
void colorReduce1(Mat inputImage, Mat& outputImage,int div);
void colorReduce2(Mat inputImage, Mat& outputImage,int div);
void colorReduce3(Mat inputImage, Mat& outputImage,int div);


int main(int argc, char** argv)
{
    Mat srcImage = imread("/Users/lichunxia/Desktop/opencvPic/picture1.jpg");
    imshow("original",srcImage);
    moveWindow("original", 0, 100);
    
    Mat dstImage1,dstImage2,dstImage3;
    dstImage1.create(srcImage.rows, srcImage.cols, srcImage.type());
    dstImage2.create(srcImage.rows, srcImage.cols, srcImage.type());
    dstImage3.create(srcImage.rows, srcImage.cols, srcImage.type());
    // 记录起始时间
    double time0 = static_cast<double>(getTickCount());
    //指针访问像素
    colorReduce1(srcImage, dstImage1, 32);
    colorReduce2(srcImage, dstImage2, 32);
    colorReduce3(srcImage, dstImage3, 32);
    
    time0 = ((double)getTickCount() - time0) / getTickCount();
    
    cout<<" 此方法运行时间为 " << time0 <<" 秒 " <<endl;
    
    imshow("processing1", dstImage1);
    moveWindow("processing1",250, 100);
    imshow("processing2", dstImage2);
    moveWindow("processing2",500, 100);
    imshow("processing3", dstImage3);
    moveWindow("processing3",750, 100);
    
    waitKey(0);
    return 0;
    
}
//指针访问像素
void colorReduce1(Mat inputImage, Mat& outputImage,int div)
{
    //参数准备
    outputImage = inputImage.clone();
    int rowNumber = outputImage.rows;
    int colNumber = outputImage.cols * outputImage.channels();//每一行的元素个数
    
    for(int i = 0; i < rowNumber; i++)
    {
        uchar* data = outputImage.ptr<uchar>(i);   //Mat最直接的访问方法是通过.ptr<>函数得到一行的指针，并用[]操作符访问某一列的像素值。
        for(int j = 0; j < colNumber; j++)
        {
            data[j] = data[j] / div * div + div / 2 ;
        }
    }
    
    
    
    
    
    
    
    
    
}
//迭代器操作像素
void colorReduce2(Mat inputImage, Mat& outputImage,int div)
{
    outputImage = inputImage.clone();
    //获取迭代器
    Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>(); //初始位置的迭代器
    Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>();//终止位置的迭代器
    
    for(;it != itend; ++it)
    {
        (*it)[0] = (*it)[0] / div * div + div / 2 ;
        (*it)[1] = (*it)[1] / div * div + div / 2 ;
        (*it)[2] = (*it)[2] / div * div + div / 2 ;
    }
    
    
    
    
    
}
// 动态地址计算
void colorReduce3(Mat inputImage, Mat& outputImage,int div)
{
    outputImage = inputImage.clone();
    int rowNumber = outputImage.rows;
    int colNumber = outputImage.cols;
    
    for(int i = 0;i < rowNumber; i++)
    {
        for(int j = 0;j < colNumber; j++)
        {
            outputImage.at<Vec3b>(i,j)[0] = outputImage.at<Vec3b>(i,j)[0] / div * div + div / 2 ;
            outputImage.at<Vec3b>(i,j)[1] = outputImage.at<Vec3b>(i,j)[1] / div * div + div / 2 ;
            outputImage.at<Vec3b>(i,j)[2] = outputImage.at<Vec3b>(i,j)[2] / div * div + div / 2 ;
        }
    }
}
*/
//ROI区域图像叠加&图像混合
/*
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

bool ROI_AddImage();
bool LinearBlending();
bool ROI_LinearBlending();

int main(int argc, char** argv)
{
    if(ROI_AddImage()&&LinearBlending()&&ROI_LinearBlending())
    {
        cout<< endl << "运行成功，得出了你需要的图像～～" <<endl;
    }
    waitKey(0);
    return 0;
}
//------------------------------------【ROI_AddImage()函数】---------------------------------
bool ROI_AddImage()
{
    //【1】读入图像
    Mat srcImage1 = imread("/Users/lichunxia/Desktop/opencvPic/dota_pa.jpg");
    Mat logoImage = imread("/Users/lichunxia/Desktop/opencvPic/dota_logo.jpg");
    
    if(!srcImage1.data)
    {
        printf("读取srcImage1错误～～ \n");
        return false;
    }
    if(!logoImage.data)
    {
        printf("读取logoImage错误～～ \n");
        return false;
    }
    //【2】定义一个Mat类型并给其设定ROI区域
    Mat imageROI = srcImage1(Rect(200,250,logoImage.cols,logoImage.rows));
    //【3】加载掩膜
    Mat mask = imread("/Users/lichunxia/Desktop/opencvPic/dota_logo.jpg");
    //【4】将掩膜复制到ROI
    logoImage.copyTo(imageROI, mask);
    //【5】显示结果
    namedWindow("<1>ROI_AddImage---example");
    imshow("<1>ROI_AddImage---example", srcImage1);
    return true;
}
//------------------------------------【LinearBlending()函数】---------------------------------
bool LinearBlending()
{
    //【0】定义一些局部变量
    double alphaValue = 0.3 ;
    double betaValue ;
    Mat srcImage2,srcImage3,dstImage;
    
    //【1】读取图像（两幅图需要同样的类型和尺寸）
    srcImage2 = imread("/Users/lichunxia/Desktop/opencvPic/mogu.jpg");
    srcImage3 = imread("/Users/lichunxia/Desktop/opencvPic/rain.jpg");
    
    if(!srcImage2.data)
    {
        printf(" 读取srcImage2错误～～～ \n");
        return false;
    }
    if(!srcImage3.data)
    {
        printf(" 读取srcImage3错误～～～ \n");
        return false;
    }
    
    //【2】进行图像混合加权操作
    betaValue = 1.0 - alphaValue ;
    addWeighted(srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);
    
    //【3】创建并显示原图窗口
    namedWindow("<2>LinearBlending--example<2-1>",1);
    imshow("<2>LinearBlending--example<2-1>", srcImage2);
    
    namedWindow("<2>LinearBlending--example<2-2>",1);
    imshow("<2>LinearBlending--example<2-2>", dstImage);
    
    return true;
}
//------------------------------------【ROI_LinearBlending()函数】---------------------------------
bool ROI_LinearBlending()
{
    //【1】读取图像
    Mat srcImage4 = imread("/Users/lichunxia/Desktop/opencvPic/dota_pa.jpg",1);
    Mat logoImage = imread("/Users/lichunxia/Desktop/opencvPic/dota_logo.jpg");
    
    if(!srcImage4.data)
    {
        printf("读取srcImage4图片错误～～～ \n");
        return false;
    }
    if(!logoImage.data)
    {
        printf("读取logoImage图片错误～～～ \n");
        return false;
    }
    
    //【2】定义一个Mat类型并设定ROI区域
    Mat imageROI = srcImage4(Rect(200,250,logoImage.cols,logoImage.rows));
    
    //【3】将logo加到原图上
    addWeighted(imageROI, 0.5, logoImage, 0.3, 0.0, imageROI);
    
    //【4】显示结果
    namedWindow("<3>ROI_LinearBlending--example");
    imshow("<3>ROI_LinearBlending--example", srcImage4);
    return true;
}
*/
//多通道图像混合
/*
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>

using namespace std;
using namespace cv;

bool MultiChannelBlending();

int main(int argc,char** argv)
{
    
    if(MultiChannelBlending())
    {
        cout<<"\n 运行成功，得出了需要的图像～～\n"<<endl;
    }
    waitKey(0);
    return 0;
}



bool MultiChannelBlending()
{
    //【0】定义相关变量
    Mat srcImage;
    Mat logoImage;
    vector<Mat> channels;
    Mat imageBlueChannel;
    
    //----------------------【蓝色通道部分】-----------------------------------
    //【1】读入图片
    srcImage = imread("/Users/lichunxia/Desktop/opencvPic/dota_jugg.jpg");
    logoImage = imread("/Users/lichunxia/Desktop/opencvPic/dota_logo.jpg",0);//切记一定要是读入灰度图像，要不然～～～～
    
    if(!srcImage.data)
    {
        cout<<"srcImage错误～～～\n"<<endl;
        return false;
    }
    if(!logoImage.data)
    {
        cout<<"logoImage错误～～～\n"<<endl;
        return false;
    }
    
    //【2】把一个三通道图像转换成3个单通道图像
    split(srcImage, channels);
    
    //【3】将原图的蓝色通道引用返回给imageBlueChannel
    imageBlueChannel = channels.at(0);
    
    //【4】线性混合操作
    addWeighted(imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows)),1.0,logoImage, 0.5, 0, imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));
    
    //【5】三个单通道重新合并成一个三通道
    merge(channels, srcImage);//因为返回的事引用，所以此时channel的蓝色通道值也变了
    
    //【6】显示效果
    namedWindow("<1>original + logo blue");
    imshow("<1>original + logo blue", srcImage);
    
    //----------------------【绿色通道部分】-----------------------------------
    Mat imageGreenChannel;
    //【1】读入图片
    srcImage = imread("/Users/lichunxia/Desktop/opencvPic/dota_jugg.jpg");
    logoImage = imread("/Users/lichunxia/Desktop/opencvPic/dota_logo.jpg",0);//切记一定要是读入灰度图像，要不然～～～～
    
    if(!srcImage.data)
    {
        cout<<"srcImage错误～～～\n"<<endl;
        return false;
    }
    if(!logoImage.data)
    {
        cout<<"logoImage错误～～～\n"<<endl;
        return false;
    }
    
    //【2】把一个三通道图像转换成3个单通道图像
    split(srcImage, channels);
    
    //【3】将原图的蓝色通道引用返回给imageBlueChannel
    imageGreenChannel = channels.at(1);
    
    //【4】线性混合操作
    addWeighted(imageGreenChannel(Rect(500, 250, logoImage.cols, logoImage.rows)),1.0,logoImage, 0.5, 0, imageGreenChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));
    
    //【5】三个单通道重新合并成一个三通道
    merge(channels, srcImage);//因为返回的事引用，所以此时channel的蓝色通道值也变了
    
    //【6】显示效果
    namedWindow("<2>original + logo green");
    imshow("<2>original + logo green", srcImage);
    
    //----------------------【红色通道部分】-----------------------------------
    Mat imageRedChannel;
    //【1】读入图片
    srcImage = imread("/Users/lichunxia/Desktop/opencvPic/dota_jugg.jpg");
    logoImage = imread("/Users/lichunxia/Desktop/opencvPic/dota_logo.jpg",0);//切记一定要是读入灰度图像，要不然～～～～
    
    if(!srcImage.data)
    {
        cout<<"srcImage错误～～～\n"<<endl;
        return false;
    }
    if(!logoImage.data)
    {
        cout<<"logoImage错误～～～\n"<<endl;
        return false;
    }
    
    //【2】把一个三通道图像转换成3个单通道图像
    split(srcImage, channels);
    
    //【3】将原图的蓝色通道引用返回给imageBlueChannel
    imageRedChannel = channels.at(2);
    
    //【4】线性混合操作
    addWeighted(imageRedChannel(Rect(500, 250, logoImage.cols, logoImage.rows)),1.0,logoImage, 0.5, 0, imageRedChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));
    
    //【5】三个单通道重新合并成一个三通道
    merge(channels, srcImage);//因为返回的事引用，所以此时channel的蓝色通道值也变了
    
    //【6】显示效果
    namedWindow("<3>original + logo red");
    imshow("<3>original + logo red", srcImage);
    return true;
}
*/
//图像的对比度、亮度值调整
/*
#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

static void on_ContrastAndBright(int, void *);
void pointOperators(Mat inputImage, Mat& outputImage);

int g_nContrastValue ;
int g_nBrightValue ;
Mat g_srcImage, g_dstImage;

int main(int argc,char** argv)
{
    //【1】读入图像
    g_srcImage = imread("/Users/lichunxia/Desktop/opencvPic/1.jpg");
    if(!g_srcImage.data)
    {
        printf("error!");
        return false;
    }
   // g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());
    
    //【2】设定对比度和亮度的初值
    g_nContrastValue = 70;
    g_nBrightValue = 80;
    
    //【3】创建效果窗口图
    namedWindow("window1",1);
    
    //【4】创建轨迹条
    char TrackbarName1[50];
    sprintf(TrackbarName1,"contrast %d ",g_nContrastValue);
    char TrackbarName2[50];
    sprintf(TrackbarName2,"bright %d ",g_nBrightValue);
    
    createTrackbar(TrackbarName1, "window1", &g_nContrastValue, 300,on_ContrastAndBright );
    createTrackbar(TrackbarName2, "window1", &g_nBrightValue, 200,on_ContrastAndBright );
    
    //【5】进行回调函数初始化
    on_ContrastAndBright(g_nContrastValue, 0);
    on_ContrastAndBright(g_nBrightValue, 0);
    
    //【6】按下“q”键时，程序退出
    while (char(waitKey(1))!= 'q'){}
    return 0;
}

static void on_ContrastAndBright(int, void *)
{
    namedWindow("window2",1);
    //【1】访问像素
//    for(int y = 0; y<g_srcImage.rows; y++)
//    {
//        for(int x = 0; x<g_srcImage.cols; x++)
//        {
//            for(int c = 0; c < 3; c++)
//            {
//                g_dstImage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((g_nContrastValue*0.01)*(g_srcImage.at<Vec3b>(y, x)[c]) + g_nBrightValue);
//            }
//        }
//    }
    //【2】访问像素
    pointOperators(g_srcImage, g_dstImage);
    imshow("window2", g_srcImage);
    imshow("window1", g_dstImage);
}
// 动态地址计算
void pointOperators(Mat inputImage, Mat& outputImage)
{
    outputImage = inputImage.clone();
    int rowNumber = outputImage.rows;
    int colNumber = outputImage.cols;
    
    for(int i = 0;i < rowNumber; i++)
    {
        for(int j = 0;j < colNumber; j++)
        {
            
            outputImage.at<Vec3b>(i,j)[0] = saturate_cast<uchar>((g_nContrastValue*0.01)*(outputImage.at<Vec3b>(i, j)[0]) + g_nBrightValue);
            outputImage.at<Vec3b>(i,j)[1] = saturate_cast<uchar>((g_nContrastValue*0.01)*(outputImage.at<Vec3b>(i, j)[1]) + g_nBrightValue);
            outputImage.at<Vec3b>(i,j)[2] = saturate_cast<uchar>((g_nContrastValue*0.01)*(outputImage.at<Vec3b>(i, j)[2]) + g_nBrightValue);
        }
    }
}
*/
//离散傅立叶变换
/*
#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc,char** argv)
{
    //【1】读入图像并显示
    
    Mat srcImage = imread("/Users/lichunxia/Desktop/opencvPic/rou.jpg",0);//灰度模式
    if(!srcImage.data)
    {
        printf("error\n");
        return false;
    }
    imshow("window-1", srcImage);
    
    //【2】将图像扩大到适合的尺寸
    int m = getOptimalDFTSize(srcImage.rows);
    int n = getOptimalDFTSize(srcImage.cols);
    Mat padded;
    copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, n - srcImage.cols, BORDER_CONSTANT,Scalar::all(0));
    
    //【3】为傅立叶变换的结果（实部和虚部）分配存储空间
    Mat planes [] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexSrcImage;
    merge(planes, 2, complexSrcImage);
    
    //【4】进行离散傅立叶变换
    dft(complexSrcImage, complexSrcImage);
    
    //【5】将复数转换为幅值
    split(complexSrcImage, planes);
    magnitude(planes[0], planes[1], planes[0]);
    Mat magnitudeImage = planes[0];
    
    //【6】进行尺度对比
    magnitudeImage += Scalar::all(1);
    log(magnitudeImage, magnitudeImage);
    
    //【7】剪切和重分布幅度图象限
    magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2));
    
    int cx = magnitudeImage.cols / 2;
    int cy = magnitudeImage.rows / 2;
    Mat q0(magnitudeImage, Rect(0, 0, cx, cy));
    Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));
    Mat q2(magnitudeImage, Rect(0, cy, cx, cy));
    Mat q3(magnitudeImage, Rect(cx, cy, cx, cy));
    
    Mat temp;
    q0.copyTo(temp);
    q3.copyTo(q0);
    temp.copyTo(q3);
    
    q1.copyTo(temp);
    q2.copyTo(q1);
    temp.copyTo(q2);
    
    //【8】归一化
    normalize(magnitudeImage, magnitudeImage, 0, 1,CV_MINMAX);
    
    //【9】显示效果图
    imshow("window-2", magnitudeImage);

    waitKey();
    return 0;
}
*/
//输入输出XML和YAML文件
/*
#include<opencv2/opencv.hpp>
#include<iostream>
#include<time.h>

using namespace std;
using namespace cv;

bool writeFile();
bool readFile();

int main(int argc, char** argv)
{
//    writeFile(); //写文件
    readFile(); //读文件

    return 0;
    
}


bool writeFile()
{
    // 初始化
    FileStorage fs("/Users/lichunxia/Desktop/opencvPic/test.yaml", FileStorage::WRITE);
    
    //开始文件写入
    fs << "frameCount" << 5 ;
    time_t rawtime;
    time(&rawtime);
    fs << "calibrationDate" << asctime(localtime(&rawtime));
    
    Mat cameraMatrix = (Mat_<double>(3, 3) << 100, 0, 320, 0, 10000, 240, 0, 0, 1);
    fs << "cameraMatrix" << cameraMatrix ;
    
    fs << "features " << "[" ;
    for(int i = 0; i < 3; i++)
    {
        int x = rand() % 640 ;
        int y = rand() % 840 ;
        uchar lbp = rand() % 256;
        
        fs << "{:" << "x" << x << "y" << y << "lbp" << "[:" ;
        for(int j = 0; j < 8; j++)
        {
            fs << ((lbp >> j) & 1);
        }
        fs << "]" << "}" ;
    }
    //    fs << "]" ;
    //    fs <<"fhfhh"<< "[:" <<2 <<"]";
    //    fs << "strings" << "[" ;
    //    fs << "/Users/lichunxia/Desktop/opencvPic/1.jpg" << "ewe" << "/Users/lichunxia/Desktop/opencvPic/rou.jpg" ;
    //    fs << "]";
    fs.release();
    printf("文件写完毕");
    getchar();
    return true;
}

bool readFile()
{
    //初始化
    FileStorage fs("/Users/lichunxia/Desktop/opencvPic/test1.yaml",FileStorage::READ);
    
    //对FileNode操作
    int frameCount = (int)fs["frameCount"];
    
    std::string date;
    
    //使用FileNode运算符
    fs["calibrationDate"] >> date;
    
    Mat cameraMatrix2;
    fs["cameraMatrix"] >> cameraMatrix2;
    
    cout<< "frameCount: " << frameCount <<endl
        << "calibration date: " << date <<endl
        << "camera matrix: " << cameraMatrix2 <<endl;
    
    FileNode features = fs["features"];
    FileNodeIterator it = features.begin(), it_end = features.end();
    int idx = 0;
    std::vector<uchar> lbpval;
    for( ; it != it_end; ++it, idx++)
    {
        cout << "features #" << idx << ": " ;
        cout << "x= " << (int)(*it)["x"] << ", y= " << (int)(*it)["y"] << ", lbp: ( " ;
        (*it)["lbp"] >> lbpval;
        for(int i = 0; i < (int)lbpval.size(); i++)
            cout << " " << (int)lbpval[i];
        cout << " )" << endl;
    }
    fs.release();
    printf("\n 文件读完毕");
    getchar();
    return true;
}
*/
//------------------------------------------------------------第6章 图像处理 -------------------------------------------------------------------
//线性滤波：方框滤波、均值滤波、高斯滤波
//非线性滤波：中值滤波、双边滤波
/*
#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

//线性滤波：方框滤波、均值滤波、高斯滤波
bool boolBoxFilter(InputArray src);
bool boolBlur(InputArray src);
bool boolGaussianBlur(InputArray src);

//非线性滤波：中值滤波、双边滤波
bool boolMedianBlur(InputArray src);
bool boolBilateralFilter(InputArray src);

int main(int argc, char** argv)
{
    
    Mat srcImage = imread("/Users/lichunxia/Desktop/opencvPic/girl.jpg");
    if(!srcImage.data)
    {
        cout << "读取图片错误～～" <<endl;
        return false;
    }
    namedWindow("original-Window");
    imshow("original-Window", srcImage);
    
//    if(boolBoxFilter(srcImage)&&boolBlur(srcImage)&&boolGaussianBlur(srcImage))
    if(boolMedianBlur(srcImage)&&boolBilateralFilter(srcImage))
        cout << "程序运行成功～～ " << endl<<endl;
    waitKey();
    return 0;
}

bool boolBoxFilter(InputArray src)
{
    Mat out;
    namedWindow("boxFilter-window");
    boxFilter(src, out, -1, Size(5,5));
    imshow("boxFilter-window", out);
    return true;
}
bool boolBlur(InputArray src)
{
    Mat out;
    namedWindow("blur-window");
    blur(src, out, Size(10,10));
    imshow("blur-window", out);
    return true;
}
bool boolGaussianBlur(InputArray src)
{
    Mat out;
    namedWindow("gaussianBlur-window");
    GaussianBlur(src, out, Size(5,5), 0, 0);
    imshow("gaussianBlur-window", out);
    return true;
}
bool boolMedianBlur(InputArray src)
{
    Mat out;
    namedWindow("medianBlur-window",1);
    medianBlur(src, out, 7);
    imshow("medianBlur-window", out);
    return true;
}
bool boolBilateralFilter(InputArray src)
{
    Mat out;
    namedWindow("bilatralFilter-window",1);
    bilateralFilter(src, out, 25, 25*2, 25/2);
    imshow("bilatralFilter-window", out);
    return true;
}
 */
//线性滤波综合实例
//非线性滤波综合实例

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

//全局变量
Mat g_srcImage, g_dstImage1, g_dstImage2, g_dstImage3, g_dstImage4, g_dstImage5;
int g_nBoxFilterValue = 6; //方框滤波参数值
int g_nMeanBlurValue = 10; //均值滤波参数值
int g_nGaussianBlurValue = 6; //高斯滤波参数值
int g_nMedianBlurValue = 10; //中值滤波参数值
int g_nBilateralFilterValue = 10; //双边滤波参数值

//全局函数
//回调函数
//线性滤波
static void on_BoxFilter(int, void *); //方框滤波器
static void on_MeanBlur(int, void *);   //均值滤波器
static void on_GaussianBlur(int, void *); //高斯滤波器

//非线性滤波
static void on_MedianBlur(int, void *); //中值滤波器
static void on_BilateralFilter(int, void *); //双边滤波器

int main()
{
    //1.read the image
    g_srcImage = imread("/Users/lichunxia/Desktop/OpenCV/OpencvPic/girl.jpg");
    if(!g_srcImage.data)
    {
        cout << "error~~~" <<endl<<endl;
        return false;
    }
    
    //2.copy the src to dst
    g_dstImage1 = g_srcImage.clone();
    g_dstImage2 = g_srcImage.clone();
    g_dstImage3 = g_srcImage.clone();
    g_dstImage4 = g_srcImage.clone();
    g_dstImage5 = g_srcImage.clone();
    
    //3.show the srcImage
    namedWindow("srcImage-window",1);
    imshow("srcImage-window", g_srcImage);
    
    //===========================<1> BoxFilter ======================================
    //create a window
    namedWindow("boxFilter-window",1);
    
    //create trackbar
    char trackbarName1[50];
    sprintf(trackbarName1, "core : %d", g_nBoxFilterValue);
    createTrackbar(trackbarName1, "boxFilter-window", &g_nBoxFilterValue, 40, on_BoxFilter);
    on_BoxFilter(g_nBoxFilterValue, 0);
    
    //===========================<2>MeanBlur  ========================================
    //create a window
    namedWindow("meanBlur-window",1);
    
    //create trackbar
    char trackbarName2[50];
    sprintf(trackbarName2, "core : %d", g_nMeanBlurValue);
    createTrackbar(trackbarName2, "meanBlur-window", &g_nMeanBlurValue, 40, on_MeanBlur);
    on_MeanBlur(g_nMeanBlurValue, 0);

    //==========================<3>GaussianBlur =======================================
    //create a window
    namedWindow("gaussianBlur-window",1);
    
    //create trackbar
    char trackbarName3[50];
    sprintf(trackbarName3, "core : %d", g_nGaussianBlurValue);
    createTrackbar(trackbarName3, "gaussianBlur-window", &g_nGaussianBlurValue, 40, on_GaussianBlur);
    on_GaussianBlur(g_nGaussianBlurValue, 0);
    
    //=========================== <4>MedianBlur ====================================================
    //create a window
    namedWindow("medianBlur-window",1);
    
    //create trackbar
    char trackbarName4[50];
    sprintf(trackbarName4, "canshuzhi : %d", g_nMedianBlurValue);
    createTrackbar(trackbarName4, "medianBlur-window", &g_nMedianBlurValue, 50, on_MedianBlur);
    on_MedianBlur(g_nMedianBlurValue, 0);
    
    //=========================== <5>BilateralFilter ===============================================
    //create a window
    namedWindow("bilateralFilter-window",1);
    
    //create trackbar
    char trackbarName5[50];
    sprintf(trackbarName5, "canshuzhi : %d", g_nBilateralFilterValue);
    createTrackbar(trackbarName5, "bilateralFilter-window", &g_nBilateralFilterValue, 50, on_BilateralFilter);
    on_BilateralFilter(g_nBilateralFilterValue, 0);
    
    cout << "程序运行完毕～～～" <<endl;
    //ddd
    
    waitKey();
    return 0;
}
static void on_BoxFilter(int, void *)
{
    boxFilter(g_srcImage, g_dstImage1, -1, Size(g_nBoxFilterValue+1, g_nBoxFilterValue+1));
    imshow("boxFilter-window", g_dstImage1);
}
static void on_MeanBlur(int, void *)
{
    blur(g_srcImage, g_dstImage2, Size(g_nMeanBlurValue+1,g_nMeanBlurValue+1));
    imshow("meanBlur-window", g_dstImage2);
}
static void on_GaussianBlur(int, void *)
{
    GaussianBlur(g_srcImage, g_dstImage3, Size(g_nGaussianBlurValue * 2 + 1, g_nGaussianBlurValue * 2 + 1), 0, 0);
    imshow("gaussianBlur-window", g_dstImage3);
}
static void on_MedianBlur(int, void *)
{
    medianBlur(g_srcImage, g_dstImage4, g_nMedianBlurValue*2+1); //参数值必须为奇数
    imshow("medianBlur-window", g_dstImage4);
}
static void on_BilateralFilter(int, void *)
{
    bilateralFilter(g_srcImage, g_dstImage5, g_nBilateralFilterValue, g_nBilateralFilterValue*2, g_nBilateralFilterValue/2);
    imshow("bilateralFilter-window", g_dstImage5);
}












