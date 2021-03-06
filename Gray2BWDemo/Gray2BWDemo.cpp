// Gray2BWDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

const int threshSliderMax = 255;
int threshSlider;
Mat img;
Mat imgG;
Mat imgBW;

void OnTrackBar(int v1, void* v2)
{
	threshold(imgG, imgBW, threshSlider, threshSliderMax, THRESH_OTSU);
	imshow("THRESH_OTSU", imgBW);
	//threshold(imgG, imgBW, threshSlider, threshSliderMax, THRESH_BINARY);
	//imshow("THRESH_BINARY", imgBW);
}

int main()
{
	img = imread("C:\\OpenCV3.1\\images\\adaptiveThreshold.png");
	pyrDown(img, img);
	//img = imread("C:\\OpenCV3.1\\images\\lena.jpg");
	if (!img.data)
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}
	namedWindow("figure1", WINDOW_AUTOSIZE);
	namedWindow("figure2", WINDOW_AUTOSIZE);

	imshow("figure1", img);
	//GaussianBlur(img, img, Size(11, 11), 0, 0);
	cvtColor(img, imgG, COLOR_BGR2GRAY);
	//blur(imgG, imgG, Size(3, 3));

	imshow("figure2", imgG);
	createTrackbar("Threshold", "figure2", &threshSlider,
		threshSliderMax, OnTrackBar);

	waitKey(0);
	return 0;
}

