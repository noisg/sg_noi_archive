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
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			stratified[i][j] = inside_shape((i+1)*20, (j+1)*20);
		}
	}
	bool found = 0;
	for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) found = max(found, stratified[i][j]);
	if (!found) {
		for (int i = 0; i < 5; i++) stratified[i][4] = my_inside_shape((i+1)*20, 100);
		for (int i = 0; i < 4; i++) stratified[4][i] = my_inside_shape(100, (i+1)*20);
		for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) found = max(found, stratified[i][j]);
		if (!found) return false;
		vector< pair<int, int> > founds;
		for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) if (stratified[i][j]) founds.push_back(make_pair(i, j));
		if (founds.size() > 1) return false;
		int x = founds[0].first, y = founds[0].second;
		if (x == 4) {
			/* bottom edge */
			int bot = y*20, top = (y+1)*20, mid;
			while (bot + 1 < top) {
				mid = (bot + top) / 2;
				if (my_inside_shape(100, mid)) top = mid;
				else bot = mid;
			}
			int left_edge = bot + 1;
			if (my_inside_shape(100, left_edge + 19) && !my_inside_shape(100, left_edge + 20)) return true;
			else return false;
		} else {
			/* top edge */
			int bot = x*20, top = (x+1)*20, mid;
			while (bot + 1 < top) {
				mid = (bot + top)/2;
				if (my_inside_shape(mid, 100)) top = mid;
				else bot = mid;
			}
			int top_edge = bot + 1;
			if (my_inside_shape(top_edge + 19, 100) && !my_inside_shape(top_edge + 20, 100)) return true;
			else return false;
		}
	} else {
		int minx = 100, miny = 100, maxx = 0, maxy = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
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
