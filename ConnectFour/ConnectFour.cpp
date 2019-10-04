#include <iostream>
using namespace std;

char** map;
int col, row;
void init() {
	map = new char* [row];
	for (int i = 0; i < row; i++) {
		data[i] = new char[col];
	}

	/*for (auto c : map) {
		c = '-';
	}*/

}


void showMap() {
	/*for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}*/
}
void gameLoop() {
	gameLoop();
}


int main()
{
    cout << "Welcome to Connect Four!\n";
	init();
	showMap();
	//gameLoop();
	return 0;
}
