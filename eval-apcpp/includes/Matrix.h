#ifndef DEF_MATRIX
#define DEF_MATRIX

#include<vector>
#include<cassert>
#include <string>

#include "math.h"

class Matrix
{
    public :

    //constructors
    Matrix();
    Matrix(int n_lignes, int n_colonnes, double fill=0.);
    Matrix(std::vector<std::vector<double>> coefs);
    Matrix(int n, double fill = 1., bool diag = false);

    //opérations
    Matrix somme_matrice(Matrix A, bool inplace=false); //le paramètre inplace permet de définir si l'on modifie la matrice A d'origine
    Matrix difference_matrice(Matrix A, bool inplace=false);
    Matrix produit_matrice(Matrix A, bool inplace=false);
    Matrix produit_par_scalaire(double lambda, bool inplace=false);
    Matrix transpose(bool inplace=false);
    double norme(); //racine de la somme des coefs au carré

    //getters
    std::vector<std::vector<double>> get_coefs() const;
    double get_coef(int i, int j);
    std::vector<int> get_size() const;
    double to_scalar(); //si A est de taille 1x1, renvoie sa valeur comme un scalaire

    //setters
    void set_coefs(std::vector<std::vector<double>> coefs);
    void set_coef(double coef, int i, int j);


    private :


    protected :

    std::vector<std::vector<double>> _coefs;
    int _ncolonnes;
    int _nlignes;

};

#endif