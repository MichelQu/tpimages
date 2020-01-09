#include "init.h"

#define ESC_KEY 27 // should be 27
#define Q_KEY 	113 // should be 113

using namespace std;
using namespace cv;

vector<vector<Mat> > init(){
	// the OpenCV data structure storing the image
	Mat im;

	int key = 0;   
	vector<vector<Mat> > matriceCoupee; 

	// the (default) name of the image file
	String imName= "image.bmp";

	im = imread(imName);

	if(!im.data || im.empty() || (im.rows == 0)|| (im.cols == 0)) {
		cout << "Could not load image !" <<endl;
		cout << "Exiting now..." << endl;
		// return matriceCoupee;
	}
	
	Mat im2 = Mat::zeros(im.rows,im.cols,CV_32FC3);
	int moduloRow = im.rows%8;
	int moduloCol= im.cols%8;
	Mat imageBonFormat(im.rows+8-moduloRow, im.cols+8-moduloCol, CV_64F , 0);
	
	for (int i =0; i< im.rows-1;i++){
		for (int j=0; j< im.cols-1; j++){
			im2.at<Vec3f>(i,j)[0] = (float)(im.at<Vec3b>(i,j)[0])/255.0;
			im2.at<Vec3f>(i,j)[1] = (float)(im.at<Vec3b>(i,j)[1])/255.0;
			im2.at<Vec3f>(i,j)[2] = (float)(im.at<Vec3b>(i,j)[2])/255.0;
		}
	}

	//imageBonFormat.colRange(0,im.rows-1).rowRange(0,im.cols-1)=im;

	for (int i=0; i<im.rows/8-1;i++){
		Range debut(8*i,8*(i+1));

		Mat ligneImage(im2, debut, Range::all());

		std::vector<cv::Mat> matricesAjoutees;

		for (int j=0; j<im.cols/8-1;j++){
			Range debut2(8*j,8*(j+1));
			Mat uneLigneImage(ligneImage,Range::all(),debut2);
			matricesAjoutees.push_back(uneLigneImage);
			
		}
		matriceCoupee.push_back(matricesAjoutees);

	}
	while ( (key != ESC_KEY) && (key!= Q_KEY) ) {
		// Creating a window to display some images
		namedWindow("Original image");
		// Displaying the loaded image in the named window
		imshow("Original image", im2);
		key = waitKey();
	}
	return matriceCoupee;
}
