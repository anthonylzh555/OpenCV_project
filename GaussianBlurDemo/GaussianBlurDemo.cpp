// GaussianBlurDemo.cpp : Defines the entry point for the console application.
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
	int i;
	Size kernelSize;
	double sigmaX = 3;
	double sigmaY = 3;
	int iteration = 20;
	Mat imgSrc, imgDst, kernel;
	imgSrc = imread("C:\\OpenCV3.1\\images\\rainbow.png");
	if (!imgSrc.data)
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}
	namedWindow("figure1", WINDOW_AUTOSIZE);
	namedWindow("figure2", WINDOW_AUTOSIZE);
	imshow("figure1", imgSrc);

	LARGE_INTEGER t1, t2, ts;
	QueryPerformanceFrequency(&ts);

	for (i = iteration; i >= 0; i--)
	{
		kernelSize = Size(2 * i + 1, 2 * i + 1);
		QueryPerformanceCounter(&t1);
		GaussianBlur(imgSrc, imgDst, kernelSize, sigmaX, sigmaY, BORDER_DEFAULT);
		QueryPerformanceCounter(&t2);

		cout << "#" << std::setw(2) << kernelSize
			<< ", Elapsed Time: "
			<< fixed
			<< std::setw(6)
			<< (t2.QuadPart - t1.QuadPart) / (double)(ts.QuadPart) << " secs" << endl;
		imshow("figure2", imgDst);
		waitKey(1000);
	}

	waitKey(0);
	return 0;
}
