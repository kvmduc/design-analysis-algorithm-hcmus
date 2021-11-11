#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
# define pi           3.14159265358979323846  /* pi */

using namespace std;

struct point {
	float x;
	float y;
};

struct tuple1 {
	point p;
	float angle;
};

float compute_angle(point from, point to) {
	float angle = atan2(to.y - from.y, to.x - from.x);
	if (angle < 0) {
		angle += 2 * pi;
	}
	return angle;
}

tuple1 FindNextPoint(vector<point> a, point cur, float curAngle) {
	float minAngle = 2 * pi;
	point next;
	tuple1 result;
	for (int i = 0; i < a.size(); i++) {
		if (a[i].x == cur.x && a[i].y == cur.y) {
			a.erase(a.begin()+i);
		}
	}
	for (point p : a) {
		float angle = compute_angle(cur, p);
		if (angle < minAngle && angle >= curAngle) {
			next = p;
			minAngle = angle;

		}
	}
	result.p = next;
	result.angle = minAngle;
	a.push_back(cur);
	return result;
}

bool checkexist(vector<point> result, point p) {
	for (point each : result) {
		if (p.x == each.x && p.y == each.y) {
			return true;
		}
	}
	return false;
}

point init(vector<point> a){
	float minY = a[0].y;
	float minX = a[0].x;
	point result = a[0];
	for (point p : a) {
		if (p.y < minY) {
			minY = p.y;
			result = p;
		}
	}
	for (point p : a) {
		if (p.y == minY && p.x < minX) {
			minX = p.x;
			result = p;
		}
	}

	return result;
}

void convex_hull(vector<point> a, int n) {
	vector<point> result;
	point init_point = init(a);
	result.push_back(init_point);
	float curAngle = 0;
	point cur = init_point;
	while (true) {
		tuple1 temp = FindNextPoint(a, cur, curAngle);
		if (checkexist(result,temp.p)) {
			break;
		}
		result.push_back(temp.p);
		cur = temp.p;
		curAngle = temp.angle;
	}
	for (int i = 0; i < result.size(); i++) {
		cout << "(" << result[i].x << "," << result[i].y << ") ";
	}
}

void main() {
	ifstream input("input_4.txt");
	int n;
	input >> n;
	vector <point> a;
	for (int i = 0; i < n; i++) {
		point temp;
		input >> temp.x >> temp.y;
		a.push_back(temp);
	}
	convex_hull(a, n);
}