#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> input;
int t;

void output(int* s, int n) {
	for (int i = 0; i < n; i++) {
		if (s[i] == 0) {
			continue;
		}
		cout << s[i] << " ";
	}
}

void Subset_sum(int* s, int n, int size, int sum, int start, int total) {
	if (sum == t) {
		output(s,n);
	}
	else {
		int lost = 0;
		for (int i = start; i < n; i++) {
			if ((sum + total - lost >= t) && (sum + input[i] <= t)) {
				s[size] = input[i];
				Subset_sum(s, n, size + 1, sum + input[i], i + 1, total - lost - input[i]);
			}
			lost += input[i];
		}
	}
	
}

void main() {
	ifstream fin("input_3.txt");
	int n;
	int total = 0;
	fin >> n;
	for (int i = 0; i < n; i++) {
		int temp;
		fin >> temp;
		input.push_back(temp);
		total += temp;
	}
	fin >> t;
	int* s = new int[n] {0};
	sort(input.begin(), input.end());
	if (input[0] <= t <= total) {
		Subset_sum(s, n, 0, 0, 0, total);
	}
}