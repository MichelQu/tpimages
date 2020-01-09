#include "DCT.h"

using namespace std;
using namespace cv;

int main(int argc, char * argv[])
{
	Mat P = calcP();
	Mat B = Mat::eye(8, 8, CV_32FC3);
	Mat F;
	F = DCT(B, P);
	cout << F << endl;
	int wait;
	cin >> wait;
	return EXIT_SUCCESS;
}
