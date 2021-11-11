#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int change_making(vector <int> a, int money) {
	int n = a.size();
	int* c = new int[money+1] {0};
	c[1] = 1;
	int* used_coin = new int[money + 1]{ 0 };
	used_coin[1] = 1;
	for (int i = 2; i <= money; i++) {
		int min = i;
		used_coin[i] = 1;
		for (int k = n-1; k >= 0; k--) {
			if (i - a[k] < 0) {
				continue;
			}
			if (c[i - a[k]] + 1 <= min) {
				min = c[i - a[k]] + 1;
				used_coin[i] = a[k];
			}
		}
		c[i] = min;
	}
	int money_temp = money;
	int* result = new int[n]{ 0 };
	while (money_temp > 0) {
		//cout << used_coin[money_temp] << endl;
		//money_temp = money_temp - used_coin[money_temp];
		for (int k = 0; k < n; k++) {
			if (used_coin[money_temp] == a[k]) {
				result[k] += 1;
			}
		}
		money_temp = money_temp - used_coin[money_temp];
	}
	for (int k = 0; k < n; k++) {
		cout << a[k] << " : " << result[k] << endl;
	}
	return c[money];
}

void main() {
	ifstream input("input_2.txt");
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
	change_making(a, k);
}