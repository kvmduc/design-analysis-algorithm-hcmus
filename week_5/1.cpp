#include <iostream>
#include <fstream>

using namespace std;
int** S;

void Traceback(int ** arr, int max, int n, int index) {
	int* result = new int[n+1];
	result[n] = arr[n][index];
	for (int i = n - 1; i >= 1; i--) {
		if (S[i][index] >= S[i][index - 1]) {
			result[i] = arr[i][index];
		}
		else {
			result[i] = arr[i][index-1];
			index = index - 1;
		}
	}
	for (int i = 1; i <= n; i++) {
		cout << result[i] << " ";
	}
}


void MaxSumTriangle(int** arr, int n) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			S[i][j] = max(S[i - 1][j], S[i - 1][j - 1]) + arr[i][j];
		}
	}
	int max = arr[n][0];
	int index;
	for (int j = 1; j <= n; j++) {
		if (S[n][j] > max) {
			max = S[n][j];
			index = j;
		}
	}
	cout << max << endl;
	Traceback(arr, max, n, index);
}



void main() {
	ifstream input("input_1.txt");
	int n;
	input >> n;
	int** arr = new int* [n + 1];
	for (int i = 0; i <= n; i++) {
		arr[i] = new int[n + 1];
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			input >> arr[i][j];
		}
	}
	for (int i = 0; i <= n; i++) {
		arr[i][0] = 0;
		arr[i][i + 1] = 0;
	}
	S = new int* [n + 1];
	for (int i = 0; i <= n; i++) {
		S[i] = new int[n + 1];
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			input >> S[i][j];
		}
	}
	for (int i = 0; i <= n; i++) {
		S[i][0] = 0;
		S[i][i + 1] = 0;
	}
	MaxSumTriangle(arr, n);
}