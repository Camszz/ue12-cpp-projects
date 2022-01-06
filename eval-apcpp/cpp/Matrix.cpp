#include "Matrix.h"
#include <vector>

using namespace std;


//constructeurs ----------------------------------------

Matrix::Matrix()
{
    _nlignes;
    _ncolonnes;
    _coefs;
}

// --- //


Matrix::Matrix(vector<vector<float>> coefs)
{
    _nlignes = coefs.size();
    _ncolonnes = coefs[0].size();
    _coefs = coefs;

}

// --- //

Matrix::Matrix(int n_colonnes, int n_lignes, double fill)
{
    vector<vector<float>> coefs_temp;

    for (int i = 0; i < n_lignes; i++)
    {
        vector<float> ligne;
        coefs_temp.push_back(ligne);
        for (int j = 0; j < n_colonnes; j++)
        {
            coefs_temp[i].push_back(fill);
        }
    }
    _nlignes = n_lignes;
    _ncolonnes = n_colonnes;
    _coefs = coefs_temp;

}


//getters ----------------------------------------

vector<vector<float>> Matrix::get_coefs() const
{
    return _coefs;
}

vector<int> Matrix::get_size() const
{
    return {_nlignes, _ncolonnes};
}


//setters ----------------------------------------

void Matrix::set_coefs(vector<vector<float>> coefs)
{
    _coefs = coefs;
}


//somme de matrices ----------------------------------------

Matrix Matrix::somme_matrice(Matrix A, bool inplace)
{
    vector<vector<float>> coefs_temp;

    // création de la matrice somme
    if ((A._ncolonnes == _ncolonnes) && (A._nlignes == _nlignes))
    {
        for (int i = 0; i < _nlignes; i++)
        {
            vector<float> ligne;
            coefs_temp.push_back(ligne);
            for (int j = 0; j < _ncolonnes; j++)
            {
                coefs_temp[i].push_back(_coefs[i][j] + A._coefs[i][j]);
            }
        }
    }

    //si nécessaire, modification de la matrice initiale
    if (inplace == true)
    {
        _coefs = coefs_temp;
    }

    // renvoi de la matrice somme
    return Matrix(coefs_temp);
}


//produit matriciel ----------------------------------------

Matrix Matrix::produit_matrice(Matrix A, bool inplace)
{
    vector<vector<float>> coefs_temp;

    // création de la matrice produit
    if (_ncolonnes == A._nlignes)
    {
        for (int i = 0; i < _nlignes; i++)
        {
            vector<float> ligne;
            coefs_temp.push_back(ligne);
            for (int j = 0; j < A._ncolonnes; j++)
            {
                coefs_temp[i].push_back(0.);
                for (int k = 0; k < _ncolonnes; k++)
                {
                    coefs_temp[i][j] += _coefs[i][k] * A._coefs[k][j];
                }
            }
        }
    }

    // modification de la matrice appelée si nécessaire
    if (inplace==true)
    {
        _coefs = coefs_temp;
    }

    // retour de la matrice produit
    return Matrix(coefs_temp);
}


//produit de matrice par un scalaire ----------------------------------------

Matrix Matrix::produit_par_scalaire(double lambda, bool inplace)
{
    vector<vector<float>> coefs_temp;

    // création de la matrice finale
    for (int i = 0; i < _nlignes; i++)
    {
        vector<float> ligne;
        coefs_temp.push_back(ligne);
        for (int j = 0; j < _ncolonnes; j++)
        {
            coefs_temp[i].push_back(_coefs[i][j] * lambda);
        }
    }

    //si nécessaire, modification de la matrice initiale
    if (inplace == true)
    {
        _coefs = coefs_temp;
    }

    // renvoi de la matrice finale
    return Matrix(coefs_temp);
}