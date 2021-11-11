#include <iostream>
#include <fstream>
using namespace std;

int** c;

void MatrixAdd(int** a, int** b, int** temp, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			temp[i][j] = a[i][j] + b[i][j];
		}
	}
}

void MatrixSub(int** a, int** b, int** temp, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			temp[i][j] = a[i][j] - b[i][j];
		}
	}
}

void Strassen( int** a, int** b, int** c, int n) {
	if (n <= 1) {
		c[0][0] = a[0][0] * b[0][0];
	}
	else {
		int div = n / 2;
		int** a11 = new int *[div], ** a12 = new int* [div], ** a21 = new int* [div], ** a22 = new int* [div];
		int** b11 = new int* [div], ** b12 = new int* [div], ** b21 = new int* [div], ** b22 = new int* [div];
		int** c11 = new int* [div], ** c12 = new int* [div], ** c21 = new int* [div], ** c22 = new int* [div];
		int** m1 = new int* [div], ** m2 = new int* [div], ** m3 = new int* [div], ** m4 = new int* [div];
		int** m5 = new int* [div], ** m6 = new int* [div], ** m7 = new int* [div];
		int** Atemp = new int* [div], ** Btemp = new int* [div];


		for (int i = 0; i <= n/2; i++) {
			a11[i] = new int[div];
			a12[i] = new int[div];
			a21[i] = new int[div];
			a22[i] = new int[div];

			b11[i] = new int[div];
			b12[i] = new int[div];
			b21[i] = new int[div];
			b22[i] = new int[div];

			c11[i] = new int[div];
			c12[i] = new int[div];
			c21[i] = new int[div];
			c22[i] = new int[div];

			m1[i] = new int[div];
			m2[i] = new int[div];
			m3[i] = new int[div];
			m4[i] = new int[div];
			m5[i] = new int[div];
			m6[i] = new int[div];
			m7[i] = new int[div];

			Atemp[i] = new int[div];
			Btemp[i] = new int[div];
		}

		for (int i = 0; i < div; i++) {
			for (int j = 0; j < div; j++) {
				a11[i][j] = a[i][j];
				b11[i][j] = b[i][j];
				a12[i][j] = a[i][j + div];
				b12[i][j] = b[i][j + div];
				a21[i][j] = a[i + div][j];
				b21[i][j] = b[i + div][j];
				a22[i][j] = a[i + div][j + div];
				b22[i][j] = b[i + div][j + div];
			}
		}
		//m1
		MatrixAdd(a11, a22, Atemp, div);
		MatrixAdd(b11, b22, Btemp, div);
		Strassen(Atemp, Btemp, m1, div);
		//m2
		MatrixAdd(a21, a22, Atemp, div);
		Strassen(Atemp, b11, m2, div);
		//m3
		MatrixSub(b12, b22, Btemp, div);
		Strassen(a11, Btemp, m3, div);
		//m4
		MatrixSub(b21, b11, Btemp, div);
		Strassen(a22, Btemp, m4, div);
		//m5
		MatrixAdd(a11, a12, Atemp, div);
		Strassen(Atemp, b22, m5, div);
		//m6
		MatrixSub(a21, a11, Atemp, div);
		MatrixAdd(b11, b12, Btemp, div);
		Strassen(Atemp, Btemp, m6, div);
		//m7
		MatrixSub(a12, a22, Atemp, div);
		MatrixAdd(b21, b22, Btemp, div);
		Strassen(Atemp, Btemp, m7, div);
		//c12, c21
		MatrixAdd(m3, m5, c12, div);
		MatrixAdd(m2, m4, c21, div);
		//c11
		MatrixAdd(m1, m4, Atemp, div);
		MatrixSub(Atemp, m5, Btemp, div);
		MatrixAdd(Btemp, m7, c11, div);
		//c22
		MatrixAdd(m1, m3, Atemp, div);
		MatrixSub(Atemp, m2, Btemp, div);
		MatrixAdd(Btemp, m6, c22, div);


		for (int i = 0; i < div; i++)
		{
			for (int j = 0; j < div; j++)
			{
				c[i][j] = c11[i][j];
				c[i][j + div] = c12[i][j];
				c[i + div][j] = c21[i][j];
				c[i + div][j + div] = c22[i][j];
			}
		}
	}
}

void main() {
	ifstream input("input_2.txt");
	int n;
	input >> n;
	int** a = new int* [n];
	int** b = new int* [n];
	c = new int* [n];
	for (int i = 0; i < n; i++) {
		a[i] = new int[n];
		b[i] = new int[n];
		c[i] = new int[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			input >> a[i][j];
		}
	}
	input.ignore();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			input >> b[i][j];
		}
	}
	Strassen(a, b, c, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << c[i][j] << " ";
		}
		cout << endl;
	}
}