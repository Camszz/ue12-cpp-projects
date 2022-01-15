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

Matrix::Matrix(vector<vector<double>> coefs)
{
    _nlignes = coefs.size();
    _ncolonnes = coefs[0].size();
    _coefs = coefs;

}

Matrix::Matrix(int n_lignes, int n_colonnes, double fill)
{
    vector<vector<double>> coefs_temp;

    for (int i = 0; i < n_lignes; i++)
    {
        vector<double> ligne;
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


//getters ----------------------------------------

vector<vector<double>> Matrix::get_coefs() const
{
    return _coefs;
}

vector<int> Matrix::get_size() const
{
    return {_nlignes, _ncolonnes};
}

double Matrix::get_coef(int i, int j) const
{
    return _coefs[i][j];
}

double Matrix::to_scalar() const
{
    assert(_ncolonnes * _nlignes == 1 && "to_scalar of non 1x1 matrix");
    return _coefs[0][0];
}

//setters ----------------------------------------

void Matrix::set_coefs(vector<vector<double>> coefs)
{
    _coefs = coefs;
}

void Matrix::set_coef(double coef, int i, int j)
{
    _coefs[i][j] = coef;
}


//somme de matrices ----------------------------------------

Matrix Matrix::somme_matrice(Matrix A, bool inplace)
{
    vector<vector<double>> coefs_temp;

    // création de la matrice somme
    if ((A._ncolonnes == _ncolonnes) && (A._nlignes == _nlignes))
    {
        for (int i = 0; i < _nlignes; i++)
        {
            vector<double> ligne;
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

Matrix Matrix::operator+(const Matrix& A) const
{
    vector<vector<double>> coefs_temp;

    // création de la matrice somme
    if ((A._ncolonnes == _ncolonnes) && (A._nlignes == _nlignes))
    {
        for (int i = 0; i < _nlignes; i++)
        {
            vector<double> ligne;
            coefs_temp.push_back(ligne);
            for (int j = 0; j < _ncolonnes; j++)
            {
                coefs_temp[i].push_back(_coefs[i][j] + A._coefs[i][j]);
            }
        }
    }

    // renvoi de la matrice somme
    return Matrix(coefs_temp); 
}

//différence de matrices ----------------------------------------

Matrix Matrix::difference_matrice(Matrix A, bool inplace)
{
    vector<vector<double>> coefs_temp;

    // création de la matrice somme
    if ((A._ncolonnes == _ncolonnes) && (A._nlignes == _nlignes))
    {
        for (int i = 0; i < _nlignes; i++)
        {
            vector<double> ligne;
            coefs_temp.push_back(ligne);
            for (int j = 0; j < _ncolonnes; j++)
            {
                coefs_temp[i].push_back(_coefs[i][j] - A._coefs[i][j]);
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

Matrix Matrix::operator-(const Matrix& A) const
{
    vector<vector<double>> coefs_temp;

    // création de la matrice somme
    if ((A._ncolonnes == _ncolonnes) && (A._nlignes == _nlignes))
    {
        for (int i = 0; i < _nlignes; i++)
        {
            vector<double> ligne;
            coefs_temp.push_back(ligne);
            for (int j = 0; j < _ncolonnes; j++)
            {
                coefs_temp[i].push_back(_coefs[i][j] - A._coefs[i][j]);
            }
        }
    }

    // renvoi de la matrice somme
    return Matrix(coefs_temp); 
}

//produit matriciel ----------------------------------------

Matrix Matrix::produit_matrice(Matrix A, bool inplace)
{
    vector<vector<double>> coefs_temp;

    // création de la matrice produit
    if (_ncolonnes == A._nlignes)
    {
        for (int i = 0; i < _nlignes; i++)
        {
            vector<double> ligne;
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

Matrix Matrix::operator*(const Matrix& A) const
{
    vector<vector<double>> coefs_temp;

    // création de la matrice produit
    if (_ncolonnes == A._nlignes)
    {
        for (int i = 0; i < _nlignes; i++)
        {
            vector<double> ligne;
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

    // retour de la matrice produit
    return Matrix(coefs_temp);
}

Matrix Matrix::operator/(double lambda) const
{
    vector<vector<double>> coefs_temp;

    // création de la matrice finale
    for (int i = 0; i < _nlignes; i++)
    {
        vector<double> ligne;
        coefs_temp.push_back(ligne);
        for (int j = 0; j < _ncolonnes; j++)
        {
            coefs_temp[i].push_back(_coefs[i][j] / lambda);
        }
    }

    // renvoi de la matrice finale
    return Matrix(coefs_temp); 
}

//opération de matrice avec un scalaire ----------------------------------------

Matrix Matrix::produit_par_scalaire(double lambda, bool inplace)
{
    vector<vector<double>> coefs_temp;

    // création de la matrice finale
    for (int i = 0; i < _nlignes; i++)
    {
        vector<double> ligne;
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

Matrix Matrix::operator*(double lambda) const
{
    vector<vector<double>> coefs_temp;

    // création de la matrice finale
    for (int i = 0; i < _nlignes; i++)
    {
        vector<double> ligne;
        coefs_temp.push_back(ligne);
        for (int j = 0; j < _ncolonnes; j++)
        {
            coefs_temp[i].push_back(_coefs[i][j] * lambda);
        }
    }

    // renvoi de la matrice finale
    return Matrix(coefs_temp); 
}

//transposition ----------------------------------------

Matrix Matrix::transpose(bool inplace)
{
    vector<vector<double>> coefs_temp;
    for (int j = 0; j < _ncolonnes; j++)
    {
        vector<double> ligne;
        coefs_temp.push_back(ligne);
        for (int i = 0; i < _nlignes; i++)
        {
            coefs_temp[j].push_back(_coefs[i][j]);
        }
    }

    if (inplace == true)
    {
        _coefs = coefs_temp;
        _nlignes = _coefs.size();
        _ncolonnes = _coefs[0].size();
    }

    return coefs_temp;
}

//norme ----------------------------------------

double Matrix::norme()
{
    double s = 0;
    for (vector<double> ligne : _coefs)
    {
        for (double coef : ligne)
        {
            s += pow(coef, 2);
        } 
    }
    return pow(s, 0.5);
}

//switches

Matrix Matrix::switch_lines(int a, int b, bool inplace)
{
    Matrix res(_coefs);
    for (int j = 0; j < _ncolonnes; j++)
    {
        res.set_coef(_coefs[a][j], b, j);
        res.set_coef(_coefs[b][j], a, j);
    }

    if (inplace == true)
    {
        _coefs = res.get_coefs();
    }

    return res;
}

Matrix Matrix::switch_cols(int a, int b, bool inplace)
{
    Matrix res(_coefs);
    for (int i = 0; i < _nlignes; i++)
    {
        res.set_coef(_coefs[i][a],i, a);
        res.set_coef(_coefs[i][b], i, b);
    }

    if (inplace == true)
    {
        _coefs = res.get_coefs();
    }

    return res;
}

//Export ----------------------------------------

void Matrix::WriteToFile(std::ofstream& fout)
{
    int N = _nlignes;
    for (int i = 0; i < N; i++)
    {
        double coef = _coefs[i][0];
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
    for (auto ligne : _coefs)
    {
        cout << "|";
        for (auto coef : ligne)
        {
            cout << coef << " ";
        }
        cout << "|" << "\n";
    }
    cout << "\n";
}