#include <iostream>
#include <fstream>
using namespace std;

void shakersort(float* a, int n) {
	bool swapped;
	do {
		swapped = false;
		for (int i = 0; i <= n - 2; i++) {
			if (a[i] > a[i + 1]) {
				swap(a[i], a[i + 1]);
				swapped = true;
			}
		}
		if (!swapped) {
			break;
		}
		else {
			swapped = false;
			for (int i = n - 2; i >= 0; i--) {
				if (a[i] > a[i + 1]) {
					swap(a[i], a[i + 1]);
					swapped = true;
				}
			}
		}

	} while (swapped);
	
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
}

void main() {
	ifstream input("input_1.txt");
	int n;
	input >> n;
	float* a = new float[n];
	for (int i = 0; i < n; i++) {
		input >> a[i];
	}
	shakersort(a, n);
}