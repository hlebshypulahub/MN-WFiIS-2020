#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.1415
const double xmin = -5.0;
const double xmax = 5.0;

double fun(double x)
{
    return exp(-pow(x, 2));
}

double Lagraunge(double *x, double *y, int n, double _x)
{

    double wielomian = 0.0;

    for (int i = 0; i <= n; i++)
    {
        double tmp = 1.0;

        for (int j = 0; j <= n; j++)
        {
            if (j != i)
            {
                tmp = tmp * ((_x - x[j]) / (x[i] - x[j]));
            }
        }

        wielomian = wielomian + y[i] * tmp;
    }

    return wielomian;
}

double Czebyszew(int n, int m)
{
    return 0.5 * ((xmax - xmin) * cos(PI * (2.0 * (double)m + 1.0) / (2.0 * (double)n + 2.0)) + (xmin + xmax));
}

void calculate(int n, FILE *file1, FILE *file2)
{
    double x[n + 1];
    double y[n + 1];
    double cx[n + 1];
    double cy[n + 1];

    double krok = (xmax - xmin) / (double)n;

    for (int i = 0; i <= n; i++)
    {
        x[i] = y[i] = cx[i] = cy[i] = 0.0;
        x[i] = xmin + krok * i;
        y[i] = fun(x[i]);
        cx[i] = Czebyszew(n, i);
        cy[i] = fun(cx[i]);
    }

    double wielom = 0.0;

    for (int i = 0; i <= 1000; i++)
    {
        double xZnaczenia = xmin + 0.01 * i;
        wielom = Lagraunge(x, y, n, xZnaczenia);
        fprintf(file1, "%g	", xZnaczenia);
        fprintf(file1, "%g\n", wielom);
    }

    for (int i = 0; i <= 1000; i++)
    {
        double xZnaczenia = xmin + 0.01 * i;
        double wielom = Lagraunge(cx, cy, n, xZnaczenia);
        fprintf(file2, "%g	", xZnaczenia);
        fprintf(file2, "%g\n", wielom);
    }
}

int main(void)
{

    int n_5 = 5;
    int n_10 = 10;
    int n_15 = 15;
    int n_20 = 20;

    FILE *zad_1;
    zad_1 = fopen("zad_1.dat", "w");
    FILE *zad_2;
    zad_2 = fopen("zad_2.dat", "w");

    calculate(n_5, zad_1, zad_2);
    fprintf(zad_1, "\n \n");
    fprintf(zad_2, "\n \n");

    calculate(n_10, zad_1, zad_2);
    fprintf(zad_1, "\n \n");
    fprintf(zad_2, "\n \n");

    calculate(n_15, zad_1, zad_2);
    fprintf(zad_1, "\n \n");
    fprintf(zad_2, "\n \n");

    calculate(n_20, zad_1, zad_2);
    fclose(zad_1);
    fclose(zad_2);

    return 0;
}