#ifndef INIT
#define INIT
#pragma once

#include<iostream>
#include<random>
#include<string>

#include "Matrix.h"

void mode(int& choix_mode)
{
    std::cout << "Tapez : \n 1 - tests de matrices \n 2 - tests euler_explicite \n 3 - tests gradient conjugué \n 4 - programme d'évaluation \n";
    std::cin >> choix_mode;
}

void init_csts(Matrix &K, Matrix &X, Matrix &T, Matrix &D, int N, int Nt, double deltaX)
{
    for (int j = 0; j < N; j++)
    {
        X.set_coef(j * deltaX, j, 0);
        double x = X.get_coef(j, 0);
        T.set_coef(1 / 2 + sin(2 * M_PI * x - 1 / 2 * cos(2 * M_PI * x)), j, 0);
    }
    T.set_coef(0., N - 1, 0);

    std::string D_aleatoire;
    std::cout << "Vecteur D aléatoire ? [y/n]";
    std::cin >> D_aleatoire;

    if (D_aleatoire == "y")
    {
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_real_distribution<float> distr(0.5, 1.5);
        for (int i = 0; i < N+1; i++)
        {
            double coef = distr(eng);
            D.set_coef(coef, i, 0);
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j)
            {
                K.set_coef((D.get_coef(i, 0) + D.get_coef(i+1, 0)) / pow(deltaX, 2), i, j);
            }
            else if (j+1 == i)
            {
                K.set_coef(- D.get_coef(i, 0) / pow(deltaX, 2), i, j);
            }
            else if (i+1 == j)
            {
                K.set_coef(- D.get_coef(i+1, 0) / pow(deltaX, 2), i, j);
            }
            else
            {
                K.set_coef(0., i, j);
            }
        }
    }
}

void set_parameters(int& N, int& Nt, int& choix_methode, std::string& filename, const double& tfinal)
{
    std::cout << "Saisissez un entier N de sorte que 1/N soit le pas spacial du système \n";
    std::cin >> N;
    std::cout << "Saisissez un entier Nt de sorte que " << tfinal << "/Nt soit le pas temporel du système \n PRENEZ Nt > " << pow(N, 2) << "\n";
    std::cin >> Nt;
    if (pow(N, 2) >= Nt)
    {
        std::cout << "Le système ne devrait pas converger. Veuillez choisir des valeurs N et Nt telles que N^2 < Nt.";
        exit(EXIT_FAILURE);
    }
    std::cout << "Tapez : \n 1 - méthode Euler explicite (q2) \n 2 - méthode implicite, gradient conjugué (q4) // ATTENTION : ne marche pas avec D aléatoire \n 3 - méthode implicite, jacobi (q4) // fonctionne avec D aléatoire \n";
    std::cin >> choix_methode;
    std::cout << "Entrez un nom de fichier \n";
    std::cin >> filename;
}

#endif // INIT