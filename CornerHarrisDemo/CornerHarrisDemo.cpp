// CornerHarrisDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;
int main()
{
	Mat imgSrc;
	imgSrc = imread("C:\\OpenCV3.1\\images\\right03.jpg");
	if (!imgSrc.data)
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}

	Mat imgG;
	cvtColor(imgSrc, imgG, COLOR_BGR2GRAY);
	Mat harrisStrength;
	int blockSize = 3;
	int kernelSize = 3;
	double k = 0.01;   // 0, 0.01, 0.1
	cornerHarris(imgG, harrisStrength, blockSize, kernelSize, k);
	Mat corners;
	double thresh = 0.003;
	threshold(harrisStrength, corners, thresh, 255, THRESH_BINARY);
	Mat normMat;
	normalize(harrisStrength, normMat, 255);

	imshow("figure1", imgSrc);
	imshow("threshold", corners);
	imshow("harrisStrength", normMat);
	waitKey(0);
	return 0;
}