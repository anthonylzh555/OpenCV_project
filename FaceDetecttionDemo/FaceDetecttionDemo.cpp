// FaceDetecttionDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>	
#include <opencv2\objdetect.hpp>
#include <iostream>
#include <iomanip>
#include <windows.h>


using namespace std;
using namespace cv;
void detectAndDraw(Mat& img, CascadeClassifier& cascade, double scale);

string cascadeName;
string nestedCascadeName;

int main()
{

	CascadeClassifier cascade, nestedCascade;
	double scale = 2.0;
	cascadeName = "C:\\OpenCV3.1\\sources\\data\\haarcascades\\haarcascade_eye.xml";   ///frontalface_alt
	//------------------------------------
	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		cout << "無法啟動攝影機" << endl;
		return -1;
	}
	namedWindow("CaptureDemo", WINDOW_AUTOSIZE);
	Mat frame;
	bool bSuccess;
	int imageCnt = 0;
	int frameCnt = 0;

	char fileName[50];

	//-------------------------------
	if (!cascade.load(cascadeName))
	{
		cerr << "ERROR: Could not load classifier cascade" << endl;
		return -1;
	}

	for (;;)
	{

		bSuccess = cap.read(frame);
		//Mat frame1 = frame.clone();
		detectAndDraw(frame, cascade, scale);
		//waitKey(10);
		if (!bSuccess)
		{
			cout << "無法從攝影機讀取影格!" << endl;
		}
		frameCnt++;

		cv::imshow("CaptureDemo", frame);
		//
		switch (waitKey(100)) {
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

void detectAndDraw(Mat& img, CascadeClassifier& cascade, double scale)
{
	double fontScale = 1;
	char label[20];
	LARGE_INTEGER t1, t2, ts;
	QueryPerformanceFrequency(&ts);
	QueryPerformanceCounter(&t1);
	double t = 0;
	vector<Rect> faces;
	const static Scalar colors[] =
	{
		Scalar(255,0,0),
		Scalar(255,128,0),
		Scalar(255,255,0),
		Scalar(0,255,0),
		Scalar(0,128,255),
		Scalar(0,255,255),
		Scalar(0,0,255),
		Scalar(255,0,255)
	};
	Mat gray, smallImg;

	cvtColor(img, gray, COLOR_BGR2GRAY);
	double fx = 1 / scale;
	resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR);
	equalizeHist(smallImg, smallImg);
	imshow("smallImg", smallImg);

	cascade.detectMultiScale(smallImg, faces, 1.1, 2, CASCADE_SCALE_IMAGE, Size(30, 30));
	for (size_t i = 0; i < faces.size(); i++)
	{
		Rect r = faces[i];
		Mat smallImgROI;
		vector<Rect> nestedObjects;
		Point center;
		Scalar color = colors[i % 8];
		int radius;

		double aspect_ratio = (double)r.width / r.height;
		if (0.75 < aspect_ratio && aspect_ratio < 1.3)
		{
			center.x = cvRound((r.x + r.width*0.5)*scale);
			center.y = cvRound((r.y + r.height*0.5)*scale);
			radius = cvRound((r.width + r.height)*0.25*scale);
			circle(img, center, radius, color, 3, 8, 0);
		}
		else
			rectangle(img, cvPoint(cvRound(r.x*scale), cvRound(r.y*scale)),
				cvPoint(cvRound((r.x + r.width - 1)*scale), cvRound((r.y + r.height - 1)*scale)),
				color, 3, 8, 0);
	}
	QueryPerformanceCounter(&t2);
	sprintf_s(label, "%.5f secs", (t2.QuadPart - t1.QuadPart) / (double)(ts.QuadPart));
	putText(img, label, CvPoint(10, 20), FONT_HERSHEY_COMPLEX_SMALL, fontScale, cvScalar(255, 0, 0));
	cv::imshow("CaptureDemo", img);
}