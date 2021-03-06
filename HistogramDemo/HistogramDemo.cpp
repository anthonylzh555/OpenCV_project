// HistogramDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <iomanip>
using namespace cv;
using namespace std;

Mat imgSrc, imgHist;
Mat histB, histG, histR;
vector<Mat> bgrPlanes(3);
int numBins = 256;
float range[] = { 0, 256 };
const float* histRange = { range };
bool _uniform = true;
bool _accumulate = false;
int hist_w = 1024;
int hist_h = 512;
int hist_max = 256;
int bin_w = cvRound((double)hist_w / numBins);

int main()
{
	imgSrc = imread("C:\\OpenCV3.1\\images\\fruits.jpg");
	if (!imgSrc.data)
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}
	imshow("Color", imgSrc);

	// Split the image into different channels
	split(imgSrc, bgrPlanes);

	calcHist(&bgrPlanes[0], 1, 0, Mat(), histB, 1, &numBins, &histRange, true, false);
	calcHist(&bgrPlanes[1], 1, 0, Mat(), histG, 1, &numBins, &histRange, true, false);
	calcHist(&bgrPlanes[2], 1, 0, Mat(), histR, 1, &numBins, &histRange, true, false);

	normalize(histB, histB, 0, hist_max, NORM_MINMAX, -1, Mat());
	normalize(histG, histG, 0, hist_max, NORM_MINMAX, -1, Mat());
	normalize(histR, histR, 0, hist_max, NORM_MINMAX, -1, Mat());

	// Draw the histograms for B, G and R
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));



	/// Draw for each channel
	for (int i = 1; i < numBins; i++)
	{
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(histB.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(histB.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(histG.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(histG.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(histR.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(histR.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
	}

	/// Display
	namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE);
	imshow("calcHist Demo", histImage);
	cvWaitKey(0);
	return 0;
}
