// LearningOpenCV3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

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


