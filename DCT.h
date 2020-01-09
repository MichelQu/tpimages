#include <iostream>
#include <math.h>

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>



cv::Mat calcP()
/*
Cette fonction renvoie la matrice de coefficients P utile pour le calcul de la DCT.
P ne dépend que de la taille du bloc B, et sera donc constante dans notre application
puisque B est toujours de taille 8x8.
*/
{
	cv::Mat P = cv::Mat(8, 8, CV_32FC1);
	// TODO
	return P;
};

cv::Mat DCT(cv::Mat B, cv::Mat P)
/*
Cette fonction renvoie la matrice F = P'BP, DCT du bloc 8x8 B.
Paramètres : le bloc B à transformer et la matrice P de coefficients
*/
{
	cv::Mat F = cv::Mat(8, 8, CV_32FC3);
	// TODO
	return F;
};