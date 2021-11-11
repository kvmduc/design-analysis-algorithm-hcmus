#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

void display(vector<int>p) {
	for (int i = 0; i < p.size(); i++){
		cout << p[i] << " ";
	}
	cout << endl;
}

void Traceback(vector <int> a, int i, int sum, int ** matrix, vector<int>p) {
	if (i == 0 && sum != 0 && matrix[1][sum])
	{
		p.push_back(a[i-1]);
		display(p);
		return;
	}
	if (i == 0 && sum == 0)
	{
		display(p);
		return;
	}
	if (matrix[i-1][sum])
	{
		vector<int> b = p;
		Traceback(a, i - 1, sum, matrix, b);
	}
 
	if (sum >= a[i-1] && matrix[i-1][sum - a[i-1]])
	{
		p.push_back(a[i-1]);
		Traceback(a, i - 1, sum - a[i-1], matrix, p);
	}
}

void SubsetSum(vector<int> a, int n, int k) {
	int** matrix = new int* [n + 1];
	for (int i = 0; i <= n; i++) {
		matrix[i] = new int[k + 1];
	}
	for (int j = 0; j <= k; j++) {
		matrix[0][j] = 0;
	}
	for (int i = 0; i <= n; i++) {
		matrix[i][0] = 1;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= k; j++) {
			int temp = 0;
			if (j >= a[i - 1]) {
				temp = matrix[i - 1][j - a[i - 1]];
			}
			matrix[i][j] = matrix[i - 1][j] || temp;
		}
	}
	vector<int> p;
	Traceback(a, n, k, matrix, p);
}


void main() {
	ifstream input("input_6.txt");
	vector<int> a;
	int n;
	input >> n;
	for (int i = 0; i < n; i++) {
		int temp;
		input >> temp;
		a.push_back(temp);
	}
	int k;
	input >> k;
	SubsetSum(a, n, k);
}