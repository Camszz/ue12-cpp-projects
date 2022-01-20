#include<vector>
#include<cassert>
#include<string>
#include<fstream>

#include "Matrix.h"
#include "math.h"

using namespace std;


//constructeurs ----------------------------------------

Matrix::Matrix()
{
    _nlignes;
    _ncolonnes;
    _coefs;
}

Matrix::Matrix(int n_lignes, int n_colonnes, double fill)
{
    vector<double> coefs_temp(n_lignes * n_colonnes, fill);

    _nlignes = n_lignes;
    _ncolonnes = n_colonnes;
    _coefs = coefs_temp;

}

Matrix::Matrix(int n, double fill, bool diag)
{
    if (diag)
    {
        Matrix temp(n, n);
        for (int i = 0; i < n; i++)
        {
            temp.set_coef(1., i, i);
        }
        _nlignes = n;
        _ncolonnes = n;
        _coefs = temp.get_coefs();
    }

    else
    {
        Matrix(n, n, fill);
    }
}

Matrix::Matrix(vector<double> coefs, int nlignes, int ncolonnes)
{
    _coefs = coefs;
    _nlignes = nlignes;
    _ncolonnes = ncolonnes;
}


//getters ----------------------------------------

vector<double> Matrix::get_coefs() const
{
    return _coefs;
}

vector<int> Matrix::get_size() const
{
    return {_nlignes, _ncolonnes};
}

double Matrix::get_coef(int i, int j) const
{
    return _coefs[_ncolonnes * i + j];
}

double Matrix::to_scalar() const
{
    assert(_ncolonnes * _nlignes == 1 && "to_scalar of non 1x1 matrix");
    return _coefs[0];
}

//setters ----------------------------------------

void Matrix::set_coefs(vector<double> coefs)
{
    _coefs = coefs;
}

void Matrix::set_coef(const double coef, int i, int j)
{
    _coefs[i * _ncolonnes + j] = coef;
}


//somme de matrices ----------------------------------------

Matrix Matrix::somme_matrice(const Matrix& A, bool inplace)
{
    vector<double> coefs_temp;

    // création de la matrice somme
    if ((A._ncolonnes == _ncolonnes) && (A._nlignes == _nlignes))
    {
        for (int i = 0; i < _nlignes; i++)
        {
            for (int j = 0; j < _ncolonnes; j++)
            {
                coefs_temp.push_back(this->get_coef(i, j) + A.get_coef(i, j));
            }
        }
    }

    //si nécessaire, modification de la matrice initiale
    if (inplace == true)
    {
        _coefs = coefs_temp;
    }

    // renvoi de la matrice somme
    return Matrix(coefs_temp, _nlignes, _ncolonnes);
}

Matrix Matrix::operator+(const Matrix& A) const
{
    vector<double> coefs_temp;

    // création de la matrice somme
    if ((A._ncolonnes == _ncolonnes) && (A._nlignes == _nlignes))
    {
        for (int i = 0; i < _nlignes; i++)
        {
            for (int j = 0; j < _ncolonnes; j++)
            {
                coefs_temp.push_back(this->get_coef(i,j) + A.get_coef(i, j));
            }
        }
    }

    // renvoi de la matrice somme
    return Matrix(coefs_temp, _nlignes, _ncolonnes); 
}

//différence de matrices ----------------------------------------

Matrix Matrix::difference_matrice(const Matrix& A, bool inplace)
{
    vector<double> coefs_temp;

    // création de la matrice somme
    if ((A._ncolonnes == _ncolonnes) && (A._nlignes == _nlignes))
    {
        for (int i = 0; i < _nlignes; i++)
        {
            for (int j = 0; j < _ncolonnes; j++)
            {
                coefs_temp.push_back(this->get_coef(i, j) - A.get_coef(i, j));
            }
        }
    }

    //si nécessaire, modification de la matrice initiale
    if (inplace == true)
    {
        _coefs = coefs_temp;
    }

    // renvoi de la matrice somme
    return Matrix(coefs_temp, _nlignes, _ncolonnes);
}

Matrix Matrix::operator-(const Matrix& A) const
{
    vector<double> coefs_temp;

    // création de la matrice somme
    if ((A._ncolonnes == _ncolonnes) && (A._nlignes == _nlignes))
    {
        for (int i = 0; i < _nlignes; i++)
        {
            for (int j = 0; j < _ncolonnes; j++)
            {
                coefs_temp.push_back(this->get_coef(i, j) - A.get_coef(i, j));
            }
        }
    }

    // renvoi de la matrice somme
    return Matrix(coefs_temp, _nlignes, _ncolonnes); 
}

