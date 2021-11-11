#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

void LongestCommonSubSeq(string a, int m, string b, int n) {
	int** matrix = new int* [m+1];
	for (int i = 0; i <= m; i++) {
		matrix[i] = new int[n + 1];
	}
	for (int i = 0; i <= m; i++) {
		matrix[i][0] = 0;
	}
	for (int j = 0; j <= n; j++) {
		matrix[0][j] = 0;
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (a[i-1] == b[j-1]) {
				matrix[i][j] = 1 + matrix[i - 1][j - 1];
			}
			else {
				matrix[i][j] = max(matrix[i][j - 1], matrix[i - 1][j - 1]);
			}
		}
	}
	int i = m, j = n;
	string result = "";
	while (i >= 1 && j >= 1) {
		if (a[i-1] == b[j-1]) {
			result += a[i - 1];
			i--;
			j--;
		}
		else if (matrix[i - 1][j] > matrix[i][j - 1]) {
			i--;
		}
		else if (matrix[i - 1][j] < matrix[i][j - 1]) {
			j--;
		}
	}
	reverse(result.begin(), result.end());
	cout << result;
}

void main() {
	ifstream input("input_3.txt");
	string a;
	input >> a;
	string b;
	input >> b;
	int m = a.size(), n = b.size();
	LongestCommonSubSeq(a, m, b, n);
}