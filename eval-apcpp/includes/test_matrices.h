#include "Matrix.h"

using namespace std;

void test1()
{
    int nbli_A, nbcol_A, nbli_B, nbcol_B;
    double lambda;
    cout << "Entrez le nombre de lignes de A ";
    cin >> nbli_A;
    cout << "Entrez le nombre de colonnes de A ";
    cin >> nbcol_A;
    cout << "Entrez le nombre de lignes de B ";
    cin >> nbli_B;
    cout << "Entrez le nombre de colonnes de B ";
    cin >> nbcol_B;
    Matrix A(nbli_A, nbcol_A), B(nbli_B, nbcol_B);

    for (int i = 0; i < nbli_A; i++)
    {
        for (int j = 0; j < nbcol_A; j++)
        {
            double coef;
            cout << "Entrez le coefficient (" << i << "," << j <<") de la matrice A ";
            cin >> coef;
            A.set_coef(coef, i, j);
        }
    }

    for (int i = 0; i < nbli_B; i++)
    {
        for (int j = 0; j < nbcol_B; j++)
        {
            double coef;
            cout << "Entrez le coefficient (" << i << "," << j <<") de la matrice B ";
            cin >> coef;
            B.set_coef(coef, i, j);
        }
    }

    cout << "Entrez un scalaire ";
    cin >> lambda;

    if (A.get_size() == B.get_size())
    {
        cout << "A+B \n";
        (A+B).afficher();
        cout << "A-B \n";
        (A-B).afficher();
    }
    if (A.get_size()[1] == B.get_size()[0])
    {
        cout << "A*B \n";
        (A*B).afficher();
    }
    cout << "lambda*A \n";
    (A*lambda).afficher();
} 
