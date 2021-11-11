#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int change_making(vector<int> coin, int k, int n, int * result) {
	if (k == 0) {
		return 0;
	}
	int res = INT_MAX;
	for (int i = 0; i < n; i++) {
		if (coin[i] <= k) {
			int sub_res = change_making(coin, k - coin[i], n, result);
			if (sub_res != INT_MAX && sub_res + 1 < res) {
				res = sub_res + 1;
			}
		}
	}
	return res;
}

void main() {
	ifstream input("input_3.txt");
	vector<int> a;
	while (true) {
		int temp;
		input >> temp;
		a.push_back(temp);
		if (temp == 1)
			break;
	}
	int k;
	input >> k;
	int* result = new int[a.size()]{ 0 };
	int total = change_making(a, k, a.size(), result);
	cout << total;
}

