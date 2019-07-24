#pragma once
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include "Stack.h"
#include "cell.h"
#include "Baedeker.h"
class MapService {
public:
	MapService(int MAX, int MAX_TOP_X, int MAX_BOTTOM_X);
	~MapService();
	vector<cell*> createMap();
private:
	int MAX;
	int MAX_TOP_X;
	int MAX_BOTTOM_X;
	void clear_X_matrix(int start_position, vector<cell*> cells, int max_iter);
	void clear_Y_matrix(int start_position, vector<cell*> cells, int max_iter);

};

MapService::MapService(int MAX, int MAX_TOP_X, int MAX_BOTTOM_X) {
	this->MAX = MAX;
	this->MAX_TOP_X = MAX_TOP_X;
	this->MAX_BOTTOM_X = MAX_BOTTOM_X;
}

MapService::~MapService() {}

inline void MapService::clear_X_matrix(int start_position, vector<cell*> cells, int max_iter) {
	for (int i = start_position; i <= max_iter; i += MAX) {
		if (start_position == 1) {
			cells.at(i - 1)->clear_X_matrix_LEFT(i, max_iter);
		} else {
			cells.at(i - 1)->clear_X_matrix_RIGHT(i, max_iter, MAX);
		}
	}
}

inline void MapService::clear_Y_matrix(int start_position, vector<cell*> cells, int max_iter) {
	for (int i = start_position; i <= max_iter; i++) {
		if (i > MAX_TOP_X) {
			if (i > MAX_TOP_X && i >= MAX_BOTTOM_X) {
				cells.at(i - 1)->clear_Y_matrix_BOTTOM(i, max_iter, MAX_BOTTOM_X);
			} else { continue; }
		} else {
			cells.at(i - 1)->clear_Y_matrix_TOP(i, max_iter);
		}
	}
}

inline vector<cell*> MapService::createMap() {
	vector<cell*> cells;
	cell* c_cell = new cell();
	for (int i = 0; i < MAX*MAX; i++) {
		cell* c = new cell(i - 1);
		cells.push_back(c);
	}
	clear_Y_matrix(1, cells, MAX_TOP_X);
	clear_Y_matrix(MAX_BOTTOM_X, cells, MAX*MAX);

	clear_X_matrix(1, cells, MAX_BOTTOM_X);
	clear_X_matrix(MAX, cells, MAX*MAX);
	for (int i = 0; i < MAX*MAX; i++) {
		cells.at(i)->cell_to_array();
	}
	c_cell->unit(cells, MAX);
	return cells;
}