//produit matriciel ----------------------------------------

Matrix Matrix::produit_matrice(const Matrix& A, bool inplace)
{
    vector<double> coefs_temp;

    // création de la matrice produit
    if (_ncolonnes == A._nlignes)
    {
        for (int i = 0; i < _nlignes; i++)
        {
            for (int j = 0; j < A._ncolonnes; j++)
            {
                coefs_temp.push_back(0.);
                for (int k = 0; k < _ncolonnes; k++)
                {
                    coefs_temp[i * _ncolonnes + j] += this->get_coef(i, k) * A.get_coef(k, j);
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
    return Matrix(coefs_temp, _nlignes, _ncolonnes);
}

Matrix Matrix::operator*(const Matrix& A) const
{
    vector<double> coefs_temp;

    // création de la matrice produit
    if (_ncolonnes == A._nlignes)
    {
        for (int i = 0; i < _nlignes; i++)
        {
            for (int j = 0; j < A._ncolonnes; j++)
            {
                coefs_temp.push_back(0.);
                for (int k = 0; k < _ncolonnes; k++)
                {
                    coefs_temp[i * A._ncolonnes + j] += this->get_coef(i, k) * A.get_coef(k, j);
                }
            }
        }
    }

    // retour de la matrice produit
    return Matrix(coefs_temp, _nlignes, A.get_size()[1]);
}

Matrix Matrix::operator/(double lambda) const
{
    vector<double> coefs_temp;

    // création de la matrice finale
    for (int i = 0; i < _nlignes; i++)
    {
        for (int j = 0; j < _ncolonnes; j++)
        {
            coefs_temp.push_back(this->get_coef(i, j) / lambda);
        }
    }

    // renvoi de la matrice finale
    return Matrix(coefs_temp, _nlignes, _ncolonnes); 
}

//opération de matrice avec un scalaire ----------------------------------------

Matrix Matrix::produit_par_scalaire(double lambda, bool inplace)
{
    vector<double> coefs_temp;

    // création de la matrice finale
    for (int i = 0; i < _nlignes; i++)
    {
        for (int j = 0; j < _ncolonnes; j++)
        {
            coefs_temp.push_back(this->get_coef(i, j) * lambda);
        }
    }

    //si nécessaire, modification de la matrice initiale
    if (inplace == true)
    {
        _coefs = coefs_temp;
    }

    // renvoi de la matrice finale
    return Matrix(coefs_temp, _nlignes, _ncolonnes);
}

Matrix Matrix::operator*(double lambda) const
{
    vector<double> coefs_temp;

    // création de la matrice finale
    for (int i = 0; i < _nlignes; i++)
    {
        for (int j = 0; j < _ncolonnes; j++)
        {
            coefs_temp.push_back(this->get_coef(i, j) * lambda);
        }
    }

    // renvoi de la matrice finale
    return Matrix(coefs_temp, _nlignes, _ncolonnes); 
}

//transposition ----------------------------------------

Matrix Matrix::transpose(bool inplace)
{
    vector<double> coefs_temp;
    for (int i = 0; i < _nlignes; i++)
    {
        for (int j = 0; j < _ncolonnes; j++)
        {
            coefs_temp.push_back(this->get_coef(j, i));
        }
    }

    Matrix out(coefs_temp, _ncolonnes, _nlignes);

    if (inplace == true)
    {
        _coefs = coefs_temp;
        _nlignes = this->get_size()[1];
        _ncolonnes = this->get_size()[0];
    }

    return out;
}

//norme ----------------------------------------

double Matrix::norme()
{
    double s = 0;
    for (double coef : this->get_coefs())
    {
        s += pow(coef, 2); 
    }
    return pow(s, 0.5);
}

//Export ----------------------------------------

void Matrix::WriteToFile(std::ofstream& fout)
{
    int N = _nlignes;
    for (int i = 0; i < N; i++)
    {
        double coef = this->get_coef(i, 0);
        fout << coef;
        if (i < N - 1)
        {
            fout << ',';
        }
    }
    fout << '\n';
}

void Matrix::afficher()
{
    for (int i = 0; i < _nlignes; i++)
    {
        cout << "|";
        for (int j = 0; j < _ncolonnes; j++)
        {
            cout << this->get_coef(i, j) << " ";
        }
        cout << "|" << "\n";
    }
    cout << "\n";
}