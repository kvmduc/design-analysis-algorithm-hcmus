#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

void Knapsack(int weight_total, float * w_arr, float * v_arr, int n) {
	int* A = new int[n];
	int* best_choice = new int[n] {0};
	int best_value = 0, best_weight = weight_total;
	for (int i = 0; i <= pow(2,n)-1; i++) {
		int j = n-1;
		int temp_weight = 0;
		int temp_value = 0;
		while (A[j] != 0 && j >= 0) {
			A[j] = 0;
			j = j - 1;
		}
		A[j] = 1;
		for (int k = 0; k < n; k++) {
			if (A[k] == 1) {
				temp_weight += w_arr[k];
				temp_value += v_arr[k];
			}
		}
		if ((temp_value > best_value) && (temp_weight <= weight_total)) {
			best_value = temp_value;
			best_weight = temp_weight;
			for (int i = 0; i < n; i++) {
				best_choice[i] = A[i];
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (best_choice[i] == 1) {
			cout << i + 1 << " ";
		}
	}
	cout << "\n" << best_value;
}

void main() {
	ifstream input("input_6.txt");
	int weight;
	input >> weight;
	int n;
	input >> n;
	float* v = new float[n];
	float* w = new float[n];
	for (int i = 0; i < n; i++) {
		input >> w[i] >> v[i];
	}
	Knapsack(weight, w, v, n);
}