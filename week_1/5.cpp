#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


void TravelingSaleman(float ** a , int n, int s) {
	int* city = new int[n];
	int* result = new int[n];
	for (int i = 0; i < n; i++) {
		city[i] = i;
	}
	int min_path = 999;
	do {
		int current_path_dis = 0;
		int k = 0;
		for (int i = 0; i < n; i++) {
			current_path_dis += a[k][city[i]];
			k = city[i];
		}
		current_path_dis += a[k][s];

		if (current_path_dis < min_path) {
			min_path = current_path_dis;
			for (int i = 0; i < n; i++) {
				result[i] = city[i];
			}
		}
	} while (next_permutation(city , city + n));
	for (int i = 0; i < n; i++) {
		cout << result[i] + 1 << " ";
	}
	cout << min_path;
}

void main() {
	ifstream input("input_5.txt");
	int n;
	input >> n;
	float** a = new float *[n];
	for (int i = 0; i < n; i++) {
		a[i] = new float[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			a[i][j] = 999;
		}
	}
	while (true) {
		int check;
		input >> check;
		if (check == -1) {
			break;
		}
		int x = check, y;
		input >> y;
		input >> a[x-1][y-1];
		a[y - 1][x - 1] = a[x - 1][y - 1];
	}
	for (int i = 0; i < n; i++) {
		a[i][i] = 0;
	}
	int start = 0;
	TravelingSaleman(a, n, start);
}