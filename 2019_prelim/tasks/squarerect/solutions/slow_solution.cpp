#include "squarerect.h"
#include <bits/stdc++.h>
using namespace std;

int N;

bool my_inside_shape(int X, int Y) {
	if (X <= 0 || X > N || Y <= 0 || Y > N) return false;
	else return inside_shape(X, Y);
}

bool am_i_square(int _N, int Q) {
	N = _N;
	bool stratified[5][5];
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			stratified[i][j] = inside_shape((i+1)*20, (j+1)*20);
		}
	}
	bool found = 0;
	for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) found = max(found, stratified[i][j]);
	if (!found) {
		return false;
	} else {
		int minx = 100, miny = 100, maxx = 0, maxy = 0;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (stratified[i][j]) {
					minx = min(minx, i);
					miny = min(miny, j);
					maxx = max(maxx, i);
					maxy = max(maxy, j);
				}
			}
		}
		int bot = minx*20, top = (minx+1)*20, mid;
		while (bot + 1 < top) {
			mid = (bot + top) / 2;
			if (my_inside_shape(mid, (miny+1)*20)) top = mid;
			else bot = mid;
		}
		int top_edge = bot + 1;
		bot = (maxx+1)*20;
		top = (maxx+2)*20+1;
		while (bot + 1 < top) {
			mid = (bot + top) / 2;
			if (my_inside_shape(mid, (miny+1)*20)) bot = mid;
			else top = mid;
		}
		int bottom_edge = bot;
		bot = miny*20;
		top = (miny+1)*20;
		while (bot + 1 < top) {
			mid = (bot + top) / 2;
			if (my_inside_shape((minx+1)*20, mid)) top = mid;
			else bot = mid;
		}
		int left_edge = bot + 1;
		int sze = bottom_edge - top_edge;
		int right_bound = left_edge + sze;
		if (my_inside_shape((minx+1)*20, right_bound) && !my_inside_shape((minx+1)*20, right_bound + 1)) return true;
		else return false;
	}
}

