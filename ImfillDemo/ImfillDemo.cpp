// ImfillDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;


Mat imgSrc;
Mat imgG;
Mat imgBW;
Mat imgFF;
Mat imgFFInv;
Mat imgDst;

const int threshSliderMax = 255;
int threshSlider = 100;

void OnTrackBar(int v1, void* v2)
{
	//threshold(imgG, imgBW, threshSlider, 255, THRESH_BINARY);
	threshold(imgG, imgBW, threshSlider, 255, THRESH_BINARY_INV);

	//floodFill(imgBW, cv::Point(0, 0), Scalar(255));

	// Floodfill from point (0, 0)
	imgBW.copyTo(imgFF);
	floodFill(imgFF, cv::Point(0, 0), Scalar(255));

	// Invert floodfilled image
	bitwise_not(imgFF, imgFFInv);

	// Combine the two images to get the foreground.
	imgDst = (imgBW | imgFFInv);

	// Display images
	imshow("Thresholded Image", imgBW);
	imshow("Floodfilled Image", imgFF);
	imshow("Inverted Floodfilled Image", imgFFInv);
	imshow("Foreground", imgDst);
}

int main()
{
	//imgSrc = imread("C:\\OpenCV3.1\\images\\backEnd7.jpg");
	//imgSrc = imread("C:\\OpenCV3.1\\images\\Nickel.jpg");
	imgSrc = imread("C:\\OpenCV3.1\\images\\TenDollar.jpg");
	//imgSrc = imread("C:\\OpenCV3.1\\images\\filling_text_holes_01.png");

	if (imgSrc.empty())
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}
	cvtColor(imgSrc, imgG, CV_BGR2GRAY);
	namedWindow("Src Image");
	imshow("Src Image", imgSrc);
	createTrackbar("Threshold", "Src Image", &threshSlider,
		threshSliderMax, OnTrackBar);
	waitKey(0);
	return 0;
}