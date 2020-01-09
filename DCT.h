#include <iostream>
#include <math.h>

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>



cv::Mat calcP()
{
	cv::Mat P = cv::Mat(8, 8, CV_32FC1);
	// TODO
	return P;
};

cv::Mat DTC(cv::Mat B, cv::Mat P)
{
	cv::Mat F = cv::Mat(8, 8, CV_32FC3);
	// TODO
	return F;
};