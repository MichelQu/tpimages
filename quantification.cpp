
#include <iostream>
#include <fstream>
#include <string>
#include <opencv/cv.hpp>

using namespace std;
using namespace cv;



Mat quantification(Mat m, int qualite){ // m : matrice d'entrée (résultat de la transf discrete , qualite : facteur de qualité (entre 0 et 25) 
	Mat sortie = Mat::zeros(8, 8, CV_32S);
	//Matrice de quantification
	Mat quantif = Mat::zeros(8, 8, CV_32F);

	// Parcours sur la ligne
	for(int r=0; r<8; r++) {
		// Parcours sur la colonne
		for(int c=0; c<8; c++) {
			quantif.at<float>(r,c) = 1 + (r+c+1)*qualite; //Remplissage de la matrice de quantification
			sortie.at<int>(r,c) = m.at<float>(r,c) / quantif.at<float>(r,c) ;
		}
	}
	return sortie;
}

Mat dequantification(Mat m, int qualite){ // m : matrice quantifiée , qualite : le même facteur que pour la quantification 
	Mat sortie = Mat::zeros(8, 8, CV_32S);
	//Matrice de quantification
	Mat quantif = Mat::zeros(8, 8, CV_32S);

	// Parcours sur la ligne
	for(int r=0; r<8; r++) {
		// Parcours sur la colonne
		for(int c=0; c<8; c++) {
			quantif.at<int>(r,c) = 1 + (r+c+1)*qualite; //Remplissage de la matrice de quantification
			sortie.at<int>(r,c) = m.at<int>(r,c) * quantif.at<int>(r,c) ;
		}
	}
	sortie.convertTo(sortie, CV_64FC1);
	return sortie;
}



