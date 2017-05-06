#include <opencv2/opencv.hpp>
//#include <opencv2/highgui.hpp>  //opencv highgui 模块头文件
//#include <opencv2/imgproc/imgproc.hpp> //opencv 图像处理头文件

using namespace cv;

int main(int argc, const char * argv[]) { //int argc 整型，用来统计程序运行时发送给main函数的命令行参数的个数；
    
    
    /**图像显示**
     string path = "/Users/lichunxia/Desktop/opencvPic/picture1.jpg";
     Mat srcImage = imread(path);  //图像的载入 imread()函数
     
     namedWindow("test1");          //创建窗口 namedWindow()
     imshow("test1", srcImage);    //图像的显示 imshow()
     **/
    
    /**图像腐蚀**
     Mat element = getStructuringElement(MORPH_RECT,Size(15,15));
     Mat dstImage;
     erode(srcImage, dstImage, element);  //图像腐蚀
     namedWindow("test2");
     imshow("test2", dstImage);
     **/
    
    /**图像模糊**
     Mat dstImage;
     blur(srcImage, dstImage, Size(7,7));
     namedWindow("test2");
     imshow("test2", dstImage);
     **/
    
    /**canny 边缘检测**/
//    string path = "/Users/lichunxia/Desktop/opencvPic/picture1.jpg";
//    Mat srcImage = imread(path);  //图像的载入 imread()函数
//     Mat edge , grayImage;
//     cvtColor(srcImage, grayImage,CV_BGR2GRAY);
//     blur(grayImage, edge, Size(3,3));
//     Canny(edge,edge,3,9,3);
//     namedWindow("test2");
//     imshow("test2", edge);
//    
//    
////    /**视频载入 以及canny边缘检测**/
////     CvCapture* capture = cvCreateFileCapture("/Users/lichunxia/Desktop/opencvPic/testVideo.mp4"); //获取视频文件
//    VideoCapture capture("/Users/lichunxia/Desktop/opencvPic/1.avi");
////     CvCapture* capture = cvCreateCameraCapture(0);  //调用摄像头读入视频
//    
//    IplImage* frame;
//   
//    
//    namedWindow(   "canny" );
//     while (1)
//     {
//       frame = cvQueryFrame(capture);
//       if (!frame)   break   ;
//       
//       cvShowImage(   "canny" ,frame);
//       char  c = cvWaitKey(33);
//       if (c == 27)   break ;
//     }
//     cvReleaseCapture(&capture);
//     cvDestroyWindow(   "canny" );
    
    
//   //*视频 canny 边缘检测 *
//    cvNamedWindow("Video", CV_WINDOW_AUTOSIZE);
//    cvNamedWindow("Gray", CV_WINDOW_AUTOSIZE);
//    cvNamedWindow("Canny", CV_WINDOW_AUTOSIZE);
//    
//    CvCapture *capture = cvCreateFileCapture("/Users/lichunxia/Desktop/opencvPic/1.avi");//获取视频文件
////     CvCapture* capture = cvCreateCameraCapture(0);  //调用摄像头读入视频
//    IplImage *frame;
//    IplImage *frame_gray;
//    IplImage *frame_canny;
//    
//    frame = cvQueryFrame(capture);
//    frame_gray = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
//    frame_canny = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
//    
//    while(1)
//    {
//        if(!frame)
//        {
//            break;
//        }
//        
//        cvConvertImage(frame, frame_gray);
//        cvCanny(frame_gray, frame_canny, 10, 100, 3);
//        
//        cvShowImage("Video", frame);
//        cvShowImage("Gray", frame_gray);
//        cvShowImage("Canny", frame_canny);
//        
//        char c = cvWaitKey(33);
//        if (c == 27)
//        {
//            break;
//        }
//        frame = cvQueryFrame(capture);
//    }
//    
//    cvReleaseCapture(&capture);
//    
//    cvDestroyAllWindows();

    waitKey(0);
    return 0;
}
