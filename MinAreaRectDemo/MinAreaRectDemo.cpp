// MinAreaRectDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
#include <math.h>


using namespace cv;
using namespace std;

Mat imgSrc, imgG, imgBW, imgEdge, imgContour, imgLine, imgCircle, imgElipse, imgRect, imgRotRect, imgConvex;
const int theshSliderMax = 255;
int threshSlider = 90;

const Scalar blueColor(255, 0, 0), greenColor(0, 255, 0), redColor(0, 0, 255), yellowColor(0, 255, 255), pinkColor(230, 130, 255);
const Scalar blackColor(0, 0, 0), whiteColor(255, 255, 255), lightBlueColor(255, 255, 160);
int lineWidth = 1;
void on_trackbar(int v1, void* v2)
{

	// Detect blobs
	if (imgSrc.channels() == 3)
		cvtColor(imgSrc, imgG, CV_BGR2GRAY);
	else
		imgSrc.copyTo(imgG);
	blur(imgG, imgG, Size(3, 3));
	threshold(imgG, imgBW, threshSlider, theshSliderMax, THRESH_BINARY);
	//threshold(imgG, imgBW, threshSlider, theshSliderMax, THRESH_BINARY_INV);
	imgBW.copyTo(imgEdge);
	imgSrc.copyTo(imgContour);
	imgSrc.copyTo(imgLine);
	imgSrc.copyTo(imgCircle);
	imgSrc.copyTo(imgElipse);
	imgSrc.copyTo(imgRect);
	imgSrc.copyTo(imgRotRect);
	imgSrc.copyTo(imgConvex);

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(imgBW, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	//findContours(imgEdge, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	/// Find the rotated rectangles and ellipses for each contour
	vector<RotatedRect> minRect(contours.size());
	vector<RotatedRect> minEllipse(contours.size());
	Point2f iCenter;
	float iRadius;
	Vec4f fitLines;
	vector<vector<Point>> hull(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		minRect[i] = minAreaRect(Mat(contours[i]));
		convexHull(Mat(contours[i]), hull[i], false);
		minEnclosingCircle(Mat(contours[i]), iCenter, iRadius);

		fitLine(Mat(contours[i]), fitLines, DistanceTypes::DIST_L2, 0, 0.01, 0.01);
		int cx = fitLines[2];
		int cy = fitLines[3];
		int x0 = cx - iRadius * fitLines[0];
		int y0 = cy - iRadius * fitLines[1];
		int x1 = cx + iRadius * fitLines[0];
		int y1 = cy + iRadius * fitLines[1];
		circle(imgLine, Point(cx, cy), 4, greenColor, -1);
		circle(imgLine, Point(x0, y0), 4, greenColor, -1);
		circle(imgLine, Point(x1, y1), 4, greenColor, -1);
		line(imgLine, Point(x0, y0), Point(x1, y1), redColor, 2, 8);
		drawContours(imgConvex, hull, i, redColor, 2, 8, vector<Vec4i>(), 0, Point());
		if (contours[i].size() > 5)
		{
			minEllipse[i] = fitEllipse(Mat(contours[i]));

		}
	}

	/// Draw contours + rotated rects + ellipses
	//Mat drawing = Mat::zeros(imgBW.size(), CV_8UC3);
	cout << "-------------------" << endl;
	char label[50];
	for (int i = 0; i< contours.size(); i++)
	{

		// contour
		drawContours(imgContour, contours, i, blueColor, 2, 8, vector<Vec4i>(), 0, Point());

		minEnclosingCircle(Mat(contours[i]), iCenter, iRadius);
		circle(imgCircle, iCenter, iRadius, redColor, 2, LineTypes::LINE_8);

		// 繪製 inclosing ellipse
		ellipse(imgElipse, minEllipse[i], redColor, 2, LineTypes::LINE_8);

		// 繪製 inclosing rectangle
		rectangle(imgRect, minRect[i].boundingRect(), redColor, 2, LineTypes::LINE_8);




		// 取得rotated rectangle頂點座標
		Point2f rect_points[4];
		minRect[i].points(rect_points);
		for (int j = 0; j < 4; j++)
			line(imgRotRect, rect_points[j], rect_points[(j + 1) % 4], redColor, 2, LineTypes::LINE_8);
		cout << "# " << i << ", (" << round(minEllipse[i].center.x) << ", " << round(minEllipse[i].center.y) << ")";
		cout << ", width = " << minEllipse[i].size.width << ", height = " << minEllipse[i].size.height;
		cout << ", area = " << minEllipse[i].size.height*minEllipse[i].size.width;
		cout << ", angle = " << round(minEllipse[i].angle) << endl;
		sprintf_s(label, "#%d,%.0f'", i, minEllipse[i].angle);
		putText(imgContour, label, Point(minEllipse[i].center.x - 10, minEllipse[i].center.y), FONT_HERSHEY_PLAIN, 1.0, redColor, 1, 8);
	}
	//imshow("imgG", imgG);
	imshow("imgBW", imgBW);
	imshow("MinAreaRect", imgContour);
	imshow("fitting Line", imgLine);
	imshow("inclosing circle", imgCircle);
	imshow("inclosing elipse", imgElipse);
	imshow("inclosing rectangle", imgRect);
	imshow("rotated rectangle", imgRotRect);
	imshow("convex hull", imgConvex);
}
int main()
{

	imgSrc = imread("C:\\OpenCV3.1\\images\\blob8.jpg", CV_LOAD_IMAGE_UNCHANGED);
	//imgSrc = imread("C:\\OpenCV3.1\\images\\blob7.jpg", CV_LOAD_IMAGE_UNCHANGED);
	//imgSrc = imread("C:\\OpenCV3.1\\images\\blob6.jpg", CV_LOAD_IMAGE_UNCHANGED);
	//imgSrc = imread("C:\\OpenCV3.1\\images\\blob5.jpg", CV_LOAD_IMAGE_UNCHANGED);
	//imgSrc = imread("C:\\OpenCV3.1\\images\\blob4.jpg", CV_LOAD_IMAGE_UNCHANGED);
	//imgSrc = imread("C:\\OpenCV3.1\\images\\blob3.jpg", CV_LOAD_IMAGE_UNCHANGED);
	//imgSrc = imread("C:\\OpenCV3.1\\images\\blob1.jpg", CV_LOAD_IMAGE_UNCHANGED);

	//pyrDown(imgSrc, imgSrc);
	if (!imgSrc.data)
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}
	if (imgSrc.channels() == 3)
		cvtColor(imgSrc, imgG, CV_BGR2GRAY);
	else
		imgSrc.copyTo(imgG);
	blur(imgG, imgG, Size(3, 3));
	threshold(imgG, imgBW, threshSlider, theshSliderMax, 0);

	// Show blobs
	namedWindow("MinAreaRect");
	createTrackbar("Threshold ", "MinAreaRect", &threshSlider, 255, on_trackbar);

	waitKey(0);
	return 0;
}

