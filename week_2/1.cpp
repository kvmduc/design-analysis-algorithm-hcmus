#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int* col;
int sum = 0;
string result = "";

bool promising(int i) {
	int j = 0;
	bool flag = true;
	while (j < i && flag) {
		if (col[i] == col[j] || abs(col[i] - col[j]) == i - j) {
			flag = false;
		}
		j++;
	}
	return flag;
}

void output(int n) {
	for (int i = 0; i < n; i++) {
		//cout << "(" << col[i] << "," << i << ")";
		result +=  "(" + to_string(col[i]) + "," + to_string(i) + ")";
		if (i == n - 1) {
			continue;
		}
		//cout << ",";
		result += ",";
	}
	result += "\n";
}

void n_Queen(int i, int n) {
	for (int j = 0; j < n; j++) {
		col[i] = j;
		if (promising(i)) {
			if (i == n - 1) {
				sum++;
				output(n);
			}
			else {
				n_Queen(i + 1, n);
				col[i] = -1;
			}
		}
	}

}

void main() {
	ifstream input("input_1.txt");
	int n;
	input >> n;
	col = new int[n] {-1};
	n_Queen(0, n);
	cout << sum << endl;
	cout << result;
}