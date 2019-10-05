#include <iostream>
#include <vector>
using namespace std;

class Map {
private:
	int colCount = 7, rowCount = 6;
	vector<vector<char>> map;
public:
	void initMap() {
		for (int i = 0; i < colCount; i++) {
			vector<char> tmp;
			for (int j = 0; j < rowCount; j++) {
				tmp.push_back('-');
			}
			map.push_back(tmp);
		}
	}
	Map() {
		initMap();
	}
	Map(int col, int row) {
		colCount = col;
		rowCount = row;
		initMap();
	}

	int cSize() { return colCount; }
	int rSize() { return rowCount; }

	void show() {
		for (int j = rowCount - 1; j >= 0; j--) {
			for (int i = 0; i < colCount; i++) {
				cout << map[i][j] << " ";
			}
			cout << "\n";
		}
		for (int i = 0; i < colCount; i++) {
			cout << (i+1) << " ";
		}
		cout << "\n";
	}

	int addPiece(int col, char c) {
		for (int i = 0; i < rowCount; i++) {
			if (map[col][i] == '-') { 
				map[col][i] = c; 
				return i;
			}
		}
		return -1;
	}

	int check() {
		return -1;
	}

};

const char player[2] = { 'O','X' };
int curtPlayer = 0;

int main() {
	Map* map = new Map(7,6);
	for (;;) {
		map->show();
		cout <<"\nPlayer " << player[curtPlayer]<< "'s turn. " << "Please Enter 1-" << map->cSize() << ": ";
		char c = cin.get();
		cin.ignore(1, '\n');
		int col = (int)c - 48;
		if (col > 0 && col < map->cSize() + 1) {
			int row = map->addPiece(col - 1, player[curtPlayer]);
			if (row == -1) {
				system("CLS");
				cout << "This column is full! Try another one." << endl;
				continue;
			}
			else {
				int res = map->check();
				if (res != -1) { 
					cout << ((res == 0) ? "Draw!" : "Player") << endl;
					break; 
				}
				else {

				}
				curtPlayer = (curtPlayer + 1) % 2;
				system("CLS");
			}
		}
		else {
			system("CLS");
			cout << "Invalid Input!" << endl;
		}
	}

	return 0;
}
