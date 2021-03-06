// RGB2GrayDemo.cpp : Defines the entry point for the console application.
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
	Mat img;
	img = imread("C:\\OpenCV3.1\\images\\lena.jpg");
	if (!img.data)
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}

	Mat imgG;
	cvtColor(img, imgG, COLOR_BGR2GRAY);

	namedWindow("figure1", WINDOW_NORMAL);
	namedWindow("figure2", WINDOW_NORMAL);

	imshow("figure1", img);
	imshow("figure2", imgG);
	waitKey(0);
	return 0;
}

