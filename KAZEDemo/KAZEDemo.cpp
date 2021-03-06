// KAZEDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
//#include "nonfree.hpp"

using namespace cv;
using namespace std;

Mat imgSrc1, imgSrc2, imgBlur1, imgBlur2, imgEdge1, imgEdge2, imgDst1, imgDst2, imgDst;
int blurKernelSize = 3;
int imgEdgeThresh1 = 30;
int imgEdgeThresh2 = 90;
int main()
{
	imgSrc1 = imread("C:\\OpenCV3.1\\images\\parkingLot.jpg");
	imgSrc2 = imread("C:\\OpenCV3.1\\images\\parkingLotOK.jpg");
	//imgSrc1 = imread("C:\\OpenCV3.1\\images\\tsukuba_l.png");
	//imgSrc2 = imread("C:\\OpenCV3.1\\images\\tsukuba_r.png");

	blur(imgSrc1, imgBlur1, Size(blurKernelSize, blurKernelSize));
	blur(imgSrc2, imgBlur2, Size(blurKernelSize, blurKernelSize));

	FeatureDetector detector;


	cv::Ptr<cv::Feature2D> pFeature = KAZE::create();

	vector<KeyPoint> kpts1, kpts2;

	cv::Mat descriptors1, descriptors2;
	pFeature->detectAndCompute(imgBlur1, cv::noArray(), kpts1, descriptors1);

	pFeature->detectAndCompute(imgBlur2, cv::noArray(), kpts2, descriptors2);

	drawKeypoints(imgSrc1, kpts1, imgDst1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	drawKeypoints(imgSrc2, kpts2, imgDst2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	imshow("Src1", imgDst1);
	imshow("Src2", imgDst2);

	BFMatcher matcher(NORM_L2);
	vector<DMatch> matches;

	matcher.match(descriptors1, descriptors2, matches);

	drawMatches(imgSrc1, kpts1, imgSrc2, kpts2, matches, imgDst);

	imshow("Result", imgDst);

	cvWaitKey(0);
	return 0;
}
