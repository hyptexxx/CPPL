#pragma once
#include <conio.h>
#include <iostream>
#include <vector>
#include "Stack.h"
#include "cell.h"
#include "MapService.h"
#define SHIFT_TO_THE_LEFT POSITION - 1
#define SHIFT_TO_THE_RIGHT  POSITION + 1
#define SHIFT_TO_THE_TOP  POSITION - capacity
#define SHIFT_TO_THE_BOTTOM  POSITION + capacity

class Baedeker {
public:
	Baedeker(vector<cell*> cells, int capacity, int MAX_TOP_X, int MAX_BOTTOM_X);
	~Baedeker();
	vector<int> start_search_the_way(int capacity, int _start_position, int _exit_position);

private:
	vector<cell*> cells;
	int capacity;
	bool can_go = true;
	int MAX_TOP_X;
	int MAX_BOTTOM_X;
	cell* goto_TOP(int _current_pos);
	cell* goto_BOTTOM(int _current_pos);
	cell* goto_LEFT(int _current_pos);
	cell* goto_RIGHT(int _current_pos);
	bool isDeadlock(cell* cell);
	bool contains(int number, vector<int> vector);
	void print();
	void clear();
	void set_dead_end(int POSITION);
	vector<int> temp_way;
	void calc_way(int POSITION);
};

Baedeker::Baedeker(vector<cell*> cells, int capacity, int MAX_TOP_X, int MAX_BOTTOM_X) {
	this->cells = cells;
	this->capacity = capacity;
	this->MAX_TOP_X = MAX_TOP_X;
	this->MAX_BOTTOM_X = MAX_BOTTOM_X;
	//Stack<cell*> way(capacity * capacity * 4);
}
Baedeker::~Baedeker() {}
inline cell* Baedeker::goto_TOP(int POSITION) { return this->cells.at(SHIFT_TO_THE_TOP); }
inline cell* Baedeker::goto_BOTTOM(int POSITION) { return this->cells.at(SHIFT_TO_THE_BOTTOM); }
inline cell* Baedeker::goto_LEFT(int POSITION) { return this->cells.at(SHIFT_TO_THE_LEFT); }
inline cell* Baedeker::goto_RIGHT(int POSITION) { return this->cells.at(SHIFT_TO_THE_RIGHT); }
inline bool Baedeker::isDeadlock(cell * cell) {
	if (cell->getTop() == false && cell->getBottom() == false && cell->getLeft() == false && cell->getRight() == false) { return true; } else { return false; }
}

inline bool Baedeker::contains(int number, vector<int> vector) {
	bool result = false;
	for (int iterator = 1; iterator < vector.size(); iterator++) {
		if (vector.at(iterator) == number) { result = true; }
	} return result;
}

inline void Baedeker::print() {
	cell* c_cell = new cell();
	system("cls");
	for (int i = 0; i < this->capacity * this->capacity; i++) { cells.at(i)->cell_to_array(); }
	c_cell->unit(this->cells, this->capacity);
	delete c_cell;
}

inline void Baedeker::calc_way(int POSITION) {
	if (POSITION == 0) { can_go = false; } 
	else {
		this->print();
		// bottom
		if (can_go) {
			if ((this->cells.at((this->capacity * this->capacity) - 1)->getLeft() == false || goto_LEFT((this->capacity * this->capacity) - 1)->getRight() == false) && (this->cells.at((this->capacity * this->capacity) - 1)->getTop() == false || goto_TOP((this->capacity * this->capacity) - 1)->getBottom() == false)) {
				can_go = false;
			}
			if (this->cells.at(POSITION)->getBottom() == true && goto_BOTTOM(POSITION)->getTop() == true) {
				if (can_go != false) {
					if (SHIFT_TO_THE_BOTTOM != temp_way.back()) {
						if (this->contains(SHIFT_TO_THE_BOTTOM, temp_way)) {
							cells.at(POSITION)->setBottom(false);
							this->clear();
						} else {
							temp_way.push_back(POSITION);
							this->cells.at(POSITION)->setCenter(true);
							calc_way(SHIFT_TO_THE_BOTTOM);
						}
					}
				} else { POSITION = 0; }
			}
			// left
			if (this->cells.at(POSITION)->getLeft() == true && goto_LEFT(POSITION)->getRight() == true) {
				if (can_go != false) {
					if (SHIFT_TO_THE_LEFT != temp_way.back()) {
						if (this->contains(SHIFT_TO_THE_LEFT, temp_way)) {
							cells.at(POSITION)->setLeft(false);
							this->clear();
						} else {
							this->cells.at(POSITION)->setCenter(true);
							temp_way.push_back(POSITION);
							calc_way(SHIFT_TO_THE_LEFT);
						}
					}
				} else { POSITION = 0; }
			}
			// top
			if (this->cells.at(POSITION)->getTop() == true && goto_TOP(POSITION)->getBottom() == true) {
				if (can_go != false) {
					if (SHIFT_TO_THE_TOP != temp_way.back()) {
						if (this->contains(SHIFT_TO_THE_TOP, temp_way)) {
							cells.at(POSITION)->setTop(false);
							this->clear();
						} else {
							this->cells.at(POSITION)->setCenter(true);
							temp_way.push_back(POSITION);
							calc_way(SHIFT_TO_THE_TOP);
						}
					}
				} else { POSITION = 0; }
			}
			// right
			if (this->cells.at(POSITION)->getRight() == true && goto_RIGHT(POSITION)->getLeft() == true) {
				if (can_go != false) {
					if (SHIFT_TO_THE_RIGHT != temp_way.back()) {
						if (this->contains(SHIFT_TO_THE_RIGHT, temp_way)) {
							cells.at(POSITION)->setRight(false);
							this->clear();
						} else {
							this->cells.at(POSITION)->setCenter(true);
							temp_way.push_back(POSITION);
							calc_way(SHIFT_TO_THE_RIGHT);
						}

					}
				} else { POSITION = 0; }
			}
			if (POSITION != 0 && can_go) { set_dead_end(POSITION); } 
			else { can_go = false; }
		}
	}
}

inline void Baedeker::set_dead_end(int POSITION) {
	this->cells.at(POSITION)->setBottom(false);
	this->cells.at(POSITION)->setTop(false);
	this->cells.at(POSITION)->setRight(false);
	this->cells.at(POSITION)->setLeft(false);
	this->temp_way.clear();
	this->temp_way.push_back(0);
	for (int i = 0; i < this->cells.capacity(); i++) {
		cells.at(i)->setCenter(false);
	}
	calc_way((this->capacity*this->capacity) - 1);
}
inline void Baedeker::clear() {
	this->temp_way.clear();
	this->temp_way.push_back(0);
	for (int i = 0; i < this->cells.capacity(); i++) {
		cells.at(i)->setCenter(false);
	}
	calc_way((this->capacity*this->capacity) - 1);
}
inline vector<int> Baedeker::start_search_the_way(int capacity, int _start_position, int _exit_position) {
	int POSITION = _start_position - 1;
	temp_way.push_back(0);
	this->cells.at(POSITION)->setBottom(false);
	calc_way(POSITION);
	return temp_way;
}