// test1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include "cv.h"
#include "highgui.h"
#include <math.h>   

using namespace cv;    
using namespace std;   

#define RATIO 0.25  
#define WEIGHT 2  
#define DELTA 20  
#define  ALPHA 0.15  
#define  BETA 0.85  
  

int _tmain(int argc, _TCHAR* argv[])  
{  
    // 准备源图像  
    //IplImage* src = cvLoadImage("G:/图像渐变/image/dao.jpg");
	IplImage* src = cvLoadImage("F:/照片/应用宝照片备份/魅族 M463C照片备份/1044_thumb.jpg");  
    int width = src->width;  
    int height = src->height;  
  
    //cvSetImageROI(src, cvRect(0, (1-RATIO)*height, width, height));  
    int mir_w = width;  
    int mir_h = RATIO*height;  
    IplImage* mir = cvCreateImage(cvSize(width, RATIO*height) ,src->depth, src->nChannels);  
    //cvCopy(src, mir);// 拷贝有bug  
    //cvResetImageROI(src);  
    // 从源图像拷贝1/4图像作为镜像图像  
    for (int i=0; i<width; i++)  
    {  
        for (int j=(1-RATIO)*height; j<height; j++)  
        {  
            uchar* pSrc = &CV_IMAGE_ELEM(src, uchar, j, i*3);  
            uchar* pDst = &CV_IMAGE_ELEM(mir, uchar, (int)(j-(1-RATIO)*height), i*3);  
            pDst[0] = pSrc[0];  //B  
            pDst[1] = pSrc[1];  //G  
            pDst[2] = pSrc[2];  //R  
        }  
    }  
    cvFlip(mir, NULL, 0);// 0：上下镜像；1：左右镜像  
  
    // 准备最终结果图像  
    CvSize dstSize;  
    dstSize.width = width;  
    dstSize.height = height + mir_h;  
    IplImage* dst = cvCreateImage(dstSize, src->depth, src->nChannels);  
    cvZero(dst);  
  
    // 载入源图像到结果图像中  
    cvSetImageROI(dst, cvRect(0, 0, width, height));  
    cvCopy(src, dst);  
    cvResetImageROI(dst);  
  
    // 准备镜像图像  
    IplImage* mask = cvCreateImage(cvSize(mir_w, mir_h), mir->depth, mir->nChannels);  
    CvScalar a = CV_RGB(255, 255, 255);  
    CvScalar b = CV_RGB(0, 0, 0);  
    cvSet(mask, a);  
  
    CvPoint origin = cvPoint(mir_w/2, 0);               // 光源设在镜像图像上方  
    //CvPoint center = cvPoint(mir_w/2, mir_h/2);  
  
    float distance = (mir_w-1 - origin.x)*  
        (mir_w-1 - origin.x)+                           // 光源与图像右下角的距离  
        (mir_h-1 - origin.y)*  
        (mir_h-1 - origin.y);  
    distance = sqrt(distance);  
  
    //double weightB = (b.val[0] - a.val[0])/distance;  // 分别计算BGR三个通道的权重  
    //double weightG = (b.val[1] - a.val[1])/distance;  
    //double weightR = (b.val[2] - a.val[2])/distance;  
    double weight = (b.val[0] - a.val[0])/distance; // 计算BGR三个通道的权重 -1.72  
  
    for ( int i=0; i<mask->width; i++)  
    {  
        for (int j=0; j<mask->height; j++)  
        {  
            float dist = WEIGHT*(j-origin.y)*(j-origin.y);  
            dist = sqrt(dist);  
            uchar* ptr = &CV_IMAGE_ELEM(mask, uchar, j, i*3);  
            ptr[0] = cvRound(ptr[0] + weight*dist-DELTA);   //B  
            ptr[1] = cvRound(ptr[1] + weight*dist-DELTA);   //G  
            ptr[2] = cvRound(ptr[2] + weight*dist-DELTA);   //R  
        }  
    }  
    cvAddWeighted(mir,ALPHA , mask, BETA, 0, mir);  
  
    // 载入镜像图像到结果图像中  
    cvSetImageROI(dst, cvRect(0, height, mir_w, mir_h));  
    cvCopy(mir, dst);  
    cvResetImageROI(dst);  
  
    cvNamedWindow( "test", 1);  
    cvShowImage( "test", dst);  
    cvWaitKey();  
  
    // 释放资源  
    cvDestroyWindow("test");  
    cvReleaseImage(&src);  
    cvReleaseImage(&dst);  
    cvReleaseImage(&mask);  
    cvReleaseImage(&mir);  
    return 0;  
}  


/*
int main( int argc, char** argv )   
{  
    IplImage* image = cvCreateImage(cvSize(800,600),IPL_DEPTH_8U,3);  
    if(!image)   
    {  
        return -1;  
    }  
    //CvScalar a=CV_RGB(0,255,0);  
    //CvScalar b=CV_RGB(0,0,0);
	CvScalar a=CV_RGB(0,255,0);
	CvScalar b=CV_RGB(255,0,0);

    cvSet(image,a);  
    CvPoint origin=cvPoint(800,600);  
    CvPoint center=cvPoint(image->width/2,image->height/2);  
    double  distance;  
    if(origin.x<=center.x && origin.y<=center.y)  
    {  
        distance=sqrt((float)((image->width-1-origin.x)*(image->width-1-origin.x)+(image->height-1-origin.y)*(image->height-1-origin.y)));  
    }  
    else if(origin.x<=center.x && origin.y>center.y)  
    {  
        distance=sqrt((float)((image->width-1-origin.x)*(image->width-1-origin.x)+  
                        origin.y*origin.y));  
    }  
    else if(origin.x>center.x && origin.y<=center.y)  
    {  
        distance=sqrt((float)(origin.x*origin.x+  
                        (image->height-1-origin.y)*(image->height-1-origin.y)));  
    }  
    else if(origin.x>center.x && origin.y>center.y)  
    {  
        distance=sqrt((float)(origin.x*origin.x+origin.y*origin.y));  
    }  
    double weightB=(b.val[0]-a.val[0])/distance;  
    double weightG=(b.val[1]-a.val[1])/distance;  
    double weightR=(b.val[2]-a.val[2])/distance;  
    for(int i=0;i<image->width;i++)  
    {         
        for(int j=0;j<image->height;j++)  
        {  
            double dist=sqrt((float)((i-origin.x)*(i-origin.x)+(j-origin.y)*(j-origin.y)));  
            uchar* ptr = &CV_IMAGE_ELEM(image,uchar,j,i*3);  
            ptr[0] = cvRound(ptr[0]+weightB*dist);  
            ptr[1] = cvRound(ptr[1]+weightG*dist);  
            ptr[2] = cvRound(ptr[2]+weightR*dist);   
        }  
    }  
    cvSaveImage( "radial.jpg", image );  
    cvNamedWindow( "test", 1 );  
    cvShowImage( "test", image );  
    cvWaitKey();  
    cvDestroyWindow("test");  
    cvReleaseImage(&image);  
    return 0;   
}  
*/