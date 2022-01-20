#include<vector>
#include<cassert>
#include<string>
#include<fstream>
#include<iostream>

#include "Matrixcreuse.h"
#include "math.h"
#include "Matrix.h"

using namespace std;

//constructors
Matrixcreuse::Matrixcreuse()
{
    int _nombrecoefs;
    vector<int> _indicesli;
    vector<int> _indicescol;
    vector<double> _coefs;
}

Matrixcreuse::Matrixcreuse(const Matrix& A)
{
    int nombrecoefs=0;
    vector<int> indicesli;
    vector<int> indicescol;
    vector<double> coefs;

    for (int i = 0; i < A.get_size()[0]; i++)
    {
        for (int j = 0; j < A.get_size()[1]; j++)
        {
            if (A.get_coef(i, j) != 0.)
            {
                coefs.push_back(A.get_coef(i, j));
                indicesli.push_back(i);
                indicescol.push_back(j);
                nombrecoefs += 1;
            }
        }
    }

    _nombrecoefs = nombrecoefs;
    _indicesli = indicesli;
    _indicescol = indicescol;
    _coefs = coefs;
}

//opérations

Matrix Matrixcreuse::operator*(const Matrix& X) const
{
    if (X.get_size()[1] != 1)
    {
        cout << "L'argument n'est pas un vecteur" << X.get_size()[0] << ',' << X.get_size()[1];
        exit(EXIT_FAILURE);
    }

    Matrix A(X.get_size()[0], 1, 0.);
    for (int i = 0; i < _nombrecoefs; i++)
    {
        double coef = A.get_coef(_indicesli[i], 0) + _coefs[i] * X.get_coef(_indicescol[i], 0);
        A.set_coef(coef, _indicesli[i], 0);
    }

    return A;
}
