#pragma once

#include "opencv2\core.hpp"
#include <string>

using namespace std;
using namespace cv;

/// Return compressed value for a 8x8 bloc
string CodageRLC (Mat bloc);

/// Return 8x8 decompressed bloc from data file
Mat DecodageRLC (string input_data);