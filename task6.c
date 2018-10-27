#include <math.h>
#include <stdio.h>

double y(double x)
{
	return sin(x);
}

double P(double x, double a[5])
{
	double l[5];
	double l_xi[5];
	for (int i = 0; i < 5; i++)
	{
		l[i] = 1;
		l_xi[i] = 1;
		for (int j = 0; j < 5; j++)
		{
			if (j != i)
			{
				l[i] = l[i] * (x - a[j]);
				l_xi[i] = l_xi[i] * (a[i] - a[j]);
			}
		}
	}

	double P = 0;
	for (int i = 0; i < 5; i++)
	{
		P += y(a[i]) * l[i] / l_xi[i];
	}

	return P;
}

double Pl(double x, double a[5])
{
	double P = 0;
	for (int i = 0; i < 5; i++)
	{
		P += a[i] * pow(x, i);
	}
	return P;
}

int main(int argc, char** argv)
{
	double x[5];
	double al[5];
	al[0] = y(x[0]);
	for (int i = 1; i < 5; i++)
	{
		al[i] = (y(x[i]) - al[0]) / (x[i] - x[0]);
		for (int j = i-1; j > 0; j--)
		{
			al[i] = (al[i] - y(x[j])) / (x[i] - x[j]);
		}
		printf("al[%d] = %lf\n", i, al[i]);
	}
	for (int i = 0; i < 5; i++)
	{
		x[i] = i * M_PI / 16;
	}

	FILE *file = fopen("graph.txt", "w");
	for (int k = -50; k < 50; k++)
	{
		double p = k * M_PI / 48;
		double dP = P(p, x) - y(p);
		double dPl = Pl(p, al) - y(p);
		fprintf(file, "%lf	%lf	%lf\n", p, dP, dPl);
	}
	fclose(file);

	return 0;
}
