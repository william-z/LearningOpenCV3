#ifndef __FUN_H__
#define __FUN_H__

#include <opencv2/imgproc/imgproc.hpp>

class Fun
{
public:
	static void Salt(cv::Mat &mat, int salt_num);
};

#endif