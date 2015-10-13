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
};

class ColorHistogram
{
public:
	ColorHistogram() {
		m_hist_size[0] = m_hist_size[1] = m_hist_size[2] = 256;
		m_h_ranges[0] = 0.0;
		m_h_ranges[1] = 255.0;
		m_ranges[0] = m_h_ranges;
		m_ranges[1] = m_h_ranges;
		m_ranges[2] = m_h_ranges;
		m_channels[0] = 0;
		m_channels[1] = 1;
		m_channels[2] = 2;
	}

	cv::SparseMat GetSparseHistogram(const cv::Mat &image);

	cv::Mat GetSparseHistogramImage(const cv::Mat &image);

private:
	int m_hist_size[3];
	float m_h_ranges[2];
	const float *m_ranges[3];
	int m_channels[3];
};

#endif