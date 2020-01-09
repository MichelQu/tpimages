


#include "../src/CodageRLC.h"
using namespace cv;
using namespace std;
#include <iostream>

//#include "unit_test.hpp"
//#define BOOST_AUTO_TEST_MODULE Test Codage
//
//BOOST_AUTO_TEST_CASE(test_compression) {
//	Mat oneMatrix = Mat::ones(8,8,CV_32S);
//	string ones_result;
//	ones_result += '#';
//	ones_result += 64;
//	ones_result += 1;
//
//	BOOST_CHECK_EQUAL(CodageRLC(oneMatrix), ones_result);
//}

/// Unable to launch boost, manual test
int main () {
	Mat oneMatrix = Mat::ones(8,8,CV_32S);
	string ones_result;
	ones_result += '#';
	int count = 64;
	ones_result += count;
	ones_result += 1;

	string result = CodageRLC(oneMatrix);
	cout << result << ", " << ones_result << endl;
	return 0;
}
