// DeskewDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat imgSrc, imgG, imgDst;
void Deskew(Mat img)
{
	cv::bitwise_not(img, img);
	imshow("bitwise not", img);
	std::vector<Point> points;
	Mat_<uchar>::iterator it = img.begin<uchar>();
	Mat_<uchar>::iterator end = img.end<uchar>();
	for (; it != end; ++it)
		if (*it)
			points.push_back(it.pos());
	RotatedRect box = minAreaRect(Mat(points));
	Point2f rect_points[4];
	//Rect rotated = box.boundingRect();
	box.points(rect_points);

	//rectangle(imgDst, box.boundingRect(), Scalar(255,0,0), 1, LineTypes::LINE_8);
	int angle = box.angle;
	if (angle < -45)
		angle += 90;
	Mat warpMat = getRotationMatrix2D(box.center, angle, 1);
	cv::Mat imgRotated;
	//Moments m = moments(img);
	//float skew = m.mu11 / m.mu02;
	cout << "angle = " << angle << endl;
	cout << warpMat << endl;
	cv::warpAffine(imgDst, imgRotated, warpMat, img.size(), cv::INTER_CUBIC);
	imshow("rotated image", imgRotated);

	cv::Size box_size = box.size;
	if (box.angle < -45.)
		std::swap(box_size.width, box_size.height);
	Mat cropped;
	getRectSubPix(imgRotated, box_size, box.center, cropped);
	imshow("cropped image", cropped);
}
int main()
{
	//int angle = -8;
	//imgSrc = imread("C:\\OpenCV3.1\\images\\deskew\\m8.jpg");
	//imgSrc = imread("C:\\OpenCV3.1\\images\\deskew\\m20.jpg");
	//imgSrc = imread("C:\\OpenCV3.1\\images\\deskew\\p3.jpg");
	imgSrc = imread("C:\\OpenCV3.1\\images\\deskew\\p16.jpg");
	//imgSrc = imread("C:\\OpenCV3.1\\images\\deskew\\p24.jpg");
	if (!imgSrc.data)
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}

	cvtColor(imgSrc, imgG, CV_BGR2GRAY);
	imgSrc.copyTo(imgDst);
	namedWindow("figure1", WINDOW_AUTOSIZE);
	imshow("figure1", imgSrc);

	Deskew(imgG);
	//imshow("result", imgDst);
	waitKey(0);
	return 0;
}