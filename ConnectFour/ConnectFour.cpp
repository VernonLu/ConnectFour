#include <iostream>
using namespace std;


//char** map;
const int col = 7, row = 6;
char map[col][row];
const char player[2] = { 'O','X' };
int curtPlayer = 0;


void init() {
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			map[i][j] = '-';
		}
	}
}


void showMap() {
	for (int i = row - 1; i >= 0; i--) {
		cout << "\t";
		for (int j = 0; j < col; j++) {
			cout << map[j][i] << " ";
		}
		cout << endl;
	}
	cout << "\t";
	for (int i = 0; i < col; i++) {
		cout << i + 1 << " ";
	}
	cout << endl;
}

void showPlayer() {
	cout << "Player " << player[curtPlayer] << "'s turn, Please Enter 1-7: ";
}

bool check() {
	return true;
}

void gameLoop() {
	showMap();
	showPlayer();
	char c;
	while ((c = cin.get()) != EOF) {
		int num = (int)c;
		if (num > 0 && num < col + 1) {
			num -= 1;
			curtPlayer = (curtPlayer + 1) % 2;
		}
	}
	system("CLS");
	cout << "you entered:" << c << endl;
}


int main()
{


	init();
	while (check()) {
		gameLoop();
	}


	return 0;
}
