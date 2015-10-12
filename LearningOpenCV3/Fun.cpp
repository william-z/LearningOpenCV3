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
	int cols = mat.cols;

	if (mat.isContinuous()) {
		cols = cols * rows;
		rows = 1;
	}

	int n = static_cast<int>(log2(div));

	uchar mask = 0xff << n;

	for (int i = 0; i < rows; i++) {
		uchar *row_data = mat.ptr<uchar>(i);

		for (int j = 0; j < cols; j++) {
			*row_data++ = *row_data&mask + div / 2;
			*row_data++ = *row_data&mask + div / 2;
			*row_data++ = *row_data&mask + div / 2;
		}
	}
}

void Fun::Sharpen(cv::Mat &image, cv::Mat &result)
{
	result.create(image.size(), image.type());

	for (int i = 1; i < image.rows - 1; i++) {
		const cv::Vec3b *last = image.ptr<const cv::Vec3b>(i - 1);
		const cv::Vec3b *current = image.ptr<const cv::Vec3b>(i);
		const cv::Vec3b *next = image.ptr<const cv::Vec3b>(i + 1);

		cv::Vec3b *output = result.ptr<cv::Vec3b>(i);

		for (int j = 1; j < image.cols - 1; j++, output++) {
			(*output)[0] = cv::saturate_cast<uchar>(5 * current[j][0] - current[j - 1][0] - current[j + 1][0] - last[j][0] - next[j][0]);
			(*output)[1] = cv::saturate_cast<uchar>(5 * current[j][1] - current[j - 1][1] - current[j + 1][1] - last[j][0] - next[j][1]);
			(*output)[2] = cv::saturate_cast<uchar>(5 * current[j][2] - current[j - 1][2] - current[j + 1][2] - last[j][2] - next[j][2]);
		}

		result.row(0).setTo(cv::Scalar(0));
		result.row(result.rows - 1).setTo(cv::Scalar(0));
		result.col(0).setTo(cv::Scalar(0));
		result.col(result.cols - 1).setTo(cv::Scalar(0));
	}
}

void Fun::Sharpen2D(cv::Mat &image, cv::Mat &result)
{
	cv::Mat kernel(3, 3, CV_32F, cv::Scalar(0));
	kernel.at<float>(1, 1) = 5;
	kernel.at<float>(0, 1) = -1;
	kernel.at<float>(2, 1) = -1;
	kernel.at<float>(1, 0) = -1;
	kernel.at<float>(1, 2) = -1;

	cv::filter2D(image, result, image.depth(), kernel);

}