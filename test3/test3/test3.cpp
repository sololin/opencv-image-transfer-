// test3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <string>
#include <string.h>

using namespace std;
using namespace cv;

int _tmain(int argc, _TCHAR* argv[])
{
	VideoWriter video1("G:/PPT监测项目/图像渐变/image/out8.avi",CV_FOURCC('M', 'J', 'P', 'G'),20, Size(1920,1080),true);

	Mat img_background = imread("G:/PPT监测项目/图像渐变/image/shamo.jpg");
	Mat img_show = imread("G:/PPT监测项目/图像渐变/image/zhuaimao.jpg");
	Mat imgROI1_y,imgROI2_y;//垂直矩形
	Mat imgROI1_x,imgROI2_x;//水平矩形
	int center_x = img_background.rows/2, center_y = img_background.cols/2;
	cout<<center_x<<"   "<<center_y<<endl;
	namedWindow("result");
	int r_col = 16, r_row = 9;
	while(r_col < 961 && r_row <541) {
		//垂直矩形
		imgROI1_y = img_background(Rect(center_y-r_col,0,2*r_col,1080));
		imgROI2_y = img_show(Rect(center_y-r_col,0,2*r_col,1080));
		//水平矩形
		imgROI1_x = img_background(Rect(0,center_x-r_row,1920,2*r_row));
		imgROI2_x = img_show(Rect(0,center_x-r_row,1920,2*r_row));
		//namedWindow("imgROI1");
		//imshow("imgROI1",imgROI1);
		imgROI2_y.copyTo(imgROI1_y);
		imgROI2_x.copyTo(imgROI1_x);
		imshow("result",img_background);
		waitKey(100);
		r_col+=16;
		r_row+=9;
		video1.write(img_background);
		
	}

	int fontSize = 1;video1.write(img_background);

	int ii = 0;

	while(fontSize < 14) {
		CvFont font;    
		double hScale=4;   
		double vScale=4;    
		int lineWidth=8;// 相当于写字的线条    
		String showMsg ="Hello world!!! "; 
		char* show1;
		String show2;
		for(int ii=0; ii<=fontSize; ii++) {
			//show1[ii] = showMsg.substr(ii,ii+1);
			//char *p=showMsg.c_str();
			show2 = showMsg.substr(0,ii+1);
			show1 = (char*)show2.data();
		}
		//cout<<show1<<endl;
		//show2 = showMsg.substr(0,2);
		//_gcvt(distance_button*7.6/1000,3,show1);
		//if(distance_button != 0)
		//	_gcvt(1000*7.6/1000,3,show1);
			//itoa(distance_button*7.6/1000,show1,10);
		//else
		//	_gcvt(distance_top*7.6/1000,3,show1);
			//itoa(distance_top*7.6/1000,show1,10);
		//strcat(showMsg,show1); 
		//strcat(showMsg," m");
		// 初始化字体   
		cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX|CV_FONT_ITALIC, hScale,vScale,0,lineWidth);//初始化字体，准备写到图片上的   
		// cvPoint 为起笔的x，y坐标   
		IplImage iplimage = img_background;
	
		cvPutText(&iplimage,show1,cvPoint(350,200),&font,CV_RGB(255,0,0));//在图片中
		
		//cvPutText(&iplimage,show1,cvPoint(700,400),&font,CV_RGB(0,0,255));//在图片中

		//显示图片效果
		Mat imageTransfor(&iplimage);
		//缩小显示
		/*
		 Size dsize = Size(imageTransfor.cols*0.7,imageTransfor.rows*0.7);
		 Mat image1 = Mat(dsize,CV_32S);
		 resize(imageTransfor,image1,dsize);
		*/
		// namedWindow("Lines");
		// imshow("Lines",image1);
		 imshow("result",img_background);
		 fontSize ++;
		 waitKey(200);
		 video1.write(img_background);

	}

	fontSize = 0;
	while(fontSize < 14) {
		CvFont font;    
		double hScale=4;   
		double vScale=4;    
		int lineWidth=8;// 相当于写字的线条    
		String showMsg ="Hello world!!! "; 
		char* show1;
		String show2;
		for(int ii=0; ii<=fontSize; ii++) {
			//show1[ii] = showMsg.substr(ii,ii+1);
			//char *p=showMsg.c_str();
			show2 = showMsg.substr(0,ii+1);
			show1 = (char*)show2.data();
		}
		//cout<<show1<<endl;
		//show2 = showMsg.substr(0,2);
		//_gcvt(distance_button*7.6/1000,3,show1);
		//if(distance_button != 0)
		//	_gcvt(1000*7.6/1000,3,show1);
			//itoa(distance_button*7.6/1000,show1,10);
		//else
		//	_gcvt(distance_top*7.6/1000,3,show1);
			//itoa(distance_top*7.6/1000,show1,10);
		//strcat(showMsg,show1); 
		//strcat(showMsg," m");
		// 初始化字体   
		cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX|CV_FONT_ITALIC, hScale,vScale,0,lineWidth);//初始化字体，准备写到图片上的   
		// cvPoint 为起笔的x，y坐标   
		IplImage iplimage = img_background;
	
		cvPutText(&iplimage,show1,cvPoint(700,400),&font,CV_RGB(255,0,0));//在图片中
		
		//cvPutText(&iplimage,show1,cvPoint(900,600),&font,CV_RGB(0,0,255));//在图片中

		//显示图片效果
		Mat imageTransfor(&iplimage);
		//缩小显示
		/*
		 Size dsize = Size(imageTransfor.cols*0.7,imageTransfor.rows*0.7);
		 Mat image1 = Mat(dsize,CV_32S);
		 resize(imageTransfor,image1,dsize);
		*/
		// namedWindow("Lines");
		// imshow("Lines",image1);
		 imshow("result",img_background);
		 fontSize ++;
		 waitKey(200);
		 video1.write(img_background);

	}

	fontSize = 0;
	while(fontSize < 14) {
		CvFont font;    
		double hScale=4;   
		double vScale=4;    
		int lineWidth=8;// 相当于写字的线条    
		String showMsg ="Hello world!!! "; 
		char* show1;
		String show2;
		for(int ii=0; ii<=fontSize; ii++) {
			//show1[ii] = showMsg.substr(ii,ii+1);
			//char *p=showMsg.c_str();
			show2 = showMsg.substr(0,ii+1);
			show1 = (char*)show2.data();
		}
		//cout<<show1<<endl;
		//show2 = showMsg.substr(0,2);
		//_gcvt(distance_button*7.6/1000,3,show1);
		//if(distance_button != 0)
		//	_gcvt(1000*7.6/1000,3,show1);
			//itoa(distance_button*7.6/1000,show1,10);
		//else
		//	_gcvt(distance_top*7.6/1000,3,show1);
			//itoa(distance_top*7.6/1000,show1,10);
		//strcat(showMsg,show1); 
		//strcat(showMsg," m");
		// 初始化字体   
		cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX|CV_FONT_ITALIC, hScale,vScale,0,lineWidth);//初始化字体，准备写到图片上的   
		// cvPoint 为起笔的x，y坐标   
		IplImage iplimage = img_background;
	
		//cvPutText(&iplimage,show1,cvPoint(650,400),&font,CV_RGB(255,0,0));//在图片中
		
		cvPutText(&iplimage,show1,cvPoint(900,600),&font,CV_RGB(0,0,255));//在图片中

		//显示图片效果
		Mat imageTransfor(&iplimage);
		//缩小显示
		/*
		 Size dsize = Size(imageTransfor.cols*0.7,imageTransfor.rows*0.7);
		 Mat image1 = Mat(dsize,CV_32S);
		 resize(imageTransfor,image1,dsize);
		*/
		// namedWindow("Lines");
		// imshow("Lines",image1);
		 imshow("result",img_background);
		 fontSize ++;
		 waitKey(200);
		 video1.write(img_background);

	}

	return 0;
}

