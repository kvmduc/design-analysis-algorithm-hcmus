#include <iostream>
#include <fstream>
#include  <vector>
#include <math.h>
using namespace std;
struct point {
	float x;
	float y;
};

float Distance(point a, point b) {
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void Output(float deltamin, vector<point>Points) {
	for (int i = 0; i < Points.size(); i++) {
		for (int j = i + 1; j < Points.size(); j++) {
			if (Distance(Points[i], Points[j]) == deltamin) {
				cout << "(" << Points[i].x << "," << Points[i].y << ") (" << Points[j].x << "," << Points[j].y << ")" << endl;
			}
		}
	}
}

float Closest_pair(vector<point>Points) {
	if (Points.size() <= 2) {
		return Distance(Points[0], Points[1]);
	}
	else {
		float l = Points[int((Points.size() + 1) / 2)].x;
		vector<point>PointL;
		vector<point>PointR;
		for (int i = 0; i <int((Points.size() + 1) / 2); i++) {
			point temp;
			temp = Points[i];
			PointL.push_back(temp);
		}
		for (int i = int((Points.size() + 1) / 2); i< Points.size(); i++) {
			point temp;
			temp = Points[i];
			PointR.push_back(temp);
		}
		float dL = Closest_pair(PointL);
		float dR = Closest_pair(PointR);
		float delta = min(dL, dR);
		
		vector<point> S;
		for (int i = 0; i < Points.size(); i++) {
			if(abs(Points[i].x - l) <= delta){
				point temp = Points[i];
				S.push_back(temp);
			}
		}
		float deltaMin = delta;
		for (int i = 0; i < S.size(); i++) {
			int j = i + 1;
			while ((j < S.size()) && (abs(S[i].y - S[j].y) <= deltaMin)) {
				deltaMin = min(Distance(S[i],S[j]),deltaMin);
				j++;
			}
		}
		Output(deltaMin, Points);
		return deltaMin;
	}
}

void main() {
	ifstream input("input_4.txt");
	int n;
	input >> n;
	vector <point> Points;
	for (int i = 0; i < n; i++) {
		point temp;
		input >> temp.x >> temp.y;
		Points.push_back(temp);
	}
	Closest_pair(Points);
}