#include <math.h>
#include <iostream>
#include <conio.h>
#include <stdio.h>

using namespace std;

double **A;			// Матрица коэффициентов
double *b;			// Столбец свободных коэфициентов
double *x;			// Столбец решений
int n;				// размерность матрицы
double d = 1;			// детерминант

						// Функция задания (создания) матрицы коэфиициентов
double **Matr(int n)
{
	double **T = new double *[n];
	for (int i = 0; i<n; i++)
		T[i] = new double[n];

	cout << " Введите матрицу -> " << endl;

	for (int i = 0; i<n; i++)
		for (int j = 0; j<n; j++)
			cin >> T[i][j];

	return T;
}

// Функция создания столбца свободных коэффициентов
double *Vekt(int n)
{
	b = new double[n];
	cout << "Введите столбец своб. коэф.!\n";
	for (int i = 0; i<n; i++)
		cin >> b[i];
	return b;

}

//ф-ия прибавления к строке i матрицы строки j матрицы умноженной на число с
void aplus(double **a, int i, int j, double c, int dim)
{
	for (int k = 0; k<dim; k++)
		a[i][k] += a[j][k] * c;
}

//ф-ия прибавления к элементу i вектора элемента j вектора умноженного на число с
void bplus(double *b, int i, int j, double c)
{
	b[i] += b[j] * c;
}

/*
//ф-ия умножения эл-та векора на число
void bumn(double b[],int n1,double n2){
b[n1]*=n2;
}

//ф-ия умножения строки м-цы на коэф.
void aumn(double a[][50],int i,double k,int dim){
for (int j=0;j<dim;j++)
a[i][j]*=k;
}
*/


//ф-ия перемены местами 2х элементов векора
void bswap(double *b, int n1, int n2) {
	double tmp;
	tmp = b[n1];
	b[n1] = b[n2];
	b[n2] = tmp;
}

//ф-ия перемены местами 2х строк м-цы
void aswap(double **a, int n1, int n2, int dim) {
	double tmp;
	for (int j = 0; j<dim; j++) {
		tmp = a[j][n1];
		a[j][n1] = a[j][n2];
		a[j][n2] = tmp;
	}
}


//приводим к верхнетреугольному виду
void verh(double **a, double *b, int dim)
{
	double k;
	int l;

	for (int j = 0; j<dim; j++)
	{
		//проверка на ноль
		if (a[j][j] == 0)
		{
			if (j = dim - 1) goto p;
			l = j + 1;
			while ((a[l][j] == 0) && (l<dim - 1)) l++;
			if ((l == dim - 1) && (a[l][l] == 0))
			{
			p:
				cout << "Матрица A вырождена!";
				d = 0;
				return;
			}
			else
			{
				aswap(a, j, l, dim);
				bswap(b, j, l);
			}

		}
		//зануляем
		for (int i = j + 1; i<dim; i++)
		{
			k = (-1)*a[i][j] / a[j][j];

			aplus(a, i, j, k, dim);
			bplus(b, i, j, k);
		}
	}

	return;
}

// Вспомогательная функция вычисления решения
double sum(double **a, int i, double *b, double *x, int dim)
{
	double sum = 0;

	for (int j = i + 1; j<dim; j++)
		sum += a[i][j] * x[j];

	sum = (-sum) + b[i];
	return sum;

}

// Функция считает решение х
void X(double **a, double *b, double *x, int n)
{
	for (int i = n - 1; i >= 0; i--)
		x[i] = sum(a, i, b, x, n) / a[i][i];

	return;
}

// Функция вывода системы на экран
void print(double **a, double *b, int n)
{
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<n; j++)
		{
			printf("%5.2lf", a[i][j]);
			cout << "*X" << j + 1;
			if (j<n - 1) cout << " + ";
		}

		cout << " = " << b[i];
		cout << "\n";
	}

	return;
}

// Функция вывода вектора на экран
void print_v(char *p, double *t, int n)
{
	for (int i = 0; i<n; i++)
		cout << p << "[" << i << "]=" << t[i] << endl;
	return;

}


void prob3()
{
	n = 3;
	A[0][0] = 2;
	A[0][1] = 3;
	A[0][2] = 1;
	A[1][0] = -4;
	A[1][1] = -2;
	A[1][2] = 6;
	A[2][0] = 8;
	A[2][1] = 12;
	A[2][2] = 6;

	b[0] = 34;
	b[1] = -48;
	b[2] = 138;

}

void main() {
	setlocale(LC_ALL, "Russian");

	int i, j;

	cout << "Введите размерность матрицы коэффициентов\n";
	cin >> n;

	// задание матрицы и столбца своб. коэф.
	A = Matr(n);
	b = Vekt(n);

	x = new double[n];
	for (i = 0; i<n; i++)
		x[i] = 0;

	//prob3();

	cout << "Система уравнений такая:\n";
	print(A, b, n);

	//приведение в верхнетреугольномц виду
	verh(A, b, n);
	if (d == 0) goto l;

	cout << "Верхнетреугольная система уравнений такая:\n";
	print(A, b, n);

	// Поиск решения
	X(A, b, x, n);

	cout << "Набор решений такой:\n";
	print_v("X", x, n);

l:

	_getch();
}