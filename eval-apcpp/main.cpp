#include <iostream>
#include <vector>

#include "Matrix.h"
Matrix mat;

int main(int, char**) {
    Matrix A({{1., 0.}, {0., 1.}}), B({{0., 1.}, {1., 0.,}});
    Matrix C = A.somme_matrice(B, false), D = A.produit_matrice(B, false);
    std::cout << D.get_coefs()[0][0] << D.get_coefs()[0][1] << D.get_coefs()[1][0] << D.get_coefs()[1][1];
}