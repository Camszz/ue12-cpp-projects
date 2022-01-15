#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <random>

#include "Matrix.h"
#include "resolution.h"
#include "init.h"
#include "test_matrices.h"

using namespace std;

int main(int, char **)
{
    //déclaration des variables

    int N = 10, Nt = 101, choix_methode, choix_mode;
    double tfinal = 0.5, epsilon = 0.0001;
    string filename;

    //modules de test ?
    mode(choix_mode);
    
    if (choix_mode == 1) //test de matrices
    {
        test1();
        cout << "Tests de matrice terminés";
        exit(EXIT_SUCCESS);
    }

    //initialisation
    set_parameters(N, Nt, choix_methode, filename, tfinal);
    vector<Matrix> matrixT_k;
    Matrix T(N, 1), X(N, 1), K(N, N), D(N+1, 1, 1.);
    double deltaX = 1. / (N - 1), deltaT = tfinal / Nt;
    init_csts(K, X, T, D, N, Nt, deltaX);

    //calcul des T_k
    if (choix_methode == 1) //Euler explicite
    {
        for (int k = 0; k < Nt; k++)
        {
            matrixT_k.push_back(T);
            T = euler_explicite(T, K, deltaT);
            T.set_coef(0., 0, 0);
            T.set_coef(0., N - 1, 0);
        }
    }

    else if (choix_methode == 2) //Gradient conjugué
    {
        for (int k = 0; k < Nt; k++)
        {
            matrixT_k.push_back(T);
            Matrix A = Matrix(N, 1., true).somme_matrice(K.produit_par_scalaire(deltaT));
            T = gradient_conjugue(A, T, euler_explicite(T, K, deltaT), epsilon);
            T.set_coef(0., 0, 0);
            T.set_coef(0., N - 1, 0);
        }
    }

    else if (choix_methode == 3) //Jacobi
    {
        for (int k = 0; k < Nt; k++)
        {
            matrixT_k.push_back(T);
            Matrix A = Matrix(N, 1., true).somme_matrice(K.produit_par_scalaire(deltaT));
            T = jacobi(A, T, euler_explicite(T, K, deltaT), epsilon);
            T.set_coef(0., 0, 0);
            T.set_coef(0., N - 1, 0);
        }
    }    

    //création d'un fichier texte

    std::ofstream fout("../data/" + filename);

    fout << N << '\n'
         << Nt << '\n'
         << tfinal << '\n';
    for (auto T : matrixT_k)
    {
        T.WriteToFile(fout);
    }
    fout.close();

    return 0;
}