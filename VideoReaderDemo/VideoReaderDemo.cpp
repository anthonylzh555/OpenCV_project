// VideoReaderDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>		
#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;
using namespace cv;
int main()
{
	LARGE_INTEGER t1, t2, ts;
	QueryPerformanceFrequency(&ts);


	//VideoCapture cap(0);
	VideoCapture cap("C:\\OpenCV3.1\\images\\contours and moments.mp4");
	if (!cap.isOpened())
	{
		cout << "無法開啟檔案" << endl;
		return -1;
	}
	double length = cap.get(CV_CAP_PROP_FRAME_COUNT);
	double width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	double height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	double fps = cap.get(CV_CAP_PROP_FPS);
	cout << "length = " << length << endl;
	cout << "width = " << width << endl;
	cout << "height = " << height << endl;
	cout << "fps = " << fps << endl;
	namedWindow("VideoCaptureDemo", WINDOW_AUTOSIZE);
	Mat frame, imgSmall;
	bool bSuccess;
	int imageCnt = 0;
	int frameCnt = 0;
	double fontScale = 1;
	char fileName[50];
	char label[20];
	double scale = 0.95;
	while (1)
	{
		QueryPerformanceCounter(&t1);
		bSuccess = cap.read(frame);
		if (frame.empty()) {
			break;
		}

		frameCnt++;
		QueryPerformanceCounter(&t2);
		sprintf_s(label, "frame #%d, %.5f secs", frameCnt, (t2.QuadPart - t1.QuadPart) / (double)(ts.QuadPart));
		resize(frame, imgSmall, Size(), scale, scale, CV_INTER_LINEAR);
		putText(imgSmall, label, CvPoint(10, 20), FONT_HERSHEY_COMPLEX_SMALL, fontScale, cvScalar(255, 0, 0));


		imshow("VideoCaptureDemo", imgSmall);

		switch (waitKey(1)) {
		case 27:       // ESC: 結束程式
			return 0;
		case 13:       // ENTER: 儲存相片
			sprintf_s(fileName, "videoFrame%d.jpg", ++imageCnt);
			imwrite(fileName, frame);
			break;
		}

	}

	return 0;
}