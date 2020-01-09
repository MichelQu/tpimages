#include <opencv/cv.hpp>


using namespace cv;

Mat quantification(Mat m, int qualite); // m : matrice d'entr�e (r�sultat de la transf discrete , qualite : facteur de qualit� (entre 0 et 25) 
Mat dequantification(Mat m, int qualite); // m : matrice quantifi�e , qualite : le m�me facteur que pour la quantification