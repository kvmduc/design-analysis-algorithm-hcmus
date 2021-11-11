#include <iostream>
#include <fstream>
using namespace std;

struct index {
	int head;
	int tail;
};

index Index = {0,0};

int sumMax(int* a, int l, int r) {
	if (l == r) {
		return max(a[l], 0);
	}
	int c = (l + r) / 2;

	int maxLS = sumMax(a, l, c);
	int maxRS = sumMax(a, c+1, r);

	int temp = 0, maxLpartS = 0;
	for (int i = c; i >= l; i--) {
		temp += a[i];
		if (temp > maxLpartS) {
			Index.head = i;
			maxLpartS = temp;
		}
	}
	int maxRpartS = 0;
	temp = 0;
	for (int i = c+1; i <= r; i++) {
		temp += a[i];
		if (temp > maxRpartS) {
			Index.tail = i;
			maxRpartS = temp;
		}
	}
	temp = maxLpartS + maxRpartS;
	int result = max(temp, max(maxLpartS, maxRpartS));
	return result;
}



void main() {
	ifstream input("input_3.txt");
	int n;
	input >> n;
	int* a = new int[n];
	for (int i = 0; i < n; i++) {
		input >> a[i];
	}
	int sum = sumMax(a, 0, n - 1);
	for (int i = Index.head; i <= Index.tail; i++) {
		cout << a[i] << " ";
	}
	cout << endl << Index.head << " " << Index.tail << endl;
	cout << sum;
	
}