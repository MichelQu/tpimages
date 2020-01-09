#include <opencv/cv.hpp>


using namespace cv;

Mat quantification(Mat m, int qualite); // m : matrice d'entrée (résultat de la transf discrete , qualite : facteur de qualité (entre 0 et 25) 
Mat dequantification(Mat m, int qualite); // m : matrice quantifiée , qualite : le même facteur que pour la quantification