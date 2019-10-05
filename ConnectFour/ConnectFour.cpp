#include <iostream>
#include <vector>
using namespace std;

class Piece {
public:
	int col;
	int row;
	char label;
	void set(int c,int r, char ch){
		col = c;
		row = r;
		label = ch;
	}
};

class Map {
private:
	int colCount = 7, rowCount = 6;
	vector<vector<char>> map;
	Piece lastPiece;
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
	~Map() {
		for (vector<char> col : map) {
			vector<char>().swap(col);
		}
		vector<vector<char>>().swap(map);
	}

	int cSize() { return colCount; }
	int rSize() { return rowCount; }

	void show() {
		for (int i = rowCount - 1; i >= 0; i--) {
			for (int j = 0; j < colCount; j++) {
				cout << map[j][i] << " ";
			}
			cout << "\n";
		}
		for (int i = 0; i < colCount; i++) {
			cout << (i + 1) << ((i+1 > 9) ? "" : " ");
		}
		cout << "\n";
	}

	int addPiece(int col, char ch) {
		for (int i = 0; i < rowCount; i++) {
			if (map[col][i] == '-') { 
				map[col][i] = ch; 
				lastPiece.set(col, i, ch);
				return i;
			}
		}
		return -1;
	}

	bool checkLink() {
		int count = 1;
		//Vertical
		for (int i = lastPiece.row - 1; i >= 0; i--) {
			if (map[lastPiece.col][i] == lastPiece.label) { ++count; }
			else { break; }
		}
		if (count >= 4) { return true; }

		//Horizontal
		int countPve = 1; int countNve = 0;
		for (int i = lastPiece.col + 1; i<colCount; i++) {
			if (map[i][lastPiece.row] == lastPiece.label) { ++countPve; }
			else { break; }
		}
		for (int i = lastPiece.col - 1; i >=0; i--) {
			if (map[i][lastPiece.row] == lastPiece.label) { ++countNve; }
			else { break; }
		}
		if (countPve + countNve >= 4) { return true; }

		//Diagonal
		countPve = 1; countNve = 0;
		for (int i = 1;; i++) {
			int indexCol = lastPiece.col + i;
			int indexRow = lastPiece.row - i;
			if (indexCol >= colCount || indexRow < 0) { break; }

			if (map[indexCol][indexRow] == lastPiece.label) { ++countPve; }
			else { break; }
		}

		for (int i = 1;; i++) {
			int indexCol = lastPiece.col - i;
			int indexRow = lastPiece.row + i;
			if (indexCol <0 || indexRow >= rowCount) { break; }

			if(map[indexCol][indexRow] == lastPiece.label) { ++countNve; }
			else { break; }
		}
		if (countPve + countNve >= 4) { return true; }

		//Diagonal
		countPve = 1; countNve = 0;
		for (int i = 1;; i++) {
			int indexCol = lastPiece.col + i;
			int indexRow = lastPiece.row + i;
			if (indexCol >= colCount || indexRow >= rowCount) { break; }

			if (map[indexCol][indexRow] == lastPiece.label) { ++countPve; }
			else { break; }
		}

		for (int i = 1;; i++) {
			int indexCol = lastPiece.col - i;
			int indexRow = lastPiece.row - i;
			if (indexCol < 0 || indexRow < 0) { break; }

			if (map[indexCol][indexRow] == lastPiece.label) { ++countNve; }
			else { break; }
		}
		if (countPve + countNve >= 4) { return true; }

		return false;
	}
	bool isFull() {
		for (int i = 0; i < rowCount; i++) {
			for (int j = 0; j < colCount; j++) {
				if (map[j][i] == '-') { return false; }
			}
		}
		return true;
	}

};

const char player[2] = { 'O','X' };
int curtPlayer = 0;

//int gameLoop() {
//
//	gameLoop();
//}
char getSingleChar() {
	char c = cin.get();
	cin.ignore(1, '\n');
	return c;
}

void newGame(int col, int row) {
	system("CLS");
	Map* map = new Map(col, row);
	curtPlayer = 0;
	for (;;) {
		map->show();
		if (map->checkLink()) {
			cout << "Player " << player[(curtPlayer + 1) % 2] << " win!" << endl;
			return;
		}
		if (map->isFull()) {
			cout << "Draw!" << endl;
			return;
		}

		cout << "\nPlayer " << player[curtPlayer] << "'s turn. " << "Please Enter 1-" << map->cSize() << ": ";
		int c = 0;
		cin >> c;
		cin.ignore(10000, '\n');	


		int col = (int)c;
		/*char c = cin.get();
		cin.ignore(2, '\n');
		int col = (int)c - 48;*/
		// Check input
		if (col > 0 && col < map->cSize() + 1) {
			//Check
			int row = map->addPiece(col - 1, player[curtPlayer]);
			if (row == -1) {
				system("CLS");
				cout << "This column is full! Try another one." << endl;
				continue;
			}
			else {
				curtPlayer = (curtPlayer + 1) % 2;
				system("CLS");
			}
		}
		else {
			system("CLS");
			cout << "Invalid Input!" << endl;
		}
	}



}

int main() {
	newGame(12, 8);
	cout << "Enter 'R' to restart, other character to exit:";
	char c = cin.get();
	cin.ignore(1, '\n');
	if (c == 'R' || c == 'r') { main(); }
	return 0;
}
