#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include "Stack.h"
#include "cell.h"
#include "Baedeker.h"
#include "MapService.h"
using namespace std;

int MAX = 3;
int MAX_TOP_X = 0;
int MAX_BOTTOM_X = 0;

int main() {
	setlocale(LC_ALL, "Ru");
	cout << "enter capacity of labirinth:\t";
	cin >> MAX;
	MAX_TOP_X = MAX;
	MAX_BOTTOM_X = (MAX * (MAX - 1)) + 1;

	bool lie = true;
	MapService mapService(MAX, MAX_TOP_X, MAX_BOTTOM_X);
	Baedeker baedeker(mapService.createMap(), MAX, MAX_TOP_X, MAX_BOTTOM_X);
	vector<int> result_way = baedeker.start_search_the_way(MAX, MAX*MAX, 1);

	while (lie) {
		if (result_way.at(0) == 0 && result_way.size() <= 1) {
			Baedeker baedeker(mapService.createMap(), MAX, MAX_TOP_X, MAX_BOTTOM_X);
			result_way = baedeker.start_search_the_way(MAX, MAX*MAX, 1);
		} else {
			lie = false;
		}
	}
	result_way.erase(result_way.begin());
	result_way.push_back(0);
	Stack<int> stack(result_way.size());
	for (int i = result_way.size() - 1; i >= 0; i--) {
		stack.push(result_way.at(i));
	}
	cout << "\nHas found the way\nCoordinates:\t"; stack.printStack();
	system("pause");
	return 0;
}