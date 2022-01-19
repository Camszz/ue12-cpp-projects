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
    Matrixcreuse(const Matrix A);
    Matrixcreuse(int ncoefs, double fill = 0.);

    //opérations

    Matrix operator*(const Matrix X) const;

    //export_Matrix_creuse
    void WriteToFile(std::ofstream& out);
    void afficher();

    //getters
    std::vector<std::vector<double>> get_coefs() const;
    double get_coef(int i, int j) const;
    std::vector<int> get_size() const;
    double to_scalar() const; //si A est de taille 1x1, renvoie sa valeur comme un scalaire

    //setters
    void set_coefs(std::vector<std::vector<double>> coefs);
    void set_coef(double coef, int i, int j);


    private :


    protected :

    std::vector<double> _coefs;
    std::vector<int> _indicesli;
    std::vector<int> _indicescol;
    int _nombrecoefs;

};

#endif