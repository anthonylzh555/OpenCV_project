// AdjContrastDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;
const int threshSliderMax = 255;
int alpha = 22, beta = 40;
Mat imgSrc;
Mat imgDst;
void OnTrackBar(int v1, void* v2)
{
	double _alpha = (double)alpha / 10.0;
	imgSrc.convertTo(imgDst, -1, _alpha, beta);
	imshow("imgDst", imgDst);
}
int main()
{
	imgSrc = imread("C:\\OpenCV3.1\\images\\lena.jpg", CV_LOAD_IMAGE_UNCHANGED);
	if (imgSrc.empty())
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}
	imgSrc.convertTo(imgDst, -1, (double)alpha / 10.0, beta);
	namedWindow("imgSrc", WINDOW_AUTOSIZE);
	namedWindow("imgDst", WINDOW_AUTOSIZE);
	imshow("imgSrc", imgSrc);
	imshow("imgDst", imgDst);

	createTrackbar("alpha", "imgSrc", &alpha,
		100, OnTrackBar);
	createTrackbar("beta", "imgSrc", &beta,
		100, OnTrackBar);
	waitKey(0);
	return 0;
}

