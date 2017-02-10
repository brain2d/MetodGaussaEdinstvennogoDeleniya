#include <math.h>
#include <iostream>
#include <conio.h>
#include <stdio.h>

using namespace std;

double **A;			// ������� �������������
double *b;			// ������� ��������� ������������
double *x;			// ������� �������
int n;				// ����������� �������
double d = 1;			// �����������

						// ������� ������� (��������) ������� �������������
double **Matr(int n)
{
	double **T = new double *[n];
	for (int i = 0; i<n; i++)
		T[i] = new double[n];

	cout << " ������� ������� -> " << endl;

	for (int i = 0; i<n; i++)
		for (int j = 0; j<n; j++)
			cin >> T[i][j];

	return T;
}

// ������� �������� ������� ��������� �������������
double *Vekt(int n)
{
	b = new double[n];
	cout << "������� ������� ����. ����.!\n";
	for (int i = 0; i<n; i++)
		cin >> b[i];
	return b;

}

//�-�� ����������� � ������ i ������� ������ j ������� ���������� �� ����� �
void aplus(double **a, int i, int j, double c, int dim)
{
	for (int k = 0; k<dim; k++)
		a[i][k] += a[j][k] * c;
}

//�-�� ����������� � �������� i ������� �������� j ������� ����������� �� ����� �
void bplus(double *b, int i, int j, double c)
{
	b[i] += b[j] * c;
}

/*
//�-�� ��������� ��-�� ������ �� �����
void bumn(double b[],int n1,double n2){
b[n1]*=n2;
}

//�-�� ��������� ������ �-�� �� ����.
void aumn(double a[][50],int i,double k,int dim){
for (int j=0;j<dim;j++)
a[i][j]*=k;
}
*/


//�-�� �������� ������� 2� ��������� ������
void bswap(double *b, int n1, int n2) {
	double tmp;
	tmp = b[n1];
	b[n1] = b[n2];
	b[n2] = tmp;
}

//�-�� �������� ������� 2� ����� �-��
void aswap(double **a, int n1, int n2, int dim) {
	double tmp;
	for (int j = 0; j<dim; j++) {
		tmp = a[j][n1];
		a[j][n1] = a[j][n2];
		a[j][n2] = tmp;
	}
}


//�������� � ������������������ ����
void verh(double **a, double *b, int dim)
{
	double k;
	int l;

	for (int j = 0; j<dim; j++)
	{
		//�������� �� ����
		if (a[j][j] == 0)
		{
			if (j = dim - 1) goto p;
			l = j + 1;
			while ((a[l][j] == 0) && (l<dim - 1)) l++;
			if ((l == dim - 1) && (a[l][l] == 0))
			{
			p:
				cout << "������� A ���������!";
				d = 0;
				return;
			}
			else
			{
				aswap(a, j, l, dim);
				bswap(b, j, l);
			}

		}
		//��������
		for (int i = j + 1; i<dim; i++)
		{
			k = (-1)*a[i][j] / a[j][j];

			aplus(a, i, j, k, dim);
			bplus(b, i, j, k);
		}
	}

	return;
}

// ��������������� ������� ���������� �������
double sum(double **a, int i, double *b, double *x, int dim)
{
	double sum = 0;

	for (int j = i + 1; j<dim; j++)
		sum += a[i][j] * x[j];

	sum = (-sum) + b[i];
	return sum;

}

// ������� ������� ������� �
void X(double **a, double *b, double *x, int n)
{
	for (int i = n - 1; i >= 0; i--)
		x[i] = sum(a, i, b, x, n) / a[i][i];

	return;
}

// ������� ������ ������� �� �����
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

// ������� ������ ������� �� �����
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

	cout << "������� ����������� ������� �������������\n";
	cin >> n;

	// ������� ������� � ������� ����. ����.
	A = Matr(n);
	b = Vekt(n);

	x = new double[n];
	for (i = 0; i<n; i++)
		x[i] = 0;

	//prob3();

	cout << "������� ��������� �����:\n";
	print(A, b, n);

	//���������� � ������������������ ����
	verh(A, b, n);
	if (d == 0) goto l;

	cout << "����������������� ������� ��������� �����:\n";
	print(A, b, n);

	// ����� �������
	X(A, b, x, n);

	cout << "����� ������� �����:\n";
	print_v("X", x, n);

l:

	_getch();
}