// FloodFillDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <iomanip>

using namespace cv;
using namespace std;

int main()
{
	Mat imgSrc, imgG, imgDst;
	imgSrc = imread("C:\\OpenCV3.1\\images\\coins.jpg", CV_LOAD_IMAGE_UNCHANGED);
	if (!imgSrc.data)
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}

	cvtColor(imgSrc, imgG, COLOR_BGR2GRAY);
	Point seedPoint(10, 10);
	// flood fill with red
	Rect ccomp;

	//Fill mask with value 128
	uchar fillValue = 128;
	int ffillMode = 1;
	int loDiff = 10, upDiff = 20;
	int lo = ffillMode == 0 ? 0 : loDiff;
	int up = ffillMode == 0 ? 0 : upDiff;
	int connectivity = 4;
	int isColor = true;
	int newMaskVal = 255;
	int flags = connectivity + (newMaskVal << 8) +
		(ffillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);
	Scalar newVal = Scalar(255);
	int area;
	area = floodFill(imgG, seedPoint, newVal, &ccomp, Scalar(lo, lo, lo),    //**FloodFill
		Scalar(up, up, up), flags);
	imgSrc.copyTo(imgDst, imgG);

	// draw a blue circle at the seed point
	circle(imgSrc, seedPoint, 6, Scalar(255, 0, 0), 3, 8);
	imshow("Src", imgSrc);
	// show the output

	namedWindow("Output", CV_WINDOW_AUTOSIZE);

	imshow("Output", imgG);
	cvWaitKey(0);
	return 0;
}
