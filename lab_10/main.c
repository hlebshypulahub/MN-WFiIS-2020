#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double fun(double x)
{
    return log(pow(x, 5) + 3 * pow(x, 2) + x + 9);
}

double fun_x6(double x)
{
    return pow(x, 6);
}

int main()
{
    /////////////
    // zmienne //
    /////////////

    FILE *log_sqrt;
    log_sqrt = fopen("log_sqrt.dat", "w");
    FILE *log_1_3;
    log_1_3 = fopen("log_1_3.dat", "w");
    FILE *x6_sqrt;
    x6_sqrt = fopen("x6_sqrt.dat", "w");
    FILE *x6_1_3;
    x6_1_3 = fopen("x6_1_3.dat", "w");

    double x_a = -0.5;
    double x_b = 1.0;
    double x_dokladne = -0.1673198;

    double x_min;

    double r = (sqrt(5) - 1) / 2;
    double epsilon = pow(10, -6);
    double x1 = x_a;
    double x2 = x_b;

    //////////// log sqrt ////////////

    for (int i = 0; fabs(x_a - x_b) > epsilon; i++)
    {
        x1 = x_a + r * r * (x_b - x_a);
        x2 = x_a + r * (x_b - x_a);

        if (fun(x2) > fun(x1))
        {
            x_b = x2;
        }
        else
        {
            x_a = x1;
        }

        fprintf(log_sqrt, "%d	%f	%f	%f	%f\n", i, x_a, x_b, x_min = (x_a + x_b) / 2, fabs(x_min - x_dokladne));
    };

    //////////// log 3 parts ////////////

    r = 1.0 / 3.0;
    x_a = -0.5;
    x_b = 1.0;
    x1 = x_a;
    x2 = x_b;

    for (int i = 0; fabs(x_a - x_b) > epsilon; i++)
    {
        x1 = x_a + r * (x_b - x_a);
        x2 = x_a + 2 * r * (x_b - x_a);

        if (fun(x2) > fun(x1))
        {
            x_b = x2;
        }
        else
        {
            x_a = x1;
        }

        fprintf(log_1_3, "%d	%f	%f	%f	%f\n", i, x_a, x_b, x_min = (x_a + x_b) / 2, fabs(x_min - x_dokladne));
    }

    //////////// x6 sqrt ////////////

    r = (sqrt(5) - 1) / 2;
    x_a = -4.0;
    x_b = 1.0;
    x1 = x_a;
    x2 = x_b;
    x_dokladne = 0.0;

    for (int i = 0; fabs(x_a - x_b) > epsilon; i++)
    {
        x1 = x_a + r * r * (x_b - x_a);
        x2 = x_a + r * (x_b - x_a);

        if (fun_x6(x2) > fun_x6(x1))
        {
            x_b = x2;
        }
        else
        {
            x_a = x1;
        }

        fprintf(x6_sqrt, "%d	%f	%f	%f	%f\n", i, x_a, x_b, x_min = (x_a + x_b) / 2, fabs(x_min - x_dokladne));
    }

    //////////// x6 3 parts ////////////

    r = 1.0 / 3.0;
    x_a = -4.0;
    x_b = 1.0;
    x1 = x_a;
    x2 = x_b;

    for (int i = 0; fabs(x_a - x_b) > epsilon; i++)
    {
        x1 = x_a + r * (x_b - x_a);
        x2 = x_a + 2 * r * (x_b - x_a);

        if (fun_x6(x2) > fun_x6(x1))
        {
            x_b = x2;
        }
        else
        {
            x_a = x1;
        }

        fprintf(x6_1_3, "%d	%f	%f	%f	%f\n", i, x_a, x_b, x_min = (x_a + x_b) / 2, fabs(x_min - x_dokladne));
    }

    return 0;
}
