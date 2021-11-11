#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

void Traceback(int* result, int n, vector <int> a) {
	int index;
	int max = 1;
	for (int i = 0; i < n; i++) {
		if (result[i] > max) {
			max = result[i];
			index = i;
		}
	}
	int max_temp = max;
	int* trace = new int[max];
	trace[max - 1] = a[index];
	int j = max - 1;
	while (max >= 1) {
		for (int i = index - 1; i >= 0; i--) {
			if ((result[i] == max - 1) && (a[i] < a[index])) {
				trace[--j] = a[i];
				index = i;
			}
		}
		max--;
	}
	for (int i = 0; i < max_temp; i++) {
		cout << trace[i] << " ";
	}
	cout << endl << max_temp;

}

void LongestMonoIncreaseSubseq(vector<int> a, int n) {
	int* result = new int[n];
	for (int i = 0; i < n; i++) {
		result[i] = 1;
	}

	for (int i = 1; i < n; i++) {
		int max = result[i];
		for (int j = 0; j <= i; j++) {
			if ((result[j] >= max) && (a[j] < a[i]) ) {
				max = result[j] + 1;
			}
		}
		result[i] = max;
	}
	
	Traceback(result, n, a);
}

void main() {
	ifstream input("input_4.txt");
	vector<int> a;
	int n;
	input >> n;
	for (int i = 0; i < n; i++) {
		int temp;
		input >> temp;
		a.push_back(temp);
	}
	LongestMonoIncreaseSubseq(a, n);
}