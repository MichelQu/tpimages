#pragma once

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
	int N = 8;
	cv::Mat P = cv::Mat(N, N, CV_32FC1);
	for (int i=0; i<N; i++)
	{
		for (int j=0; j<N; j++)
		{
			if (j == 0)
			{
				P.at<float>(i,j) = (1.0 / sqrt(N)) * cos(((2*i + 1.0) * j * CV_PI) / ((float) 2 * N));
			}
			else
			{
				P.at<float>(i,j) = (sqrt(2.0 / N)) * cos(((2*i + 1.0) * j * CV_PI) / ((float) 2 * N));
			}
		}
	}
	return P;
};

cv::Mat DCT(cv::Mat B, cv::Mat P)
/*
Cette fonction renvoie la matrice F = P'BP, Discrete Cosine Transform du bloc 8x8 B.
Paramètres : le bloc B à transformer et la matrice P de coefficients
*/
{
	cv::Mat F = cv::Mat(8, 8, CV_32FC3);
	std::vector<cv::Mat> YIQ;
	split(B, YIQ); // On sépare les différents channels pour pouvoir multiplier par P
	
	for (int i=0; i<3; i++)
	{
		YIQ[i] = P.t() * YIQ[i] * P;
	}
	merge(YIQ, F); // On fusionne les différents channels pour reformer l'image RGB (ou plutôt YIQ)

	return F;
};

cv::Mat inverseDCT(cv::Mat F, cv::Mat P)
/*
Cette fonction renvoie la matrice B = PFP', en faisant la Discrete Cosine Transform inverse du bloc 8x8 B.
Paramètres : le bloc F à transformer et la matrice P de coefficients
*/
{
	cv::Mat B = cv::Mat(8, 8, CV_32FC3);
	std::vector<cv::Mat> YIQ;
	split(F, YIQ); // On sépare les différents channels pour pouvoir multiplier par P
	
	for (int i=0; i<3; i++)
	{
		YIQ[i] = P * YIQ[i] * P.t();
	}
	merge(YIQ, B); // On fusionne les différents channels pour reformer l'image RGB (ou plutôt YIQ)

	return B;
}