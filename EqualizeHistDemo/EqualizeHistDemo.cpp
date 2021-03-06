// EqualizeHistDemo.cpp : Defines the entry point for the console application.
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
int main()
{
	Mat imgSrc, imgDst, kernel;
	imgSrc = imread("C:\\OpenCV3.1\\images\\lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	if (!imgSrc.data)
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}
	Mat dst;
	equalizeHist(imgSrc, imgDst);
	imshow("window1", imgSrc);
	imshow("window2", imgDst);
	waitKey(0);
	return 0;
}
