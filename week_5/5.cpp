#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

vector<int> key;
vector<float> freq;
vector<float> final;



float sum(int i, int j)
{
	float s = 0;
	for (int k = i; k <= j; k++)
		s += freq[k];
	return s;
}



void show() {
	cout << final[0] << endl;
	for (int i = 0; i < final.size(); i++)
	{
		cout << final[i] << " ";
	}
}

void tree(float** result, int i, int j)
{
	if (j < i)
		return;
	float t = result[i][j];
	final.push_back(t);
	tree(result, i, t - 1);
	tree(result, t + 1, j);
}

void OptimalBTS(vector<int> key, vector<float> freq, int n) {
	float** C = new float*[n];
	float** R = new float* [n];

	for (int i = 0; i < n; i++) {
		C[i] = new float[n] {0};
		R[i] = new float[n] {0};
	}

	for (int i = 0; i < n; i++) {
		C[i][i] = freq[i];
		R[i][i] = i + 1;
	}



	for (int diag = 2; diag <= n; diag++)
	{
		for (int i = 0; i < n - diag + 1; i++)
		{
			int j = i + diag - 1;
			C[i][j] = FLT_MAX;
			for (int t = i; t <= j; t++)
			{
				float min1 = ((t > i) ? C[i][t - 1] : 0);
				float min2 = ((t < j) ? C[t + 1][j] : 0);
				float min3 = sum(i, j);
				float min = min1 + min2 + min3;

				if (min < C[i][j])
				{
					C[i][j] = min;
					R[i][j] = t + 1;
				}
			}
		}
	}

	float** Result = new float* [n + 1];
	for (int i = 0; i <= n; i++) {
		Result[i] = new float[n + 1]{ 0 };
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			Result[i + 1][j + 1] = R[i][j];
		}
	}
	//cout << C[0][n - 1] << endl;

	tree(Result, 1, n);
	show();
}


void main() {
	ifstream input("input_5.txt");
	int n;
	input >> n;
	
	for (int i = 0; i < n; i++) {
		int temp1;
		float temp2;
		input >> temp1 >> temp2;
		key.push_back(temp1);
		freq.push_back(temp2);
	}
	OptimalBTS(key, freq, n);
}