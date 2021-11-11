#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

void Knapsack(int weight, int* w, int* v, int n) {
	int** result = new int * [n + 1];
	for (int i = 0; i <= n; i++) {
		result[i] = new int[weight + 1];
	}
	for (int i = 0; i <= n; i++) {
		result[i][0] = 0;
	}
	for (int j = 0; j <= weight; j++) {
		result[0][j] = 0;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= weight; j++) {
			if (j >= w[i - 1]) {
				result[i][j] = max(result[i - 1][j], result[i - 1][j - w[i - 1]] + v[i - 1]);
			}
			else {
				result[i][j] = result[i-1][j];
			}
		}
	}
	int k = result[n][weight];
	int i = n, j = weight;
	string index = "";
	while (k > 0) {
		if (k == result[i - 1][j]) {
			i--;
			continue;
		}
		else {
			index += " " + to_string(i - 1);
			k -= v[i - 1];
			j -= w[i - 1];
			i--;
		}
	}
	reverse(index.begin(), index.end());
	cout << index << endl;
	cout << result[n][weight];
}


void main() {
	ifstream input("input_7.txt");
	int weight;
	input >> weight;
	int n;
	input >> n;
	int* v = new int[n];
	int* w = new int[n];
	for (int i = 0; i < n; i++) {
		input >> w[i] >> v[i];
	}
	Knapsack(weight, w, v, n);
}
