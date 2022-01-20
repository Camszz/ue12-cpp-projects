#ifndef RESOLUTION
#define RESOLUTION
#pragma once

#include"Matrix.h"
#include"Matrixcreuse.h"

Matrix gradient_conjugue(const Matrix& A, const Matrix& b, const Matrix& x0, double epsilon)
{
    Matrix r = b-(A*x0);
    Matrix p = r;
    int k = 0;
    Matrix X = x0;
    double alpha, alpha1, alpha2, beta;
    while (r.norme() > epsilon)
    {
        //calcul de alpha
        alpha1 = (r.transpose()*r).to_scalar();
        alpha2 = (p.transpose()*A*p).to_scalar();
        alpha = alpha1 / alpha2;
        //calcul de X_k+1, R_k+1, P_k+1
        X = X+(p*alpha);
        r = r-(A*p*alpha);
        beta = (r.transpose()*r).to_scalar() / alpha1;
        p = r+(p*beta);
        //on incrémente k de 1
        k += 1;
    }

    return X;
}

Matrix gradient_conjugue_creux(const Matrixcreuse& A, const Matrix& b, const Matrix& x0, double epsilon)
{
    Matrix r = b-(A*(x0));
    Matrix p = r;
    int k = 0;
    Matrix X = x0;
    double alpha, alpha1, alpha2, beta;
    while (r.norme() > epsilon)
    {
        //calcul de alpha
        alpha1 = (r.transpose()*r).to_scalar();
        alpha2 = (p.transpose()*(A*p)).to_scalar();
        alpha = alpha1 / alpha2;
        //calcul de X_k+1, R_k+1, P_k+1
        X = X+(p*alpha);
        r = r-(A*p*alpha);
        beta = (r.transpose()*r).to_scalar() / alpha1;
        p = r+(p*beta);
        //on incrémente k de 1
        k += 1;
    }

    return X;
}

Matrix euler_explicite(const Matrix& T, const Matrix& K, const double deltaT)
{
    Matrix temp = K*T;
    Matrix out = T-(temp*deltaT);
    return out;
}

Matrix jacobi(const Matrix& A, const Matrix& b, const Matrix& x0, double epsilon)
{
    int N = A.get_size()[0];
    Matrix X_n = x0;
    Matrix X_npun = x0;
    while ((b - (A*X_n)).norme() > epsilon) 
    {
        for (int i = 0; i < N; i++)
        {
            double somme = 0., coef;
            for (int k = 0; k < N; k++)
            {
                if (k != i)
                {
                    somme += A.get_coef(i, k) * X_n.get_coef(k, 0);
                }
            }
            coef = (b.get_coef(i, 0) - somme)/A.get_coef(i,i);
            X_npun.set_coef(coef, i, 0);
        }
        X_n = X_npun;
    }
    
    return X_n;
}

#endif // RESOLUTION