#include <iostream>
#include <vector>
#include <fstream>
#include <map>
using namespace std;

map<int, int> trace;

int change_making(vector<int> a, int money) {
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == money) {
			return 1;
		}
	}
	int mincoin = money;
	for (int i = 0; i < a.size(); i++) {
		if (money > a[i]) {
			/*if (trace.find(money - a[i]) == trace.end())
				trace[money - a[i]] = change_making(a, money - a[i]);
			int tempsum = 1 + trace[money - a[i]];*/
			int tempsum = 1 + change_making(a, money - a[i]);
			if (tempsum < mincoin) {
				mincoin = tempsum;
			}
		}
	}
	return mincoin;
}



void main() {
	ifstream input("input_5.txt");
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
	cout << change_making(a, k) << endl;
}