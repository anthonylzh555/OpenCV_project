// LoadImg.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("C:\\OpenCV3.1\\images\\lena.jpg");
	if (!img.data)
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}
	namedWindow("figure1", WINDOW_AUTOSIZE);
	imshow("figure1", img);
	//flip(img, img, 0);
	//imwrite("test.jpg", img);

	waitKey(0);
    return 0;
}

