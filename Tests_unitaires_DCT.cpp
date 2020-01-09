#include "DCT.h"
#define BOOST_TEST_MODULE my_test
#include <boost/test/included/unit_test.hpp>

using namespace std;
using namespace cv;



BOOST_AUTO_TEST_CASE(first_test)
{
	// Définition B pour le test
	Mat B = Mat::eye(8, 8, CV_32FC3);
	// Calcul de P
	Mat P = calcP();
	// Détermination de F
	Mat F;
	F = DCT(B, P);

	// Vérification de la décompression : la matrice B issues de la compression puis décompression 
	// doit être suffisamment similaire à la matrice B originelle
	Mat B2 = inverseDCT(F, P);
	double mini, maxi;
	double eps = 0.001;
	minMaxLoc(B-B2, &mini, &maxi);
	BOOST_CHECK(max(abs(mini), abs(maxi)) < eps);
}