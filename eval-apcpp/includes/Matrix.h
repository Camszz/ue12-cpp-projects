#ifndef DEF_MATRIX
#define DEF_MATRIX
#pragma once

#include<vector>
#include<cassert>
#include<string>
#include<fstream>
#include<iostream>


#include "math.h"

class Matrix
{
    public :

    //constructors
    Matrix();
    Matrix(int n_lignes, int n_colonnes, double fill=0.);
    Matrix(int n, double fill = 1., bool diag = false);
    Matrix(std::vector<double> coefs, int nlignes, int ncolonnes);

    //opérations
    Matrix somme_matrice(const Matrix& A, bool inplace=false); //le paramètre inplace permet de définir si l'on modifie la matrice A d'origine
    Matrix difference_matrice(const Matrix& A, bool inplace=false);
    Matrix produit_matrice(const Matrix& A, bool inplace=false);
    Matrix produit_par_scalaire(double lambda, bool inplace=false);
    Matrix transpose(bool inplace=false);
    double norme(); //racine de la somme des coefs au carré

    Matrix operator+(const Matrix& A) const;
    Matrix operator*(const Matrix& A) const;
    Matrix operator-(const Matrix& A) const;
    
    Matrix operator/(double lambda) const;
    Matrix operator*(double lambda) const;

    Matrix switch_lines(int a, int b, bool inplace = false);
    Matrix switch_cols(int a, int b, bool inplace = false);

    //export_matrix
    void WriteToFile(std::ofstream& out);
    void afficher();

    //getters
    std::vector<double> get_coefs() const;
    double get_coef(int i, int j) const;
    std::vector<int> get_size() const;
    double to_scalar() const; //si A est de taille 1x1, renvoie sa valeur comme un scalaire

    //setters
    void set_coefs(std::vector<double> coefs);
    void set_coef(const double coef, int i, int j);


    private :


    protected :

    std::vector<double> _coefs;
    int _ncolonnes;
    int _nlignes;

};

#endif