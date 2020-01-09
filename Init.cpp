#include "init.h"

using namespace std;
using namespace cv;

vector<vector<cv::Mat> > init(){
	// the OpenCV data structure storing the image
	Mat im;
	Mat im2;
	int key = 0;   
	vector<vector<cv::Mat> > matriceCoupee; 

	// the (default) name of the image file
	String imName= "image.bmp";

	im = imread(imName);

	if(!im.data || im.empty() || (im.rows == 0)|| (im.cols == 0)) {
		cout << "Could not load image !" <<endl;
		cout << "Exiting now..." << endl;
		return 1;
	}

	int moduloRow = im.rows%8;
	int moduloCol= im.cols%8;
	Mat imageBonFormat(im.rows+8-moduloRow, im.cols+8-moduloCol, CV_64F , 0);
	im.convertTo(im2,CV_64F);

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
