// KmeansColorDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
#include <math.h>


using namespace cv;
using namespace std;

Mat imgSrc, imgDst;

int main()
{
	int clusterCount = 5;    // 分群數
	imgSrc = imread("C:\\OpenCV3.1\\images\\opencv.png");
	//imgSrc = imread("C:\\OpenCV3.1\\images\\pic7.png");
	//Mat samples(imgSrc.cols*imgSrc.rows, 1, CV_32FC3); 
	Mat labels(imgSrc.cols*imgSrc.rows, 1, CV_32SC1);  // integer
	uchar* p;
	int i, j, k = 0;

	Mat samples;
	imgSrc.reshape(3, imgSrc.cols*imgSrc.rows).copyTo(samples);
	samples.convertTo(samples, CV_32FC3, 1.0 / 255.0, 0.0);
	cout << "samples dims = " << samples.size() << endl;
	cout << "samples type = " << samples.type() << endl;

	//fs << "samples" << samples;
	Mat centers(clusterCount, 1, samples.type());
	kmeans(samples, clusterCount, labels,
		TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 1000, 1.0e-3),
		3, KMEANS_PP_CENTERS, centers);

	waitKey(0);
	imgDst = Mat(imgSrc.rows, imgSrc.cols, CV_8UC1);
	float step = 255 / (clusterCount - 1);
	k = 0;
	for (i = 0; i < imgDst.rows; i++)
	{
		p = imgDst.ptr<uchar>(i);
		for (j = 0; j< imgDst.cols; j++)
		{
			int tt = labels.at<int>(k, 0);
			k++;
			p[j] = tt * step;
		}
	}
	namedWindow("Source image");
	namedWindow("K-means image");
	imshow("Source image", imgSrc);
	imshow("K-means image", imgDst);
	waitKey(0);
	return 0;
}
