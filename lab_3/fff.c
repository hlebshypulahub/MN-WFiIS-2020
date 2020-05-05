#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 1000
#define m 10

void iloczynMW(float a[N][N], float wektor_x[N][1], float wektor_temp[N][1], const int n)
{
	for (int i = 0; i < n; i++)
	{
		wektor_temp[i][0] = 0;
		for (int j = fmax(0, i - m); j <= fmin(i + m, n - 1); j++)
		{
			wektor_temp[i][0] += (a[i][j] * wektor_x[j][0]);
		}
	}
}

float iloczynSkalarny(float wektor_1[N][1], float wektor_2[N][1], const int n)
{
	float wynik = 0.0;
	for (int i = 0; i < N; i++)
		wynik += wektor_1[i][0] * wektor_2[i][0];

	return wynik;
}

void sumWektor(float wektor_1[N][1], float wektor_2[N][1], const int n)
{
	for (int i = 0; i < n; i++)
		wektor_2[i][0] = wektor_1[i][0] + wektor_2[i][0];
}

int main(void)
{

	float licznik = 0.0;
	float mianownik = 0.0;
	float alfa = 0.0;
	float A[N][N];
	float b[N][1];
	float x[N][1];
	float r[N][1];
	float temp[N][1];
	FILE *fpa = fopen("zad_a.dat", "w");
	FILE *fpb = fopen("zad_b.dat", "w");

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (abs(i - j) > m)
			{
				A[i][j] = 0.0;
			}
			else
			{
				A[i][j] = 1.0 / (1.0 + abs(i - j));
			}
		}
	}

	for (int i = 0; i < N; i++)
		b[i][0] = i;

	int k = 0;

	for (int i = 0; i < N; i++)
		x[i][0] = 0.0;

	do
	{
		iloczynMW(A, x, temp, N);

		for (int i = 0; i < N; i++)
			r[i][0] = b[i][0] - temp[i][0];

		iloczynMW(A, r, temp, N);
		licznik = iloczynSkalarny(r, r, N);
		mianownik = iloczynSkalarny(r, temp, N);
		alfa = licznik / mianownik;

		for (int i = 0; i < N; i++)
			temp[i][0] = r[i][0] * alfa;
		sumWektor(temp, x, N);

		k++;
		printf("%d ", k);
		printf("%.6f ", sqrt(iloczynSkalarny(r, r, N)));
		printf("%g ", alfa);
		printf("%.6f ", sqrt(iloczynSkalarny(x, x, N)));
		printf("\n");

		fprintf(fpa, "%d \t %f \t %f \t %f\n", k, sqrt(iloczynSkalarny(r, r, N)), alfa, sqrt(iloczynSkalarny(x, x, N)));

	} while (sqrt(iloczynSkalarny(r, r, N)) > pow(10, -6) && k < 500);

	for (int i = 0; i < N; i++)
		x[i][0] = 1.0;

	k = 0;

	do
	{
		iloczynMW(A, x, temp, N);

		for (int i = 0; i < N; i++)
			r[i][0] = b[i][0] - temp[i][0];

		iloczynMW(A, r, temp, N);
		licznik = iloczynSkalarny(r, r, N);
		mianownik = iloczynSkalarny(r, temp, N);
		alfa = licznik / mianownik;

		for (int i = 0; i < N; i++)
			temp[i][0] = r[i][0] * alfa;
		sumWektor(temp, x, N);

		k++;
		printf("%d ", k);
		printf("%.6f ", sqrt(iloczynSkalarny(r, r, N)));
		printf("%g ", alfa);
		printf("%.6f ", sqrt(iloczynSkalarny(x, x, N)));
		printf("\n");

		fprintf(fpb, "%d \t %f \t %f \t %f\n", k, sqrt(iloczynSkalarny(r, r, N)), alfa, sqrt(iloczynSkalarny(x, x, N)));

	} while (sqrt(iloczynSkalarny(r, r, N)) > pow(10, -6) && k < 500);

	fclose(fpa);
	fclose(fpb);

	return 0;
}