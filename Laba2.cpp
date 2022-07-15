#include <iostream>
#include <clocale>
#include <cmath>
#include <fstream>
#include <ctime>

using namespace std;

int **Massiv(const int n)
{
	int** array;
	array = new int* [n];
	for (int i = 0; i < n; i++)
	{
		array[i] = new int[n];
	}
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (rand() % 2)
			{
				array[i][j] = 1;
			}
			else
			{
				array[i][j] = -1;
			}
		}
	return array;
}

int Sosedup(int **gy, int a, int b, const int n)
{
	int h;
	if(a == 0)
	{
		h = gy[n - 1][b];
	}
	else
	{
		h = gy[a - 1][b];
	}
	return h;
}

int Soseddown(int** gy, int a, int b, const int n)
{
	int u;
	if (a == n - 1)
	{
		u = gy[0][b];
	}
	else
	{
		u = gy[a + 1][b];
	}
	return u;
}

int Sosedleft(int** gy, int a, int b, const int n)
{
	int k;
	if (b == 0)
	{
		k = gy[a][n - 1];
	}
	else
	{
		k = gy[a][b - 1];
	}
	return k;
}

int Sosedright(int** gy, int a, int b, const int n)
{
	int l;
	if (b == n - 1)
	{
		l = gy[a][0];
	}
	else
	{
		l = gy[a][b + 1];
	}
	return l;
}
double Energ(int** gy,int a, int b,const int n)
{
	double Ei = -1 * ((gy[a][b] * Sosedup(gy, a, b, n)) + (gy[a][b] * Soseddown(gy, a, b, n)) + (gy[a][b] * Sosedleft(gy, a, b, n)) + (gy[a][b] * Sosedright(gy, a, b, n)));
//	cout << "Энергия взаимодействия рандомного спина с его 4 соседями:" << Ei << endl;
	return Ei;
}

double Energfull(int** gy, const int n)
{
	double Efull = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			Efull += Energ(gy, i, j, n);
		}
	}
	Efull /= ((double)n * n);
	cout << "Полная энергия системы:" << Efull << endl;
	return Efull;
}

double Magnit(int** gy, const int n)
{
	double M = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			M += gy[i][j];
		}
	}
	if (M < 0)
	{
		M = M * (- 1);
	}
	M = M / ((double)n * n);
//	M = fabs(M) / ((double)n * n);
	cout << "Намагниченность всей системы:" << M << endl;
	return M;
}

void Metropolis(int** gy,int a,int b, const int n)
{
	ofstream f{ "1.txt" };
	double E1 = 0, E2 = 0;
	for (double t = 0.01; t < 4.0; t += 0.1)
	{
		for (double i = 0; i < 1000000; i++)
		{
			a = rand() % n;
			b = rand() % n;
			E1 = Energ(gy, a, b, n);
			E2 = E1 * (-1);
			if (E1 > E2)
			{
				gy[a][b] *= (-1);
			}
			else
			{
				double p = exp((E1 - E2) / t);
				if (((double)rand() / (double)RAND_MAX) <= p)
				{
					gy[a][b] *= (-1);
				}
			}
		}
		cout << "Температура =" << t << endl;
		f << t << "\t" << Energfull(gy, n) << "\t" << "\t" << Magnit(gy, n) << endl;
	}
}

int main()
{
	setlocale(LC_CTYPE, "rus");
	const int n = 29;
	int a = 0, b = 0;
//	ifstream f("1.txt");
///////////////////////////2
	int **gy =Massiv(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << " " << gy[i][j] << " ";
		}
		cout << endl;
	}
	cout << "\n";
	int** array = gy;
///////////////////////////3
	a = rand() % n;
	b = rand() % n;
	cout << "First index:" << a << endl;
	cout << "Second index:" << b << endl;
	cout << "Случайно выбранный элемент:" << gy[a][b] << endl;
///////////////////////////4
	cout << "Верхний сосед:" << Sosedup(gy, a, b, n) << endl;
	cout << "Нижний сосед:" << Soseddown(gy, a, b, n) << endl;
	cout << "Левый сосед:" << Sosedleft(gy, a, b, n) << endl;
	cout << "Правый сосед:" << Sosedright(gy, a, b, n) << endl;
///////////////////////////5
	Energ(gy, a, b, n);
///////////////////////////6
	Energfull(gy, n);
///////////////////////////7
	Magnit(gy, n);
///////////////////////////9
	Metropolis(gy, a, b, n);
//////////////////////////delete
	for (int i = 0; i < a; i++)
	{
		delete[]array[i];
	}
	delete[]array;
	return 0;
}
//code
//code1