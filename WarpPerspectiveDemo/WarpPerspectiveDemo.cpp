// WarpPerspectiveDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace cv;

Mat imgSrc, imgDst, imgMap1, imgMap2;
Point2f triSrc[4];
Point2f triDst[4];
int selInd;

int selIndMax = 3;
void onTrackbar(int v1, void* v2)
{
	cout << "selInd: " << selInd << endl;
}

void onMouseSrc(int Event, int x, int y, int flags, void* param) {
	switch (Event)
	{
	case CV_EVENT_LBUTTONDOWN:
		triSrc[selInd].x = x;
		triSrc[selInd].y = y;
		cout << "Src # " << selInd << endl;
		cout << "(x, y) = " << x << " ," << y << endl;
		break;
	case CV_EVENT_RBUTTONDOWN:
		Mat warpMap = getPerspectiveTransform(triSrc, triDst);
		warpPerspective(imgSrc, imgMap1, warpMap, imgMap1.size());
		imshow("Map Forward", imgMap1);
		cout << "右鍵點擊" << endl;
		break;
	}
}
void onMouseDst(int Event, int x, int y, int flags, void* param) {
	switch (Event)
	{
	case CV_EVENT_LBUTTONDOWN:
		triDst[selInd].x = x;
		triDst[selInd].y = y;
		cout << "Dst # " << selInd << endl;
		cout << "(x, y) = " << x << " ," << y << endl;
		//cout << "左鍵點擊" << endl;
		break;
	case CV_EVENT_RBUTTONDOWN:
		Mat warpMap = getAffineTransform(triDst, triSrc);
		warpAffine(imgDst, imgMap2, warpMap, imgMap2.size());
		imshow("Map Backward", imgMap2);
		cout << "右鍵點擊" << endl;
		break;
	}
}
int main()
{
	/*imgSrc = imread("C:\\OpenCV3.1\\images\\right03.jpg");
	imgDst = imread("C:\\OpenCV3.1\\images\\right04.jpg");*/
	/*imgSrc = imread("C:\\OpenCV3.1\\images\\right06.jpg");
	imgDst = imread("C:\\OpenCV\\images\\patternSmall.jpg");*/
	imgSrc = imread("C:\\OpenCV3.1\\images\\parkingLotOK.jpg");
	imgDst = imread("C:\\OpenCV3.1\\images\\parkingLotTopView.jpg");

	if (!imgSrc.data)
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}
	Mat imgMap1 = Mat::zeros(imgSrc.rows, imgSrc.cols, imgSrc.type());
	Mat imgMap2 = Mat::zeros(imgSrc.rows, imgSrc.cols, imgSrc.type());
	selInd = 0;

	namedWindow("Src", WINDOW_AUTOSIZE);
	namedWindow("Dst", WINDOW_AUTOSIZE);
	namedWindow("Setting", WINDOW_AUTOSIZE);
	createTrackbar("sel index  ", "Setting", &selInd, selIndMax, onTrackbar);

	imshow("Src", imgSrc);
	imshow("Dst", imgDst);
	setMouseCallback("Src", onMouseSrc, NULL);
	setMouseCallback("Dst", onMouseDst, NULL);
	waitKey(0);
	return 0;
}