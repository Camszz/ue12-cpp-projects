#include "Matrix.h"
#include "resolution.h"

Matrix gradient_conjugue(Matrix A, Matrix b, Matrix x0, double epsilon)
{
    Matrix r = b.difference_matrice(A.produit_matrice(x0));
    Matrix p = r;
    int k = 0;
    Matrix X = x0;
    double alpha, alpha1, alpha2, beta;
    while (r.norme() > epsilon)
    {
        //calcul de alpha
        alpha1 = r.transpose().produit_matrice(r).to_scalar();
        alpha2 = p.transpose().produit_matrice(A).produit_matrice(p).to_scalar();
        alpha = alpha1 / alpha2;
        //calcul de X_k+1, R_k+1, P_k+1
        X = X.somme_matrice(p.produit_par_scalaire(alpha));
        r = r.difference_matrice(A.produit_matrice(p).produit_par_scalaire(alpha));
        beta = r.transpose().produit_matrice(r).to_scalar() / alpha1;
        p = r.somme_matrice(p.produit_par_scalaire(beta));
        //on incrémente k de 1
        k += 1;
    }

    return X;
}

Matrix euler_explicite(Matrix T, Matrix K, double deltaT)
{
    T.somme_matrice(K.produit_matrice(T).produit_par_scalaire(-deltaT));
    return T;
}