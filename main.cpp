//
//  main.cpp
//  VSION-TP1
//
//  Created by Jean-Marie Normand on 04/02/2016.
//  Copyright © 2016 Jean-Marie Normand. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <opencv/cv.hpp>

// no idea why on the virtual box the keycode is completely wrong
#define ESC_KEY 27 // would be 1048603 on the virtual box
#define Q_KEY  113 // would be 1048689 on the virtual box

using namespace std;
using namespace cv;

string videoName;
VideoCapture cap;
int nbFrames;
double fps = 30;
bool videoRead = false;

Mat im;
Mat imGray;
Mat route;
Mat mask;
Mat mask_op;
Mat mask_close;
vector<Mat> vect;
vector<Mat> vectGray;
Mat ones_op(2,2,CV_8U);
Mat ones_close(4,4,CV_8U);


Mat calcul_img_moyenne(vector<Mat> & v, int M_i) {
	float M = (float) M_i;
	Mat img_moy = Mat::zeros(v.at(0).rows, v.at(0).cols, CV_32F);

	// Pour chaque image
	for (int i=0; i<M_i; i++) {
		// Parcours sur la ligne
		Mat im = v.at(i).clone();
		for(int r=0; r<im.rows; r++) {
			// Parcours sur la colonne
			for(int c=0; c<im.cols; c++) {
				float increment = (1/M) * im.at<uchar>(r,c) / 255.f ;
				img_moy.at<float>(r,c) += increment;
			}
		}
	}

	// Convertion en matrice de uchar
	//img_moy.convertTo(img_moy,CV_8U);
	return img_moy;
}

Mat calcul_route(vector<Mat> & v, int M_i, Mat moy){
	mask = Mat::zeros(moy.rows, moy.cols, CV_8U);
	// Pour chaque image
	for (int i=0; i<M_i; i++) {
		Mat im = v.at(i).clone();
		// Parcours sur la ligne
		for(int r=0; r<im.rows; r++) {
				// Parcours sur la colonne
			for(int c=0; c<im.cols; c++) {
				if (abs((int) im.at<uchar>(r,c) - (int) (moy.at<float>(r,c)*255.f))>80){
					mask.at<uchar>(r,c) = 255;
				}
			}
		}
		morphologyEx(mask,mask_op,MORPH_OPEN,ones_op);
	}

	// Convertion en matrice de uchar
	return mask_op;
}

Mat calcul_voiture(vector<Mat> & v, int M_i, Mat moy){
	mask = Mat::zeros(moy.rows, moy.cols, CV_8U);
	// Pour chaque image
	//for (int i=0; i<M_i; i++) {
	Mat im = v.at(0).clone();
		// Parcours sur la ligne
	for(int r=0; r<im.rows; r++) {
				// Parcours sur la colonne
		for(int c=0; c<im.cols; c++) {
			if (abs((int) im.at<uchar>(r,c) - (int) (moy.at<float>(r,c)*255.f))>80){
				mask.at<uchar>(r,c) = 255;
			}
		}
	}
	morphologyEx(mask,mask_close,MORPH_CLOSE,ones_close);
	morphologyEx(mask_close,mask_op,MORPH_OPEN,ones_op);
	//}

	// Convertion en matrice de uchar
	return mask_op;
}


int main(int argc, const char * argv[]) {
   
	if(argc > 1) {
		videoName = argv[1];
		cout <<"video name: "<<videoName<<endl;
	}
	else {
		videoName = "C:/Users/eleve/Documents/Vision/TP2/TP2/video.avi";
	}


	// Reading the image (and forcing it to grayscale)	   
	cap.open(videoName);
	
	
	int N = (int) cap.get(CV_CAP_PROP_FRAME_COUNT);
   // Making sure the capture has opened successfully
	if(cap.isOpened()){
		//On met tout dans un vecteur
		for (int i = 0; i<N; i++){
			cap.read(im);
			vect.push_back(im.clone());
			// Turning im into grayscale and storing it in imGray
			cvtColor(im, imGray, CV_RGB2GRAY);
			vectGray.push_back(imGray.clone());
		}
    }
	else {
      // capture opening has failed we cannot do anything :'(
		return 1;
	}

	
	//Fond de la video : calcul de la moyenne
	Mat imMoyenne;
	imMoyenne = calcul_img_moyenne(vectGray, N);

	//Detection de la route
	Mat mask;
	mask = calcul_voiture(vectGray, N, imMoyenne);
	vectGray.at(0).copyTo(route,mask);

	//Detection des formes connexes
	/*
	// On supppose que ’img’ est une image binaire
	Mat testCC(route.size(), CV_32S);
	// on compte le nombre de composantes connexes
	int nLabels = connectedComponents(route, testCC, 8);
	// Les lignes suivantes sont pour l’affichage de ces composantes connexes !
	vector<Vec3b> colors(nLabels);
	colors[0] = Vec3b(0, 0, 0);
	//background color
	// on genere des couleurs aleatoires
	for (int label = 1; label < nLabels; ++label) {
		colors[label] = Vec3b((rand() & 255), (rand() & 255), (rand() & 255));
	}
	// on affiche dans l’image ’dstCC’ les composantes connexes en couleur
	Mat dstCC(route.size(), CV_8UC3);
	for (int r = 0; r < dstCC.rows; ++r) {
		for (int c = 0; c < dstCC.cols; ++c) {
			int label = testCC.at<int>(r, c);
			Vec3b &pixel = dstCC.at<Vec3b>(r, c);
			pixel = colors[label];
		}
	}
	// on affiche l’image resultat
	imshow("Connected comps", dstCC );
	cout << nLabels << endl;*/

	
	imshow("Application du masque", route);

	// On suppose l’image ’img’ etant une image binaire
	// L’image ’output’ sera utilisee pour le dessin des contours
	cv::Mat output = cv::Mat::zeros(route.size(), CV_8UC3);
	/// Find contours
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	RNG rng(12345);
	// detection de contours dans ’img’
	findContours( route, contours, hierarchy,CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	// Draw contours
	Mat drawing = Mat::zeros( route.size(), CV_32FC3 );
	for( int i = 0; i< contours.size(); i++ ){
		Scalar color = Scalar( rng.uniform(0,255), rng.uniform(0,255), rng.uniform(0,255) );
		cout<<color[0]<<","<<color[1]<<","<<color[2]<<endl;
		drawContours(output, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point());
	}


	// Creating a window to display some images
	//namedWindow("Original video");
	//namedWindow("Gray video moyenne");
	namedWindow("Gray video");
	namedWindow("Masque");
	namedWindow("Application du masque");
	
	//imshow("Original video", vect[0]);
	//imshow("Gray video moyenne", imMoyenne);
	imshow("Gray video", vectGray.at(0));
	imshow("Masque", mask);
	imshow("Contours", route);

	
	// Waiting for the user to press ESCAPE before exiting the application	
   int key = 0;
   while ( (key != ESC_KEY) && (key!= Q_KEY) ) {
      // Look for waitKey documentation
      // TODO put something in the waitkey function!
		key = waitKey(); // video is XXfps
	}
   
	return 0;
}