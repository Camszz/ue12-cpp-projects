#ifndef DEF_MATRIX
#define DEF_MATRIX

#include<vector>

class Matrix
{
    public :

    //constructors
    Matrix();
    Matrix(int n_colonnes, int n_lignes, double fill=0.);
    Matrix(std::vector<std::vector<float>> coefs);

    //opérations
    Matrix somme_matrice(Matrix A, bool inplace=true); //le paramètre inplace permet de définir si l'on modifie la matrice A d'origine
    Matrix produit_matrice(Matrix A, bool inplace=true);
    Matrix produit_par_scalaire(double lambda, bool inplace=true);

    //getters
    std::vector<std::vector<float>> get_coefs() const;
    std::vector<int> Matrix::get_size() const;

    //setters
    void set_coefs(std::vector<std::vector<float>> coefs);


    private :


    protected :

    std::vector<std::vector<float>> _coefs;
    int _ncolonnes;
    int _nlignes;

};

#endif