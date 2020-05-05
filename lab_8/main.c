#include "gsl/gsl_linalg.h"
#include "gsl/gsl_math.h"
#include "math.h"
#include "stdio.h"

const double xmin = -5.0;
const double xmax = 5.0;

const double alfa = 0.0;
const double beta = 0.0;

double fun1(double x)
{
    return (1 / (1 + (x * x)));
}

double fun2(double x)
{
    return cos(2 * x);
}

double delta(int n)
{
    return (xmax - xmin) / (double)(n - 1);
}

double wylicz_d(double h, double h1, double y, double y1, double y2)
{
    return (6.0 / (h + h1)) * ((y2 - y1) / h1 - (y1 - y) / h);
}

void wyznacz_M(double *x, double *y, double *m,
               int n, double alfa, double beta)
{
    gsl_matrix *A = gsl_matrix_calloc(n, n);
    gsl_vector *d = gsl_vector_calloc(n);
    gsl_vector_set(d, 0, alfa);
    gsl_vector_set(d, n - 1, beta);

    double lambda[n];
    double miu[n];

    for (int i = 1; i < n - 1; i++)
    {
        gsl_vector_set(d, i, wylicz_d((x[i] - x[i - 1]), (x[i + 1] - x[i]), y[i - 1], y[i], y[i + 1]));
    }
    gsl_matrix_set(A, 0, 0, 1.0);
    gsl_matrix_set(A, n - 1, n - 1, 1.0);
    for (int i = 1; i < n - 1; i++)
    {
        gsl_matrix_set(A, i, i, 2.0);
    }
    for (int i = 2; i < n; i++)
    {
        lambda[i] = (x[i + 1] - x[i]) / ((x[i] - x[i - 1]) + (x[i + 1] - x[i]));
        gsl_matrix_set(A, i - 1, i, lambda[i - 2]);
    }
    for (int i = 0; i < n - 2; i++)
    {
        miu[i] = 1 - lambda[i];
        gsl_matrix_set(A, i + 1, i, miu[i]);
    }

    gsl_linalg_HH_svx(A, d);
    for (int i = 0; i < n; i++)
    {
        m[i] = gsl_vector_get(d, i);
    }

    gsl_vector_free(d);
    gsl_matrix_free(A);
}

double wyznacz_Sx(double *x, double *y, double *m, int n, double _x)
{
    double Sx = 0;
    int i = 0;

    for (int j = 1; j < n; j++)
    {
        if (_x >= x[j - 1] && _x <= x[j])
        {
            i = j;
            break;
        }
    }
    
    double h = x[i] - x[i - 1];
    double A = ((y[i] - y[i - 1]) / h) - (h / 6) * (m[i] - m[i - 1]);
    double B = y[i - 1] - (m[i - 1] * h * h) / 6;

    Sx = m[i - 1] * (pow((x[i] - _x), 3) / (6.0 * h)) +
         m[i] * (pow((_x - x[i - 1]), 3) / (6.0 * h)) +
         A * (_x - x[i - 1]) + B;

    return Sx;
}
void policz(int n, FILE *file1, FILE *file2)
{
    double x[n];
    double y[n];
    double m[n];
    double cos_x[n];
    double cos_y[n];
    double cos_m[n];
    for (int i = 0; i < n; i++)
    {
        x[i] = y[i] = cos_x[i] = cos_y[i] = 0.0;
        x[i] = xmin + delta(n) * i;
        y[i] = fun1(x[i]);
        cos_x[i] = xmin + delta(n) * i;
        cos_y[i] = fun2(cos_x[i]);
    }
    wyznacz_M(x, y, m, n, alfa, beta);
    wyznacz_M(cos_x, cos_y, cos_m, n, alfa, beta);

    for (int i = 0; i <= 1000; i++)
    {
        double _x = xmin + 0.01 * i;
        double Sx = wyznacz_Sx(x, y, m, n, _x);
        fprintf(file1, "%g %g\n", _x, Sx);
    }
    for (int i = 0; i <= 1000; i++)
    {
        double _x = xmin + 0.01 * i;
        double Sx = wyznacz_Sx(cos_x, cos_y, cos_m, n, _x);
        fprintf(file2, "%g %g\n", _x, Sx);
    }
    fprintf(file1, "\n\n");
    fprintf(file2, "\n\n");
}

int main()
{
    FILE *file1;
    file1 = fopen("f1.dat", "w");
    FILE *file2;
    file2 = fopen("f2.dat", "w");
    FILE *file3;
    file3 = fopen("pochodne.dat", "w");

    policz(5, file1, file2);
    policz(8, file1, file2);
    policz(21, file1, file2);

    int n = 10;
    double sigma = 0.01;
    double x[n];
    double y[n];
    double m[n];
    double poch[n];
    for (int i = 0; i < n; i++)
    {
        x[i] = y[i] = poch[i] = 0.0;
        x[i] = xmin + delta(n) * i;
        y[i] = fun1(x[i]);
        poch[i] = (fun1(x[i] - sigma) - 2 * fun1(x[i]) + fun1(x[i] + sigma)) / (sigma * sigma);
    }
    wyznacz_M(x, y, m, n, alfa, beta);

    for (int i = 0; i < n; i++)
    {
        fprintf(file3, " %g   %g  %g \n", x[i], m[i], poch[i]);
    }

    fclose(file1);
    fclose(file2);
    fclose(file3);

    return 0;
}