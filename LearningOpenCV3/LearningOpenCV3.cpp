// LearningOpenCV3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Fun.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

using namespace cv;
using namespace std;

#define forever for(;;)

int main(int argc, char** argv)
{
	if (argc < 2) return -1;

	if (argc == 2) {	// example commandline: edges
		if (strcmp(argv[1], "edges") == 0) {
			VideoCapture cap(0);
			if (!cap.isOpened()) return -1;

			Mat frame, edges;
			namedWindow("edges");
			forever{
				cap >> frame;
				cvtColor(frame, edges, CV_BGR2GRAY);
				GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
				Canny(edges, edges, 0, 30, 3);
				imshow("edges", edges);
				if (waitKey(30) >= 0) break;
			}

			return 0;
		}
	}

	if (argc == 3) {
		if (strcmp(argv[1], "salt") == 0) {
			Mat in = imread(argv[2]);

			for (int i = 0; i < 1024; i++) {
				Fun::Salt(in, i);
				namedWindow("salt");
				imshow("salt", in);
				waitKey(1);
			}

			waitKey();
		}

		if (strcmp(argv[1], "reduce") == 0) {
			Mat in = imread(argv[2]);
			namedWindow("in");
			imshow("in", in);

			namedWindow("out");
			Fun::ReduceColor(in);
			imshow("out", in);

			waitKey();
		}

		if (strcmp(argv[1], "sharpen") == 0) {
			Mat in = imread(argv[2]);
			namedWindow("in");
			imshow("in", in);

			Mat out;

			namedWindow("out");
			double duration;
			duration = static_cast<double>(cv::getTickCount());

			Fun::Sharpen(in, out);

			duration = static_cast<double>(cv::getTickCount()) - duration;
			duration /= cv::getTickFrequency(); // the elapsed time in s
			cout << "take " << duration*1000 << "ms" << endl;

			imshow("out", out);

			waitKey();
		}

		if (strcmp(argv[1], "sharpen2d") == 0) {
			Mat in = imread(argv[2]);
			namedWindow("in");
			imshow("in", in);

			Mat out;

			namedWindow("out");
			double duration;
			duration = static_cast<double>(cv::getTickCount());

			Fun::Sharpen2D(in, out);

			duration = static_cast<double>(cv::getTickCount()) - duration;
			duration /= cv::getTickFrequency(); // the elapsed time in s
			cout << "take " << duration * 1000 << "ms" << endl;

			imshow("out", out);

			waitKey();
		}

		if (strcmp(argv[1], "split") == 0) {
			Mat in = imread(argv[2]);
			namedWindow("in");
			imshow("in", in);

			Mat out;

			namedWindow("outB");
			double duration;
			duration = static_cast<double>(cv::getTickCount());

			std::vector<cv::Mat> planes;
			cv::split(in, planes);

			duration = static_cast<double>(cv::getTickCount()) - duration;
			duration /= cv::getTickFrequency(); // the elapsed time in s
			cout << "take " << duration * 1000 << "ms" << endl;

			imshow("outB", planes[0]);

			namedWindow("outG");
			imshow("outG", planes[1]);

			namedWindow("outR");
			imshow("outR", planes[2]);
			waitKey();
		}

		if (strcmp(argv[1], "hist") == 0) {
			Mat in = imread(argv[2]);
			namedWindow("in");
			imshow("in", in);

			Mat hist_img;
			Fun::Histogram(in, hist_img);

			namedWindow("Histogram");
			imshow("Histogram", hist_img);
			waitKey();
		}
	}

	if (argc == 7) {  //example commandline: "C:\Users\Public\Pictures\Sample Pictures\Penguins.jpg" 50 50 200 200 200

		try {
			Mat src = imread(argv[1]);
			int x = atoi(argv[2]);
			int y = atoi(argv[3]);
			int width = atoi(argv[4]);
			int height = atoi(argv[5]);
			int add = atoi(argv[6]);

			Rect roi(x, y, width, height);

			Mat src_roi = src(roi);

			cv::add(src_roi, cv::Scalar(add), src_roi);

			namedWindow("Roi_add");
			imshow("Roi_add", src);

			waitKey();
		}
		catch (cv::Exception& e)
		{
			const char* err_msg = e.what();
			std::cout << "exception caught: " << err_msg << std::endl;
		}
	}

	return 0;
}


