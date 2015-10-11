#include "stdafx.h"
#include "Fun.h"


void Fun::Salt(cv::Mat &mat, int salt_num)
{
	for (int i = 0; i < salt_num; i++) {
		int r = rand() % mat.rows;
		int c = rand() % mat.cols;

		if (mat.channels() == 1) {
			mat.at<uchar>(r, c) = 255;
		}
		else if (mat.channels() == 3) {
			mat.at<cv::Vec3b>(r, c)[0] = 255;
			mat.at<cv::Vec3b>(r, c)[1] = 255;
			mat.at<cv::Vec3b>(r, c)[2] = 255;
		}
	}
}

void Fun::ReduceColor(cv::Mat &mat, int div /*= 8*/)
{
	int rows = mat.rows;
	int cols = mat.cols * mat.channels();

	uchar mask = 0xff << div;

	for (int i = 0; i < rows; i++) {
		uchar *row_data = mat.ptr<uchar>(i);

		for (int j = 0; j < cols; j++) {
			row_data[j] = row_data[j]&mask + div/2;
		}
	}
}
