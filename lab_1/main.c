#include <gsl/gsl_math.h>
#include <gsl/gsl_linalg.h>
#include <stdio.h>

int main()
{

    /// zmienne

    FILE *fp;

    int signum;
    int n = 4;
    int i = 0, j = 0, k = 0;

    float det_a;

    gsl_matrix *a = gsl_matrix_calloc(n, n);
    gsl_matrix *a_copy = gsl_matrix_calloc(n, n);
    gsl_matrix *a_abs = gsl_matrix_calloc(n, n);
    gsl_matrix *a_odwr = gsl_matrix_calloc(n, n);
    gsl_matrix *a_odwr_abs = gsl_matrix_calloc(n, n);
    gsl_matrix *c = gsl_matrix_calloc(n, n);

    gsl_vector *b = gsl_vector_calloc(n);

    gsl_vector *x1 = gsl_vector_calloc(n);
    gsl_vector *x2 = gsl_vector_calloc(n);
    gsl_vector *x3 = gsl_vector_calloc(n);
    gsl_vector *x4 = gsl_vector_calloc(n);

    gsl_permutation *p = gsl_permutation_alloc(n);

    ///

    fp = fopen("wynik.dat", "w");

    ///
    /// PUNKT 1 - Znaleźć rozkład LU macierzy A
    ///

    printf("Macierz a:\n");
    fprintf(fp, "Macierz a:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            gsl_matrix_set(a, i, j, 1.0 / (i + j + 2));
            gsl_matrix_set(a_copy, i, j, gsl_matrix_get(a, i, j));
            fprintf(fp, "%f ", gsl_matrix_get(a, i, j));
            printf("%f ", gsl_matrix_get(a, i, j));
        }
        printf("\n");
        fprintf(fp, "\n");
    }

    printf("\n");
    fprintf(fp, "\n");

    ///

    gsl_linalg_LU_decomp(a, p, &signum);

    ///
    /// PUNKT 2 - Zapisać do pliku: elementy diagonalne macierzy U oraz wyznacznik macierzy A
    ///

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%f ", gsl_matrix_get(a, i, j));
        }
        printf("\n");
    }

    ///

    det_a = 1;

    ///

    fprintf(fp, "Elementy diagonalne U:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i == j)
            {
                fprintf(fp, "%f ", gsl_matrix_get(a, i, j));
                det_a *= gsl_matrix_get(a, i, j);
            }
        }
    }

    ///

    printf("\nWyznacznik macierzy a:\n%g\n", det_a);
    fprintf(fp, "\n\nWyznacznik macierzy a:\n%g\n", det_a);

    ///
    /// PUNKT 3 - Znaleźć macierz odwrotną A^-1 rozwiązując n układów równań z wektorami wyrazów wolnych
    ///

    gsl_vector_set_zero(b);
    gsl_vector_set(b, 0, 1);
    gsl_linalg_LU_solve(a, p, b, x1);

    gsl_vector_set_zero(b);
    gsl_vector_set(b, 1, 1);
    gsl_linalg_LU_solve(a, p, b, x2);

    gsl_vector_set_zero(b);
    gsl_vector_set(b, 2, 1);
    gsl_linalg_LU_solve(a, p, b, x3);

    gsl_vector_set_zero(b);
    gsl_vector_set(b, 3, 1);
    gsl_linalg_LU_solve(a, p, b, x4);

    ///

    printf("\nMacierz odwrotna a^-1:\n");
    fprintf(fp, "\nMacierz odwrotna a^-1:\n");

    for (i = 0; i < n; i++)
    {
        printf("%f	", gsl_vector_get(x1, i));
        fprintf(fp, "%f	", gsl_vector_get(x1, i));

        printf("%f	", gsl_vector_get(x2, i));
        fprintf(fp, "%f	", gsl_vector_get(x2, i));

        printf("%f	", gsl_vector_get(x3, i));
        fprintf(fp, "%f	", gsl_vector_get(x3, i));

        printf("%f\n", gsl_vector_get(x4, i));
        fprintf(fp, "%f\n", gsl_vector_get(x4, i));
    }

    for (i = 0; i < n; i++)
    {
        gsl_matrix_set(a_odwr, 0, i, gsl_vector_get(x1, i));
        gsl_matrix_set(a_odwr, 1, i, gsl_vector_get(x2, i));
        gsl_matrix_set(a_odwr, 2, i, gsl_vector_get(x3, i));
        gsl_matrix_set(a_odwr, 3, i, gsl_vector_get(x4, i));
    }

    ///
    /// PUNKT 4 - Obliczyć iloczyn A*(A^-1)
    ///

    fprintf(fp, "\nIloczyn a * a^-1:\n");
    printf("\nIloczyn a * a^-1:\n");

    // wartosci sa wyzerowane przy alokacji

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            for (k = 0; k < n; k++)
            {
                gsl_matrix_set(c, i, j, gsl_matrix_get(c, i, j) + gsl_matrix_get(a_copy, i, k) * gsl_matrix_get(a_odwr, k, j));
            }
            fprintf(fp, "%g	\t\t", gsl_matrix_get(c, i, j));
            printf("%g \t\t", gsl_matrix_get(c, i, j));
        }
        printf("\n");
        fprintf(fp, "\n");
    }

    ///
    /// PUNKT 5 - Obliczyc wskaznik uwarunkowania
    ///

    /// Korzystamy z a_copy, bo a jest nadpisana macierza LU
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            gsl_matrix_set(a_abs, i, j, fabs(gsl_matrix_get(a_copy, i, j)));
        }
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            gsl_matrix_set(a_odwr_abs, i, j, fabs(gsl_matrix_get(a_odwr, i, j)));
        }
    }

    ///

    double a_norm = gsl_matrix_max(a_abs), a_odwr_norm = gsl_matrix_max(a_odwr_abs);

    ///

    double wsk_uwarun = a_norm * a_odwr_norm;

    ///
    
    printf("\nWskaznik uwarunkowania:\n%g\n", wsk_uwarun);
    fprintf(fp, "\nWskaznik uwarunkowania:\n%g\n", wsk_uwarun);

    ///

    fclose(fp);

    ///

    return 0;
}
