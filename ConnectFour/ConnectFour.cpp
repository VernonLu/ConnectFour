#include <iostream>
using namespace std;


//char** map;
const int col = 7, row = 6;
char map[row][col];
const char player[2] = { 'O','X' };
int curtPlayer = 0;


void init() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			map[i][j] = '-';
		}
	}
}


void showMap() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
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
	//char in = cin.get();
	char in = 0;
	cin.get(in);

	if ((int)in > 48 && (int)in < 56) {
		in -= 49;
		curtPlayer = (curtPlayer + 1) % 2;
	}
	cout << "you entered " << (int)in << endl;
}


int main()
{


	init();
	while (check()) {
		gameLoop();
	}


	return 0;
}
