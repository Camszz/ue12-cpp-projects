#ifndef DEF_MATRIX
#define DEF_MATRIX

#include<vector>

class Matrix
{
    public :

    //constructors
    Matrix();
    Matrix(int n_lignes, int n_colonnes, double fill=0.);
    Matrix(std::vector<std::vector<double>> coefs);

    //opérations
    Matrix somme_matrice(Matrix A, bool inplace=true); //le paramètre inplace permet de définir si l'on modifie la matrice A d'origine
    Matrix produit_matrice(Matrix A, bool inplace=true);
    Matrix produit_par_scalaire(double lambda, bool inplace=true);
    Matrix transpose(bool inplace=true);

    //getters
    std::vector<std::vector<double>> get_coefs() const;
    double get_coef(int i, int j);
    std::vector<int> get_size() const;

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