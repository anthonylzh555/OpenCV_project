// MLPDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/ml.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;

int numTrainingPoints = 200;
int numTestPoints = 2000;
int iSize = 300;
int eq = 0;

// accuracy
float evaluate(const cv::Mat& predicted, const cv::Mat& actual) {
	assert(predicted.rows == actual.rows);
	int t = 0;
	int f = 0;
	for (int i = 0; i < actual.rows; i++) {
		float p = predicted.at<float>(i, 0);
		float a = actual.at<float>(i, 0);
		if ((p >= 0.0 && a >= 0.0) || (p <= 0.0 &&  a <= 0.0)) {
			t++;
		}
		else {
			f++;
		}
	}
	return (t * 1.0) / (t + f);
}
// plot data and class
void plot_binary(const Mat& data, const cv::Mat& classes, string name) {
	Mat plot(iSize, iSize, CV_8UC3);
	plot.setTo(cv::Scalar(255, 255, 255));
	for (int i = 0; i < data.rows; i++) {

		float x = data.at<float>(i, 0) * iSize;
		float y = data.at<float>(i, 1) * iSize;

		if (classes.at<float>(i, 0) > 0) {
			cv::circle(plot, Point(x, y), 2, CV_RGB(255, 0, 0), 1);
		}
		else {
			cv::circle(plot, Point(x, y), 2, CV_RGB(0, 0, 255), 1);
		}
	}
	cv::imshow(name, plot);
}
// function to learn
int f(float x, float y, int equation) {
	switch (equation) {
	case 0:
		return y > sin(x * 10) ? -1 : 1;
		break;
	case 1:
		return y > cos(x * 10) ? -1 : 1;
		break;
	case 2:
		return y > 2 * x ? -1 : 1;
		break;
	case 3:
		return y > tan(x * 10) ? -1 : 1;
		break;
	default:
		return y > cos(x * 10) ? -1 : 1;
	}
}
// label data with equation
cv::Mat labelData(cv::Mat points, int equation) {
	cv::Mat labels(points.rows, 1, CV_32FC1);
	for (int i = 0; i < points.rows; i++) {
		float x = points.at<float>(i, 0);
		float y = points.at<float>(i, 1);
		labels.at<float>(i, 0) = f(x, y, equation);
	}
	return labels;
}
void mlp(const Mat& trainingData, const Mat& trainingClasses, const Mat& testData, const Mat& testClasses) {
	const int LAYERS_NUM = 4;    //層數
	int layers[LAYERS_NUM] = { 2, 5, 5, 1 };                                //各層node數
	Mat layersMat = Mat(LAYERS_NUM, 1, CV_32SC1, layers);
	Ptr<ANN_MLP> mlp = ANN_MLP::create();
	mlp->setLayerSizes(layersMat);
	mlp->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 1000, 1e-6));               //TermCriteria迭代次數
	mlp->setTrainMethod(ANN_MLP::BACKPROP);
	mlp->setActivationFunction(ANN_MLP::SIGMOID_SYM);
	mlp->setBackpropWeightScale(0.05);                                    //加速收斂速度
	mlp->setBackpropMomentumScale(0.05);
	//mlp->train(trainingData, SampleTypes::ROW_SAMPLE, trainingClasses);
	if (!mlp->train(trainingData, SampleTypes::ROW_SAMPLE, trainingClasses))
		return;
	//cout << "\nweights[0]:\n" << mlp->getWeights(0) << endl;
	//cout << "\nweights[1]:\n" << mlp->getWeights(1) << endl;
	//cout << "\nweights[2]:\n" << mlp->getWeights(2) << endl;
	//cout << "\nweights[3]:\n" << mlp->getWeights(3) << endl;
	Mat response(1, 1, CV_32FC1);
	Mat predicted(testClasses.rows, 1, CV_32F);
	for (int i = 0; i < testData.rows; i++) {
		Mat sample = testData.row(i);
		mlp->predict(sample, response);
		//cout << "# " << i << " : " << sample << endl;
		cout << "(desired, predicted) = " << " (" << testClasses.row(i) << ", " << response << " )" << endl;
		predicted.at<float>(i, 0) = response.at<float>(0, 0);
	}

	cout << "Accuracy_{MLP} = " << evaluate(predicted, testClasses) << endl;
	plot_binary(testData, predicted, "Predictions Backpropagation");
}
int main()
{
	Mat trainingData(numTrainingPoints, 2, CV_32FC1);
	Mat testData(numTestPoints, 2, CV_32FC1);

	randu(trainingData, 0, 1);
	randu(testData, 0, 1);

	Mat trainingClasses = labelData(trainingData, eq);
	Mat testClasses = labelData(testData, eq);

	plot_binary(trainingData, trainingClasses, "Training Data");
	plot_binary(testData, testClasses, "Test Data");

	mlp(trainingData, trainingClasses, testData, testClasses);
	waitKey(0);
	return 0;
}
