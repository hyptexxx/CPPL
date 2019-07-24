#pragma once
#include <cstdlib>
#include <vector>
#include <string>
#include <random> 
#include <Windows.h>
using namespace std;
enum test {
	Black,
	Blue,
	Green,
	Cyan,
	Red,
	Magenta,
	Brown,
	LightGray,
	DarkGray,
	LightBlue,
	LightGreen,
	LightCyan,
	LightRed,
	LightMagenta,
	Yellow,
	White
};
class cell {
private:
	bool top;
	bool bottom;
	bool left;
	bool right;
	bool center;
	char** matrix;
	void calc_opened_wall();
	void init_matrix();

public:
	cell() {
		this->top = false;
		this->bottom = false;
		this->left = false;
		this->right = false;
		this->center = false;
		calc_opened_wall();
		init_matrix();
		cell_to_array();
	}
	cell(int pos) {
		this->top = false;
		this->bottom = false;
		this->left = false;
		this->right = false;
		this->center = false;
		calc_opened_wall();
		init_matrix();
		cell_to_array();
		this->pos = pos;
	}
	int pos;
	bool _come_from_top = false;
	bool _come_from_botom = false;
	bool _come_from_left = false;
	bool _come_from_right = false;
	bool is_NODE = false;
	bool is_dead_end = false;
	void cell_to_array();
	void print();
	void unit(vector<cell*> cells, int capacity);

	void clear_Y_matrix_TOP(int current_iterator, int max_iter);
	void clear_Y_matrix_BOTTOM(int current_iterator, int max_iter, int start_position);

	void clear_X_matrix_LEFT(int current_iterator, int max_iter);
	void clear_X_matrix_RIGHT(int current_iterator, int max_iter, int start_position);

	void setTop(bool top) { this->top = top; }
	void setBottom(bool bottom) { this->bottom = bottom; }
	void setLeft(bool left) { this->left = left; }
	void setRight(bool right) { this->right = right; }
	void setCenter(bool center) { this->center = center; }

	void print_rows_of_united_matrix(char** result, int capacity);

	bool getTop() { return this->top; }
	bool getBottom() { return this->bottom; }
	bool getLeft() { return this->left; }
	bool getRight() { return this->right; }
	char** getMatrix() { return this->matrix; }
	char** unit_row(vector<cell*> cells, int capacity);

};

void cell::init_matrix() {
	this->matrix = new char*[3];
	for (int i = 0; i < 3; i++) {
		this->matrix[i] = new char[3];
	}
}

void cell::cell_to_array() {
	int current_point = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			++current_point;
			switch (current_point) {
				case 2: this->top == true ? this->matrix[i][j] = ' ' : this->matrix[i][j] = '@'; break;
				case 4: this->left == true ? this->matrix[i][j] = ' ' : this->matrix[i][j] = '@'; break;
				case 5: this->center == true ? this->matrix[i][j] = '*' : this->matrix[i][j] = ' '; break;
				case 6: this->right == true ? this->matrix[i][j] = ' ' : this->matrix[i][j] = '@'; break;
				case 8: this->bottom == true ? this->matrix[i][j] = ' ' : this->matrix[i][j] = '@'; break;
			default: matrix[i][j] = '@'; break;
			}
		}
	}
}
void cell::calc_opened_wall() {
	srand(time(NULL));
	int result = 0;
	random_device rd;
	uniform_int_distribution<int> uid(1, 4);
	uniform_int_distribution<int> max_opened_walls_generate(4, 4);
	int prev = 0;
	int max_opened_walls = max_opened_walls_generate(rd);
	for (int i = 0; i < max_opened_walls; i++) {
		while (prev == result) {
			result = uid(rd);
			if (prev == result) { result = uid(rd); }
		}
		prev = result;
		switch (result) {
			case 1: this->top = true; break;
			case 2: this->left = true; break;
			case 3: this->right = true; break;
			case 4: this->bottom = true; break;
		default: break;
		}
	}
}
char** cell::unit_row(vector<cell*> cells, int capacity) {
	char** result = new char*[capacity * 3];
	for (int i = 0; i < 3; i++) {
		result[i] = new char[capacity * 3];
	}
	for (int row = 0; row < 3; row++) {
		int elem = 0;
		int count = 0;
		for (int i = 0; i < capacity * 3; i++) {
			if (i % 3 == 0) {
				for (int col = 0; col < 3; col++) {
					result[row][count] = cells.at(elem)->matrix[row][col];
					++count;
				}
				++elem;
			}
			if (i == capacity * 3) {
				row++;
				i = 0;
				if (row == 3) { break; }
			}
		}
	}
	return result;
}
void cell::unit(vector<cell*> cells, int capacity) {
	vector<cell*> row_to_unit;
	int position = -1;
	for (int i = 0; i < capacity; i++) {
		row_to_unit.clear();
		for (int j = 0; j < capacity; j++) {
			++position;
			row_to_unit.push_back(cells.at(position));
		}
		this->print_rows_of_united_matrix(this->unit_row(row_to_unit, capacity), capacity);
	}
}

void cell::print_rows_of_united_matrix(char** result, int capacity) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < capacity * 3; j++) {
			cout << result[i][j] << " ";
		}
		cout << endl;
	}
}
void cell::print() {
	//SetConsoleOutputCP(CP_UTF8);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << this->matrix[i][j] << "\t";
		}
		cout << endl; cout << endl;
	}
	cout << endl; cout << endl;
}
void cell::clear_Y_matrix_TOP(int current_iterator, int max_iter) {
	if (current_iterator == 1) {
		this->left = false;
		this->top = false;
	}
	if (current_iterator == max_iter) {
		this->right = false;
	}
	if (!(current_iterator == 1) && !(current_iterator == max_iter)) {
		this->top = false;
	}
}


void cell::clear_Y_matrix_BOTTOM(int current_iterator, int max_iter, int start_position) {
	if (current_iterator == start_position) {
		this->left = false;
		this->bottom = false;
	}
	if (current_iterator == max_iter) {
		this->right = false;
		this->bottom = false;
	}
	if (!(current_iterator == start_position) && !(current_iterator == max_iter)) {
		this->bottom = false;
	}
}

void cell::clear_X_matrix_LEFT(int current_iterator, int max_iter) {
	if (current_iterator == 1) {
		this->left = false;
		this->top = true;
	}
	if (!(current_iterator == 1) && !(current_iterator == max_iter)) {
		this->left = false;
	}
	if (current_iterator == max_iter) {
		this->left = false;
		this->bottom = false;
	}

}

void cell::clear_X_matrix_RIGHT(int current_iterator, int max_iter, int start_position) {
	if (current_iterator == start_position) {
		this->right = false;
		this->top = false;
	}
	if (!(current_iterator == start_position) && !(current_iterator == max_iter)) {
		this->right = false;
	}
	if (current_iterator == max_iter) {
		this->right = false;
		this->bottom = true;
	}
}
