#include <gsl/gsl_math.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_eigen.h>
#include <stdio.h>
#include <math.h>

double delta(int i, int j)
{
    double d;
    d = (i == j ?  1 : 0);
    return d;
}

int main()
{
    FILE *a0;
    a0 = fopen("a0.dat", "w");
    FILE *a100;
    a100 = fopen("a100.dat", "w");
    FILE *eigen;
    eigen = fopen("eigen.dat", "w");

    double L = 10;
    double n = 200;
    double N = 1;
    int alfa = 0;
    double delta_x = (double)L / (n + 1);

    gsl_matrix *A = gsl_matrix_calloc(n, n);
    gsl_matrix *B = gsl_matrix_calloc(n, n);
    gsl_vector *x = gsl_vector_calloc(n);
    gsl_vector *ro = gsl_vector_calloc(n);
    gsl_vector *eval = gsl_vector_calloc(n);
    gsl_matrix *evec = gsl_matrix_calloc(n, n);
    gsl_eigen_gensymmv_workspace *w = gsl_eigen_gensymmv_alloc(n);

    for (alfa = 0; alfa <= 100; alfa += 2)
    {
        /// alfa
        fprintf(eigen, "%d ", alfa);

        /// x_{i}
        for (int i = 0; i < n; i++)
        {
            gsl_vector_set(x, i, (double)(-L / 2 + delta_x * (i + 1)));
        }

        /// ro(x)_{i}
        for (int i = 0; i < n; i++)
        {
            gsl_vector_set(ro, i, (double)(1 + 4 * alfa * pow(gsl_vector_get(x, i), 2)));
        }

        /// A, B
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                gsl_matrix_set(A, i, j, (double)((-delta(i, j + 1) + 2 * delta(i, j) - delta(i, j - 1)) / pow(delta_x, 2)));
                gsl_matrix_set(B, i, j, (gsl_vector_get(ro, i) / N) * delta(i, j));
            }
        }

        gsl_eigen_gensymmv(A, B, eval, evec, w);
        gsl_eigen_gensymmv_sort(eval, evec, GSL_EIGEN_SORT_ABS_ASC);

        for (int i = 0; i < 6; i++)
        {
            fprintf(eigen, "%f ", sqrt(gsl_vector_get(eval, i)));
        }
        fprintf(eigen, "\n");

        /// alfa = 0
        if (alfa == 0)
        {
            for (int j = 0; j < n; j++)
            {
                fprintf(a0, "%f ", gsl_vector_get(x, j));
                for (int i = 0; i < 6; i++)
                {
                    fprintf(a0, "%f ", gsl_matrix_get(evec, j, i));
                }
                fprintf(a0, "\n");
            }
        }

        /// alfa = 100
        if (alfa == 100)
        {
            for (int j = 0; j < n; j++)
            {
                fprintf(a100, "%f ", gsl_vector_get(x, j));
                for (int i = 0; i < 6; i++)
                {
                    fprintf(a100, "%f ", gsl_matrix_get(evec, j, i));
                }
                fprintf(a100, "\n");
            }
        }
    }

    fclose(a0);
    fclose(a100);
    fclose(eigen);

    return 0;
}
