// Le main qui déchire tout

#include <Windows.h>
#include <opencv2/core/mat.hpp>

#include "CodageRLC.h"
#include "DCT.h"

using namespace std;
using namespace cv;

int main (int argc, char* argv[]){
	// On charge l'image
	vector< vector<Mat> > matriceImage; // = lectureImage();

	// On calcule les dimensions de l'image
	int lenght = matriceImage.size();
	int height = matriceImage[0].size();

	// On lit linéairement cette chose
	for (int i=0 ; i<lenght; i++){
		for (int j=0 ; j<height; i++){
			DCT(matriceImage[i][j], calcP() );
			// quantif();
			codageRLC();
		}
	}
	return 0;
}