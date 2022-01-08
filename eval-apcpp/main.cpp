#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

#include "Matrix.h"

using namespace std;

void init(Matrix &K, Matrix &X, Matrix &T, int N, int Nt, double deltaX)
{
    for (int j = 0; j < N; j++)
    {
        X.set_coef(j*deltaX, j, 0);
        double x = X.get_coef(j, 0);
        T.set_coef(1/2 + sin(2*M_PI*x - 1/2 * cos(2*M_PI*x)), j, 0);
    }
    T.set_coef(0., N-1, 0);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j) {K.set_coef(2/pow(deltaX, 2), i, j);}
            else if (j == i-1) {K.set_coef(-1/pow(deltaX, 2), i, j);}
            else if (i == j-1) {K.set_coef(-1/pow(deltaX, 2), i, j);}
            else {K.set_coef(0., i, j);}
        }
    }
}

int main(int, char**) 
{
    //déclaration des variables
    vector<Matrix> matrixT_k;
    vector<vector<vector<double>>> T_k;
    int N = 4, Nt = 50; double tfinal = 0.5;
    Matrix T(N, 1), X(N, 1), K(N, N);
    double deltaX = 1./(N-1), deltaT = tfinal/Nt;

    //initialisation
    init(K, X, T, N, Nt, deltaX);

    //calcul des T_k
    for (int k = 0; k < Nt; k++)
    {
        matrixT_k.push_back(T);
        T_k.push_back(T.get_coefs());
        Matrix temp = K.produit_matrice(T, false).produit_par_scalaire(-deltaT, false); // T{k+1} = T{k} - deltat . K * T{k}
        T.somme_matrice(temp);
        T.set_coef(0., 0, 0);
        T.set_coef(0., N-1, 0);
    }

    //création d'un fichier texte

    std::ofstream fout("/home/camsz/prgms/ue12-projects/eval-apcpp/data.txt");

    fout << N << '\n' << Nt << '\n' << tfinal <<'\n';
    for (auto T : T_k)
    {
        for (int i = 0; i < N; i++)
        {
            double coef = T[i][0];
            fout << coef;
            if (i < N-1)
            {
                fout << ',';
            }
        }
        fout << '\n';
    }

    fout.close();

    return 0;
}