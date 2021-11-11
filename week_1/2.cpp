#include <iostream>
#include <fstream>
using namespace std;

void subsequence(float* a, int n) {
	float max = a[0];
	for (int i = 0; i < n; i++) {
		max = a[i] > max ? a[i] : max;
	}
	if (max <= 0) {
		cout << max << "\n" << max;
		return;
	}
	float max_sum = 0 , temp_sum = 0;
	int left = 0, right = 0;

	for (int i = 0; i < n; i++) {
		temp_sum += a[i];
		if (temp_sum > max_sum) {
			right = i;
			max_sum = temp_sum;
		}
		if (temp_sum < 0) {
			temp_sum = 0;
			left = i+1;
		}
	}
	for (int i = left; i <= right; i++) {
		cout << a[i] << " ";
	}

	cout << "\n" << max_sum;
}

void main() {
	ifstream input("input_2.txt");
	int n;
	input >> n;
	float* a = new float[n];
	for (int i = 0; i < n; i++) {
		input >> a[i];
	}
	subsequence(a, n);
}