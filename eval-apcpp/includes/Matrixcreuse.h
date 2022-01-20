#ifndef DEF_Matrixcreuse
#define DEF_Matrixcreuse
#pragma once

#include<vector>
#include<cassert>
#include<string>
#include<fstream>
#include<iostream>


#include "math.h"
#include "Matrix.h"

class Matrixcreuse
{
    public :

    //constructors
    Matrixcreuse();
    Matrixcreuse(const Matrix& A);

    //opérations

    Matrix operator*(const Matrix& X) const;


    private :


    protected :

    std::vector<double> _coefs;
    std::vector<int> _indicesli;
    std::vector<int> _indicescol;
    int _nombrecoefs;

};

#endif