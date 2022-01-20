#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <random>
#include <chrono>

#include "Matrix.h"
#include "resolution.h"
#include "init.h"
#include "test_matrices.h"
#include "Matrixcreuse.h"

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
    Matrix T(N, 1), X(N, 1), K(N, N), D(N+1, 1, 1.), X0(N, 1);
    double deltaX = 1. / (N - 1), deltaT = tfinal / Nt;
    init_csts(K, X, T, D, N, Nt, deltaX);

    //calcul des T_k

    auto start = std::chrono::steady_clock::now();
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
        Matrix A = Matrix(N, 1., true).somme_matrice(K.produit_par_scalaire(deltaT));
        for (int k = 0; k < Nt; k++)
        {
            matrixT_k.push_back(T);
            T = gradient_conjugue(A, T, euler_explicite(T, K, deltaT), epsilon);
            T.set_coef(0., 0, 0);
            T.set_coef(0., N - 1, 0);
        }
    }

    else if (choix_methode == 3) //Jacobi
    {
        Matrix A = Matrix(N, 1., true).somme_matrice(K.produit_par_scalaire(deltaT));
        for (int k = 0; k < Nt; k++)
        {
            matrixT_k.push_back(T);
            T = jacobi(A, T, euler_explicite(T, K, deltaT), epsilon);
            T.set_coef(0., 0, 0);
            T.set_coef(0., N - 1, 0);
        }
    }

    else if (choix_methode == 4) //Gradient conjugué, matrices creuses
    {
        Matrixcreuse A(Matrix(N, 1., true).somme_matrice(K.produit_par_scalaire(deltaT)));
        for (int k = 0; k < Nt; k++)
        {
            matrixT_k.push_back(T);
            T = gradient_conjugue_creux(A, T, euler_explicite(T, K, deltaT), epsilon);
            T.set_coef(0., 0, 0);
            T.set_coef(0., N - 1, 0);
        }
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;

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

    string reg = "n";
    cout << "Enregistrer les performances ? [y/n]";
    cin >> reg;
    if (reg == "y")
    {
        std::ofstream out("../data/performance.txt", std::ios_base::app);
        std::vector<string> method_name = {"Euler explicite", "Gradient conjugué", "Jacobi", "Matrices creuses, gradient"};
        out << method_name[choix_methode-1] << ';' << 1./N << ';' << tfinal/Nt << ';' << elapsed_seconds.count() << "\n";
        out.close();
    }

    return 0;
}