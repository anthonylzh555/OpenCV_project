// ContourDemo2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\core\utility.hpp>
#include <opencv2\imgproc.hpp>
#include "opencv2\highgui.hpp"
#include <iostream>
#include <iomanip>

using namespace cv;
using namespace std;

Mat imgSrc, imgG, imgBW, imgDst, imgMask;
int main()
{
	//imgSrc = imread("C:\\OpenCV3.1\\images\\contour\\star.jpg", CV_LOAD_IMAGE_UNCHANGED);
	//imgSrc = imread("C:\\OpenCV3.1\\images\\contour\\rectangle.jpg", CV_LOAD_IMAGE_UNCHANGED);
	imgSrc = imread("C:\\OpenCV3.1\\images\\contour\\polygonColor.jpg", CV_LOAD_IMAGE_UNCHANGED);

	if (!imgSrc.data)
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}

	cvtColor(imgSrc, imgG, CV_BGR2GRAY);
	threshold(imgG, imgBW, 100, 255, THRESH_BINARY);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	RNG rng(clock());

	findContours(imgBW, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	//findContours(imgBW, contours, hierarchy, RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

	imgSrc.copyTo(imgDst);


	for (int i = 0; i < contours.size(); i++) {
		cout << "contour # " << i << endl;
		imgMask = Mat::zeros(imgSrc.size(), CV_8UC1);
		drawContours(imgMask, contours, i, Scalar(255), -1);
		Mat imgROI;
		imgSrc.copyTo(imgROI, imgMask);
		string name = std::to_string(i);
		string name2 = std::to_string(4 + i);
		imshow(name2, imgMask);
		imshow(name, imgROI);
		cout << "mean = " << mean(imgSrc, imgMask) << endl;
	}
	imshow("Contour1", imgDst);

	waitKey(0);
	return 0;
}



