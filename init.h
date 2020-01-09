#pragma once
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define ESC_KEY 27 // should be 27
#define Q_KEY 	113 // should be 113


using namespace std;
using namespace cv;

std::vector<std::vector<cv::Mat> > init();
