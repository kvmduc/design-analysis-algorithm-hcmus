#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

int InterpolationSearch(vector<double>  arr, double key, int l, int r) {
	int x = l + floor((key - arr[l]) * (r - l) / (arr[r] - arr[l]));
	if (l <= r && key >= arr[l] && key <= arr[r]) {
		if (arr[x] == key) {
			return x;
		}
		if (arr[x] > key) {
			return InterpolationSearch(arr, key, l, x - 1);
		}
		if (arr[x] < key) {
			return InterpolationSearch(arr, key, x + 1, r);
		}
	}
	return -1;
}



void main() {
	ifstream input("input_4.txt");
	int n;
	input >> n;
	vector<double>  arr;
	for (int i = 0; i < n; i++) {
		double temp;
		input >> temp;
		arr.push_back(temp);
	}
	double key;
	input >> key;
	cout << InterpolationSearch(arr, key, 0, n-1);
}