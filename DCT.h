#pragma once

#include <iostream>
#include <math.h>

// OpenCV
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

cv::Mat calcP();

cv::Mat DCT(cv::Mat B, cv::Mat P);

cv::Mat inverseDCT(cv::Mat F, cv::Mat P);