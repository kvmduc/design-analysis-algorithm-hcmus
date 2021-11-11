#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
int** cb;
int n;
int row[] = { 1, -1, -2, -2, -1, 1, 2, 2 };
int col[] = { 2, 2, 1, -1, -2, -2, -1, 1 };
int sum = 0;

struct coordinate{
	int x; 
	int y;
};

vector <coordinate> location;
string result = "";

void output() {
	/*for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << cb[i][j] << " , ";
		}
		cout << endl;
	}
	cout << endl;*/
	for (int i = 0; i < n * n; i++) {
		result+= "(" + to_string(location[i].x) + "," + to_string(location[i].y) + ")";
		if (i != n * n - 1) {
			result += " , ";
		}
	}
	result += "\n";
}


void KnightTour(int i, int r, int c) {
	for (int k = 0; k < 8; k++) {
		int u = r + row[k];
		int v = c + col[k];
		if ((u >= 0 && u < n && v >= 0 && v < n) && (cb[u][v] == 0)) {
			cb[u][v] = i;
			coordinate temp;
			temp.x = u;
			temp.y = v;
			location.push_back(temp);
			if (i == pow(n,2)) {
				sum++;
				output();
			}
			else {
				KnightTour(i + 1, u, v);
			}
			cb[u][v] = 0;
			location.pop_back();
		}
	}
}


void main() {
	int init_x = 0, init_y = 0;
	ifstream input("input_2.txt");
	input >> n;
	cb = new int* [n];
	for (int i = 0; i < n; i++) {
		cb[i] = new int [n] {0};
	}
	coordinate temp = { init_x, init_y};
	location.push_back(temp);
	cb[init_x][init_y] = 1;
	KnightTour(2, init_x, init_y);
	cout << sum << endl;
	cout << result;
}