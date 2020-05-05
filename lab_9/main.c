#include "gsl/gsl_linalg.h"
#include "gsl/gsl_math.h"
#include "math.h"
#include "stdio.h"

#define N 7
#define M 7

const int n = N + M;

double fun(double x)
{
    return sin(x);
}

unsigned long long int factorial(int n)
{
    unsigned long long int r;
    for (r = 1; n > 1; r *= (n--))
        ;
    return r;
}

double poch_0(int k)
{
    double wartosc;
    if (k % 2 == 0)
    {
        wartosc = 0;
    }
    else if (k % 2 == 1)
    {
        if (k > 0)
            wartosc = pow(-1, (k - 1) / 2);
        else if (k == 0)
            wartosc = 0;
    }

    return wartosc;
}

double R_n_m(gsl_vector *a, gsl_vector *b, double x)
{
    double P_n = 0;
    double Q_m = 0;

    for (int i = 0; i <= M; i++)
    {
        P_n += gsl_vector_get(a, i) * pow(x, i);
        Q_m += gsl_vector_get(b, i) * pow(x, i);
    }

    return P_n / Q_m;
}

int main()
{
    double temp;
    int signum;

    gsl_vector *c = gsl_vector_calloc(n + 1);
    gsl_vector *y = gsl_vector_calloc(M);
    gsl_vector *x = gsl_vector_calloc(M);
    gsl_vector *b = gsl_vector_calloc(M + 1);
    gsl_vector *a = gsl_vector_calloc(N + 1);
    gsl_matrix *A = gsl_matrix_calloc(M, M);
    gsl_permutation *p = gsl_permutation_alloc(M);

    /////////////// punkt 1 ///////////////

    for (int k = 0; k <= n; k++)
    {
        temp = poch_0(k) / factorial(k);
        gsl_vector_set(c, k, temp);
    }

    /////////////// punkt 2.1 ///////////////

    for (int i = 0; i <= M - 1; i++)
    {
        gsl_vector_set(y, i, -gsl_vector_get(c, N + 1 + i));

        for (int j = 0; j <= M - 1; j++)
        {
            gsl_matrix_set(A, i, j, gsl_vector_get(c, N - M + i + j + 1));
        }
    }

    gsl_linalg_LU_decomp(A, p, &signum);
    gsl_vector_set_zero(x);
    gsl_linalg_LU_solve(A, p, y, x);

    /////////////// punkt 2.2 ///////////////

    gsl_vector_set(b, 0, 1);

    for (int i = 0; i <= M - 1; i++)
    {
        gsl_vector_set(b, M - i, gsl_vector_get(x, i));
    }

    /////////////// punkt 3 ///////////////

    for (int i = 0; i <= N; i++)
    {
        temp = 0;

        for (int j = 0; j <= i; j++)
        {
            temp += gsl_vector_get(c, i - j) * gsl_vector_get(b, j);
        }

        gsl_vector_set(a, i, temp);
    }

    /////////////// punkt 4 ///////////////

    FILE *fp;
    fp = fopen("wynik.dat", "w");

    for (double X = -2 * M_PI; X <= 2 * M_PI; X += 0.0001)
    {
        fprintf(fp, "%f\t", X);
        fprintf(fp, "%f\t", fun(X));
        fprintf(fp, "%f\t", R_n_m(a, b, X));
        fprintf(fp, "\n");
    }

    fclose(fp);

    return 0;
}