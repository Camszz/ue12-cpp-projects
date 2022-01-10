#ifndef RESOLUTION
#define RESOLUTION
#include"Matrix.h"

Matrix gradient_conjugue(Matrix A, Matrix b, Matrix x0, double epsilon = 0.01);
Matrix euler_explicite(Matrix T, Matrix K, double deltaT);

#endif // RESOLUTION