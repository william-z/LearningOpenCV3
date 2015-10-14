#ifndef __FUN_H__
#define __FUN_H__

#include <opencv2/imgproc/imgproc.hpp>

class Fun
{
public:
	static void Salt(cv::Mat &mat, int salt_num);
	static void ReduceColor(cv::Mat &mat, int div = 64);
	static void Sharpen(cv::Mat &image, cv::Mat &result);
	static void Sharpen2D(cv::Mat &image, cv::Mat &result);
	static void Histogram(cv::Mat &image, cv::Mat &hist_img);
	static void Lookup(cv::Mat &image, cv::Mat &result);
};



#endif