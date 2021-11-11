#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

void swap(double* a, double* b)
{
	double t = *a;
	*a = *b;
	*b = t;
}

int Partition(vector<double> & arr, int lower, int upper, int pos) {
	if (upper == lower) {
		return lower;
	}
	double pivot = arr[pos];

	swap(&arr[lower], &arr[pos]);

	pos = lower;

	for (int i = lower+1; i <= upper; i++) {
		if (pivot > arr[i]) {
			pos++;
			swap(&arr[i], &arr[pos]);
		}
	}
	swap(&arr[lower], &arr[pos]);

	return pos;
}


float Selection(vector<double> & arr, int lower, int upper, int k) {
	srand(time(NULL));
	int h = rand() % (upper - lower + 1) + lower;

	int pos = Partition(arr, lower, upper, h);
	double result;
	if (pos == k) {
		return arr[pos];
	}
	if (pos > k) {
		result = Selection(arr, lower, pos-1, k);
	}
	if (pos < k) {
		result = Selection(arr, pos+1, upper, k);
	}
	return result;
}

void main() {
	ifstream input("input_3.txt");
	int n;
	input >> n;
	vector<double>  arr;
	for (int i = 0; i < n; i++) {
		double temp;
		input >> temp;
		arr.push_back(temp);
	}
	int index;
	input >> index;
	cout << Selection(arr, 0, n - 1, index - 1);
}