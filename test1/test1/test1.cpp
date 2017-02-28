// test1.cpp : �������̨Ӧ�ó������ڵ㡣
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
    // ׼��Դͼ��  
    //IplImage* src = cvLoadImage("G:/ͼ�񽥱�/image/dao.jpg");
	IplImage* src = cvLoadImage("F:/��Ƭ/Ӧ�ñ���Ƭ����/���� M463C��Ƭ����/1044_thumb.jpg");  
    int width = src->width;  
    int height = src->height;  
  
    //cvSetImageROI(src, cvRect(0, (1-RATIO)*height, width, height));  
    int mir_w = width;  
    int mir_h = RATIO*height;  
    IplImage* mir = cvCreateImage(cvSize(width, RATIO*height) ,src->depth, src->nChannels);  
    //cvCopy(src, mir);// ������bug  
    //cvResetImageROI(src);  
    // ��Դͼ�񿽱�1/4ͼ����Ϊ����ͼ��  
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
    cvFlip(mir, NULL, 0);// 0�����¾���1�����Ҿ���  
  
    // ׼�����ս��ͼ��  
    CvSize dstSize;  
    dstSize.width = width;  
    dstSize.height = height + mir_h;  
    IplImage* dst = cvCreateImage(dstSize, src->depth, src->nChannels);  
    cvZero(dst);  
  
    // ����Դͼ�񵽽��ͼ����  
    cvSetImageROI(dst, cvRect(0, 0, width, height));  
    cvCopy(src, dst);  
    cvResetImageROI(dst);  
  
    // ׼������ͼ��  
    IplImage* mask = cvCreateImage(cvSize(mir_w, mir_h), mir->depth, mir->nChannels);  
    CvScalar a = CV_RGB(255, 255, 255);  
    CvScalar b = CV_RGB(0, 0, 0);  
    cvSet(mask, a);  
  
    CvPoint origin = cvPoint(mir_w/2, 0);               // ��Դ���ھ���ͼ���Ϸ�  
    //CvPoint center = cvPoint(mir_w/2, mir_h/2);  
  
    float distance = (mir_w-1 - origin.x)*  
        (mir_w-1 - origin.x)+                           // ��Դ��ͼ�����½ǵľ���  
        (mir_h-1 - origin.y)*  
        (mir_h-1 - origin.y);  
    distance = sqrt(distance);  
  
    //double weightB = (b.val[0] - a.val[0])/distance;  // �ֱ����BGR����ͨ����Ȩ��  
    //double weightG = (b.val[1] - a.val[1])/distance;  
    //double weightR = (b.val[2] - a.val[2])/distance;  
    double weight = (b.val[0] - a.val[0])/distance; // ����BGR����ͨ����Ȩ�� -1.72  
  
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
  
    // ���뾵��ͼ�񵽽��ͼ����  
    cvSetImageROI(dst, cvRect(0, height, mir_w, mir_h));  
    cvCopy(mir, dst);  
    cvResetImageROI(dst);  
  
    cvNamedWindow( "test", 1);  
    cvShowImage( "test", dst);  
    cvWaitKey();  
  
    // �ͷ���Դ  
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