#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

#include "Matrix.h"
#include "resolution.h"

using namespace std;

void init(Matrix &K, Matrix &X, Matrix &T, int N, int Nt, double deltaX)
{
    for (int j = 0; j < N; j++)
    {
        X.set_coef(j * deltaX, j, 0);
        double x = X.get_coef(j, 0);
        T.set_coef(1 / 2 + sin(2 * M_PI * x - 1 / 2 * cos(2 * M_PI * x)), j, 0);
    }
    T.set_coef(0., N - 1, 0);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j)
            {
                K.set_coef(2 / pow(deltaX, 2), i, j);
            }
            else if (j == i - 1)
            {
                K.set_coef(-1 / pow(deltaX, 2), i, j);
            }
            else if (i == j - 1)
            {
                K.set_coef(-1 / pow(deltaX, 2), i, j);
            }
            else
            {
                K.set_coef(0., i, j);
            }
        }
    }
}

int main(int, char **)
{
    //déclaration des variables
    int N, Nt;
    double tfinal = 0.5;
    cout << "Saisissez un entier N de sorte que 1/N soit le pas spacial du système \n";
    cin >> N;
    cout << "Saisissez un entier Nt de sorte que 1/Nt soit le pas temporel du système \n PRENEZ Nt > " << pow(N, 2) << "\n";
    cin >> Nt;
    if (pow(N, 2) >= Nt)
    {
        cout << "Le système ne devrait pas converger. Veuillez choisir des valeurs N et Nt telles que N^2 < Nt.";
    }
    vector<Matrix> matrixT_k;
    vector<vector<vector<double>>> T_k;
    Matrix T(N, 1), X(N, 1), K(N, N);
    double deltaX = 1. / (N - 1), deltaT = tfinal / Nt;

    //initialisation
    init(K, X, T, N, Nt, deltaX);
    int choix_methode;
    cout << "Tapez 1 pour la méthode Euler explicite (q2), tapez 2 pour la méthode implicite (q4)";
    cin >> choix_methode;

    //calcul des T_k
    if (choix_methode == 1)
    {
        for (int k = 0; k < Nt; k++)
        {
            matrixT_k.push_back(T);
            T_k.push_back(T.get_coefs());
            T = euler_explicite(T, K, deltaT);
            T.set_coef(0., 0, 0);
            T.set_coef(0., N - 1, 0);
        }
    }

    else if (choix_methode == 2)
    {
        for (int k = 0; k < Nt; k++)
        {
            matrixT_k.push_back(T);
            T_k.push_back(T.get_coefs());
            Matrix A = Matrix(N, 1., true).somme_matrice(K.produit_par_scalaire(deltaT));
            T = gradient_conjugue(A, T, euler_explicite(T, K, deltaT), 0.0001);
            T.set_coef(0., 0, 0);
            T.set_coef(0., N - 1, 0);
        }
    }

    //création d'un fichier texte

    std::ofstream fout("/home/camsz/prgms/ue12-projects/eval-apcpp/data.txt");

    fout << N << '\n'
         << Nt << '\n'
         << tfinal << '\n';
    for (auto T : T_k)
    {
        for (int i = 0; i < N; i++)
        {
            double coef = T[i][0];
            fout << coef;
            if (i < N - 1)
            {
                fout << ',';
            }
        }
        fout << '\n';
    }

    fout.close();

    return 0;
}