// test2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include<iostream> 
#include<cv.h> 
#include<highgui.h> 
using namespace std; 
using namespace cv; //合成图片 
int main() { 
	clock_t start, finish; 
	start = clock(); 
	double duration; 
	IplImage*img1 = cvLoadImage("2.jpg"); 
	//IplImage* img2 = cvLoadImage("2.jpg");
	IplImage*img = cvLoadImage("1.jpg", 1); 
	//IplImage* img = cvCreateImage(cvSize(img1->width + img2->width, img1->height), img1->depth, 3); 
	//cout << img1->widthStep << endl; 
	//cout << img2->widthStep << endl; 
	uchar r1, g1, b1; 
	for (int i = 0; i < img1->height; i++) { 
		uchar *ptrImage = (uchar*)(img1->imageData + i * img1->widthStep); 
		uchar *ptrDst = (uchar*)(img->imageData + i * img->widthStep); 
		for (int j = 0; j < img1->width; j++) { 
			b1 = ptrImage[3 * j + 0]; 
			g1 = ptrImage[3 * j + 1]; 
			r1 = ptrImage[3 * j + 2]; 
			ptrDst[3 * (j+400) + 0] = b1; 
			ptrDst[3 * (j+400) + 1] = g1; 
			ptrDst[3 * (j+400) + 2] = r1; 
		} 
	} 
	cvSaveImage("result.jpg", img); 
	finish = clock(); 
	duration = (double)(finish - start) / CLOCKS_PER_SEC; 
	cout << duration << endl; 
	cvNamedWindow("img.jpg", 0); 
	cvShowImage("img.jpg", img); 
	waitKey(); 
	return 0; 
}


/*
IplImage* image3 = cvCreateImage( cvSize(image1->width+image2->width,MAX(image1->height,image2->height)),IPL_DEPTH_8U,3);

CvRect rect=cvRect(0,0,image1->width,image1->height);
cvSetImageROI(image3,rect);
cvCopy(image1,image3);
cvResetImageROI(image3);

rect=cvRect(image1->width,0,image2->width,image2->height);
cvSetImageROI(image3,rect);
cvCopy(image2,image3);
cvResetImageROI(image3);

cvNamedWindow("image3");
cvShowImage("image3",image3);
*/

/*
int main(){
    cv::Mat image = cv::imread("E:/Image/Fruits.jpg");
    cv::Mat logo = cv::imread("E:/logo.png");
    cv::Mat imageROI;
    imageROI = image(cv::Rect(10,10,logo.cols,logo.rows));
    logo.copyTo(imageROI);
    cv::namedWindow("result");
    cv::imshow("result",image);
    cv::waitKey();
    return 0;
}
*/



