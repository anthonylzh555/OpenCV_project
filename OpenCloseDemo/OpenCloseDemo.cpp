// OpenCloseDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;
using namespace cv;

/// Global variables
Mat imgSrc, imgSrcGray, imgOpening, imgClosing;

int openingElem = 0;
int openingSize = 3;
int closingElem = 0;
int closingSize = 3;
int const maxElem = 2;
int const maxKernelSize = 21;

/** Function Headers */
void Opening(int, void*);
void Closing(int, void*);

/** @function main */
int main(int argc, char** argv)
{
	int thresh = 20;
	int theshSliderMax = 255;
	/// Load an image
	imgSrc = imread("C:\\OpenCV3.1\\images\\LinuxLogo.png");
	//imgSrc = imread("C:\\OpenCV3.1\\images\\whiteJ.jpg");
	/*imgSrc = imread("C:\\OpenCV3.1\\images\\blackJ.jpg");*/
	//imgSrc = imread("C:\\OpenCV3.1\\images\\windmill.jpg");
	pyrUp(imgSrc, imgSrc);
	if (!imgSrc.data)
	{
		return -1;
	}
	imgSrc.copyTo(imgSrcGray);
	cvtColor(imgSrc, imgSrcGray, COLOR_BGR2GRAY);
	threshold(imgSrcGray, imgSrcGray, thresh, theshSliderMax, THRESH_BINARY);

	/// Create windows
	namedWindow("Color", CV_WINDOW_AUTOSIZE);
	namedWindow("Opening", CV_WINDOW_AUTOSIZE);
	namedWindow("Closing", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("Dilation", imgSrc.cols, 0);
	imshow("Color", imgSrc);
	/// Create Erosion Trackbar
	createTrackbar("Elem 0~2", "Opening", &openingElem, maxElem, Opening);
	createTrackbar("Kernel", "Opening", &openingSize, 200, Opening);

	/// Create Dilation Trackbar
	createTrackbar("Elem 0~2", "Closing", &closingElem, maxElem, Closing);
	createTrackbar("Kernel", "Closing", &closingSize, 200, Closing);

	/// Default start
	Opening(0, 0);
	Closing(0, 0);

	waitKey(0);
	return 0;
}

/**  @function Erosion  */
void Opening(int, void*)
{
	int opening_type;
	switch (openingElem)
	{
	case 0:
		opening_type = MORPH_RECT;
		break;
	case 1:
		opening_type = MORPH_CROSS;
		break;
	case 2:
		opening_type = MORPH_ELLIPSE;
		break;
	}

	Mat element = getStructuringElement(opening_type,
		Size(2 * openingSize + 1, 2 * openingSize + 1),
		Point(openingSize, openingSize));

	/// Apply the erosion operation
	morphologyEx(imgSrcGray, imgOpening, MORPH_OPEN, element);
	imshow("Opening", imgOpening);
}

/** @function Dilation */
void Closing(int, void*)
{
	int closing_type;
	switch (closingElem)
	{
	case 0:
		closing_type = MORPH_RECT;
		break;
	case 1:
		closing_type = MORPH_CROSS;
		break;
	case 2:
		closing_type = MORPH_ELLIPSE;
		break;
	}


	Mat element = getStructuringElement(closing_type,
		Size(2 * closingSize + 1, 2 * closingSize + 1),
		Point(closingSize, closingSize));

	/// Apply the closing operation
	morphologyEx(imgSrcGray, imgClosing, MORPH_CLOSE, element);
	imshow("Closing", imgClosing);
}
