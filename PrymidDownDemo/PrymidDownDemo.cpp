// PrymidDownDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <iomanip>

using namespace cv;
using namespace std;


int main()
{
	Mat imgSrc;
	Mat imgDstDn, imgDstUp;

	imgSrc = imread("C:\\OpenCV3.1\\images\\lena.jpg");
	if (imgSrc.empty())
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}
	namedWindow("figure1", WINDOW_AUTOSIZE);
	imshow("figure1", imgSrc);
	pyrDown(imgSrc, imgDstDn);
	imshow("pyrDown", imgDstDn);
	pyrUp(imgDstDn, imgDstUp);
	imshow("pyrUp", imgDstUp);
	waitKey(0);
	return 0;
}