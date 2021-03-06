// MatchTemplateDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

void onMouse(int Event, int x, int y, int flags, void* param);
Point ROILeftTop(-1, -1);
Point ROIRightBot(-1, -1);
Mat imgSrc;
Mat imgCpy;
Mat imgROI;
Mat imgDst;
enum DrawMode { Clear, onDraw, DrawDone };
DrawMode statusDraw = Clear;
//--------------------------------
int match_method;
int max_Trackbar = 5;
void MatchingMethod(int, void*);

int main()
{
	imgSrc = imread("C:\\OpenCV3.1\\images\\board.jpg", CV_LOAD_IMAGE_UNCHANGED);

	namedWindow("image", WINDOW_AUTOSIZE);
	namedWindow("result", WINDOW_NORMAL);
	imshow("image", imgSrc);
	setMouseCallback("image", onMouse, NULL);
	const char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED                     ";
	createTrackbar(trackbar_label, "image", &match_method, max_Trackbar, MatchingMethod);
	//MatchingMethod(0, 0);

	while (true) {
		if (cvWaitKey(33) == 27) {
			break;
		}
	}
	return 0;
}

void onMouse(int Event, int x, int y, int flags, void* param) {
	switch (Event)
	{
	case CV_EVENT_MOUSEMOVE:
		ROIRightBot.x = x;
		ROIRightBot.y = y;
		break;
	case CV_EVENT_LBUTTONDOWN:
		ROILeftTop.x = x;
		ROILeftTop.y = y;
		ROIRightBot.x = -1;
		ROIRightBot.y = -1;
		statusDraw = onDraw;
		break;
	case CV_EVENT_RBUTTONDOWN:
		statusDraw = Clear;
		break;
	case CV_EVENT_LBUTTONUP:
		ROIRightBot.x = x;
		ROIRightBot.y = y;
		statusDraw = Clear;
		break;
	}

	if (statusDraw == onDraw && ROILeftTop.x != -1 && ROIRightBot.x != -1) {
		imgSrc.copyTo(imgCpy);
		rectangle(imgCpy, Rect(ROILeftTop, ROIRightBot), Scalar(255, 0, 0), 2);
		imshow("image", imgCpy);
	}
	if (Event == CV_EVENT_LBUTTONUP)
	{
		destroyWindow("ROI");
		try {
			cv::Rect ROI(ROILeftTop.x, ROILeftTop.y, ROIRightBot.x - ROILeftTop.x + 1, ROIRightBot.y - ROILeftTop.y + 1);
			imgSrc(ROI).copyTo(imgROI);
			imshow("ROI", imgROI);
		}
		catch (Exception exception)
		{
			cout << exception.msg << endl;
		}
	}

}
void MatchingMethod(int, void*)
{
	Mat img_display;
	imgSrc.copyTo(img_display);
	int result_cols = imgSrc.cols + imgROI.cols + 1;
	int result_rows = imgSrc.rows + imgROI.rows + 1;
	imgDst.create(result_rows, result_cols, CV_32FC1);
	matchTemplate(imgSrc, imgROI, imgDst, match_method);
	normalize(imgDst, imgDst, 0, 1, NORM_MINMAX, -1, Mat());
	double minVal; double maxVal; Point minLoc; Point maxLoc;
	Point matchLoc;
	minMaxLoc(imgDst, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
	if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
	{
		matchLoc = minLoc;
	}
	else
	{
		matchLoc = maxLoc;
	}
	rectangle(img_display, matchLoc, Point(matchLoc.x + imgROI.cols, matchLoc.y + imgROI.rows), Scalar(0, 0, 255), 2, 8, 0);
	rectangle(imgDst, matchLoc, Point(matchLoc.x + imgROI.cols, matchLoc.y + imgROI.rows), Scalar::all(0), 2, 8, 0);
	imshow("image", img_display);
	imshow("result", imgDst);
	return;
}
