#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;


void TopologicalSort(vector<vector<int>> matrix) {
	int* indegree = new int[matrix.size()]{ 0 };
	queue<int> Queue;
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix.size(); j++) {
			indegree[j] += matrix[i][j];
		}
	}

	for (int i = 0; i < matrix.size(); i++) {
		if (indegree[i] == 0) {
			Queue.push(i);
		}
	}
	while (!Queue.empty()) {
		int temp = Queue.front();
		Queue.pop();
		cout << temp + 1 << " ";
		for (int i = 0; i < matrix.size(); i++) {
			if (matrix[temp][i] == 1) {
				indegree[i] --;
				if (indegree[i] == 0) {
					Queue.push(i);
				}
			}
		}
	}
}


vector<string> DelimSplit(const string& str, const string& delim)
{
	vector<string> tokens;
	size_t prev = 0, pos = 0;
	do
	{
		pos = str.find(delim, prev);
		if (pos == string::npos) pos = str.length();
		string token = str.substr(prev, pos - prev);
		tokens.push_back(token);
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}


void main() {
	ifstream input("input_1.txt");
	int n;
	input >> n;
	vector<vector<int>> matrix(n, vector<int>(n, 0));
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			matrix[i][j] = 0;
		}
	}
	string a;
	getline(input, a);
	while (true) {
		string temp;
		getline(input, temp);
		if (temp == "") {
			break;
		}
		vector <string> line = DelimSplit(temp, " ");
		if (stoi(line[0]) == 0)
			break;
		for (int i = 1; i < line.size(); i++) {
			matrix[stoi(line[i]) - 1][stoi(line[0])-1] = 1;
		}
	}
	//for (int i = 0; i < 5; i++) {
	//	for (int j = 0; j < 5; j++) {
	//		cout << matrix[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	TopologicalSort(matrix);
}