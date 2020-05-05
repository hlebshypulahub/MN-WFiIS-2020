#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
// #include <unistd.h>
#define max(X,Y) ((X)>(Y)? (X):(Y))
#define min(X,Y) ((X)<(Y)? (X):(Y))
#define abs(X) ((X)>0? (X):-(X))

double ilSkalarany(int n, double* v1, double*v2)
{
	double sum = 0;
	for(int i=0; i<n; i++)
	{
		sum += v1[i] * v2[i];
	}
	return sum;
}
void iloczyn(int n, int m, double** A, double* x, double* y)
{
	for(int i=0; i<n; i++)
	{
		y[i] = 0.0;
		for(int j=max(0,i-m); j<=min(n-1, i+m); j++)
			y[i] += A[i][j] * x[j];
	}
}
void odejmowanie(int n, double* v1, double* v2, double* v_result)
{
	for(int i=0; i<n; i++)
		v_result[i] = v1[i] - v2[i];
}
void dodawanie(int n, double* v1, double* v2, double* v_result)
{
	for(int i=0; i<n; i++)
		v_result[i] = v1[i] + v2[i];	
}

int main()
{
	int i,j,k;
	int n = 1000;
	int m = 5;

	time_t t1, t2;
	double tDiff;

	FILE *fp = fopen("wyniki.dat", "w");

	double **A = (double**) malloc (n*sizeof(double*));
	for(i=0; i<n; i++)
		A[i] = (double*) malloc (n*sizeof(double));

	double *b = (double*) malloc (n*sizeof(double));
	double *x = (double*) malloc (n*sizeof(double));
	double *y = (double*) malloc (n*sizeof(double));
	double *r = (double*) malloc (n*sizeof(double));
	double *v = (double*) malloc (n*sizeof(double));

	double alfa;

	for(i=0; i<n; i++)
	{
		b[i] = i+1;
		x[i] = 0;
		for(j=0; j<n; j++)
		{
			if(abs(i - j) > m)
				A[i][j] = 0.0;
			else
			{
				A[i][j] = 1./(1+abs(i-j));
			}
		}
	}

	time(&t1);

	iloczyn(n, m, A, x, y);
	odejmowanie(n, b, y, r);
	for(i=0; i<n; i++)
		v[i] = r[i];

	int iteracja = 0;
	fprintf(fp, "Iteracja - wartość normy euklidesowej wektora reszt - alfa - beta - wartość normy euklidesowej wektora rozwiązań\n");
	while(sqrt(ilSkalarany(n, r,r)) > pow(10, -6))
	{
		iteracja++;
		iloczyn(n,m, A, v, y);
		double bottom = ilSkalarany(n, v, y);
		double il_r_r = ilSkalarany(n, r,r);

		alfa = il_r_r / bottom;

		for(i = 0; i<n ;i++)
		{
			x[i] =  x[i] + alfa*v[i];
			r[i] =  r[i] - alfa*y[i];
		}

		double beta = ilSkalarany(n, r,r) / il_r_r;
		for(i=0; i<n; i++)
		{
			v[i] = r[i] + beta*v[i];
		}

		printf("Iteracja: %d - %f - %f - %f - %f\n", iteracja, sqrt(ilSkalarany(n, r,r)), alfa, beta, sqrt(ilSkalarany(n, x,x)));
		fprintf(fp, "Iteracja: %d - %f - %f - %f - %f\n", iteracja, sqrt(ilSkalarany(n, r,r)), alfa, beta, sqrt(ilSkalarany(n, x,x)));
	}
	time(&t2);
	tDiff = difftime(t2, t1) * 1000;
	printf("CZAS: %f\n", tDiff);
	fclose(fp);
	return 0;
}
