#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define n 7
#define IT_MAX 12

void mac_wek(double a[n][n], double x[n], double temp[n])
{
    for (int i = 0; i < n; i++)
    {
        temp[i] = 0;

        for (int j = 0; j < n; j++)
        {
            temp[i] += (a[i][j] * x[j]);
        }
    }
}

double wek_wek(double w1[n], double w2[n])
{
    double skalar = 0;

    for (int i = 0; i < n; i++)
    {
        skalar += w1[i] * w2[i];
    }

    return skalar;
}

void mac_mac(double A[n][n], double B[n][n], double C[n][n])
{
    double temp;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            temp = 0;

            for (int k = 0; k < n; k++)
            {
                temp += A[i][k] * B[k][j];
            }

            C[i][j] = temp;
        }
    }
}

int main()
{
    double A[n][n];
    double W[n][n];
    double X[n][n];
    double C[n][n];
    double X_T[n][n];
    double D[n][n];
    double x_old[n];
    double x_new[n];
    double lambda[n];

    FILE *wynik;
    FILE *macierz_D;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = (1.0 + fabs(i + j)) / (1.0 + fabs(i - j));
            W[i][j] = A[i][j];
        }
    }

    wynik = fopen("wynik.dat", "w");
    macierz_D = fopen("macierz_D.dat", "w");

    for (int k = 0; k < n; k++)
    {
        double c = 0;

        for (int i = 0; i < n; i++)
        {
            x_old[i] = 1;
            c = c + x_old[i];
        }

        for (int i = 0; i < n; i++)
        {
            x_old[i] = x_old[i] / sqrt(c);
        }

        for (int m = 1; m <= IT_MAX; m++)
        {
            mac_wek(W, x_old, x_new);

            lambda[k] = wek_wek(x_new, x_old);

            for (int i = 0; i < n; i++)
            {
                x_old[i] = x_new[i] / sqrt(wek_wek(x_new, x_new));
            }

            fprintf(wynik, "%d  % d  %7f \n", k, m, lambda[k]);
        }

        fprintf(wynik, "\n\n\n");

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                W[i][j] = W[i][j] - lambda[k] * x_old[i] * x_old[j];
            }
        }

        for (int i = 0; i < n; i++)
        {
            X[i][k] = x_old[i];
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            X_T[j][i] = X[i][j];
            C[i][j] = 0;
        }
    }

    mac_mac(X_T, A, C);
    mac_mac(C, X, D);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fprintf(macierz_D, "%12.6g ", D[i][j]);
        }
        fprintf(macierz_D, "\n");
    }

    fclose(wynik);
    fclose(macierz_D);

    return 0;
}
