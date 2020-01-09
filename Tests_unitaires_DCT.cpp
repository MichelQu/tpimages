#include "DCT.h"
#define BOOST_TEST_MODULE my_test
#include <boost/test/included/unit_test.hpp>

using namespace std;
using namespace cv;



BOOST_AUTO_TEST_CASE(first_test)
{
	// D�finition B pour le test
	Mat B = Mat::eye(8, 8, CV_32FC3);
	// Calcul de P
	Mat P = calcP();
	// D�termination de F
	Mat F;
	F = DCT(B, P);

	// V�rification de la d�compression : la matrice B issues de la compression puis d�compression 
	// doit �tre suffisamment similaire � la matrice B originelle
	Mat B2 = inverseDCT(F, P);
	double mini, maxi;
	double eps = 0.001;
	minMaxLoc(B-B2, &mini, &maxi);
	BOOST_CHECK(max(abs(mini), abs(maxi)) < eps);
}