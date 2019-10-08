#include <iostream>
#include <string>

using namespace std;

const char player[2] = { 'O','X' };
int curtPlayer = 0;

class Map {
private:
	int colCount = 7, rowCount = 6;
	char** map;
	int piecesNum = 0;
public:
	void initMap() {
		map = new char* [colCount];
		for (int i = 0; i < colCount; i++) {
			map[i] = new char[rowCount];
			for (int j = 0; j < rowCount; j++) {
				map[i][j] = '-';
			}
		}
	}

	Map() { initMap(); }
	Map(int col, int row) {
		colCount = col;
		rowCount = row;
		initMap();
	}
	~Map() { 
		for (int i = colCount - 1; i > 0; i--) {
			delete[] map[i];
		}
		delete[] map;
	}
	char getLabel(int col, int row) {
		return map[col][row];
	}

	int cSize() { return colCount; }
	int rSize() { return rowCount; }

	void show() {
		for (int i = 0; i < colCount; i++) {
			cout << (i + 1) << ((i+1 > 9) ? "" : " ");
		}
		cout << "\n";
		for (int i = rowCount - 1; i >= 0; i--) {
			for (int j = 0; j < colCount; j++) {
				cout << map[j][i] << " ";
			}
			cout << "\n";
		}
	}

	int append(int col, char ch) {
		for (int i = 0; i < rowCount; i++) {
			if (map[col][i] == '-') { 
				map[col][i] = ch; 
				++piecesNum;
				return i;
			}
		}
		return -1;
	}
	int remove(int col) {
		if (map[col][0] == '-') { return -1; }

		int row = rowCount - 1;

		for (int i = 0; i < rowCount - 1; i++) {
			if (map[col][i] != '-') {
				map[col][i] = map[col][i + 1];
			}
			else {
				row = i;
				break;
			}
		}
		--piecesNum;
		map[col][row] = '-';
		return row;
	}

	bool checkLink(int col, int row, int num, int wrap) {
		int count = 1;
		char label = map[col][row];

		//Vertical
		for (int i = row - 1; i >= 0; i--) {
			if (map[col][i] == label) { ++count; }
			else { break; }
		}
		if (count >= num) { return true; }
		
		//Horizontal
		int countPve = 0; int countNve = 0;
		for (int i = col; i<colCount; i = (wrap == 0) ? (i + 1) : ((i + 1) % colCount)) {
			if (map[i][row] == label) { ++countPve; }
			else { break; }
		}
		for (int i = col; i >=0; i= (wrap == 0) ? (i - 1) : ((i - 1 + colCount) % colCount)) {
			if (map[i][row] == label) { ++countNve; }
			else { break; }
		}
		if (countPve + countNve - 1 >= num) { return true; }

		//Diagonal (backslash)'\'
		countPve = 0; countNve = 0;
		for (int i = 0;; i++) {
			int indexCol = (wrap == 0) ? (col + i) : ((col + i) % colCount);
			int indexRow = row - i;
			if (indexCol >= colCount || indexRow < 0) { break; }

			if (map[indexCol][indexRow] == label) { ++countPve; }
			else { break; }
		}
		for (int i = 0;; i++) {
			int indexCol = (wrap == 0) ? (col - i) : ((col - i + colCount) % colCount);
			int indexRow = row + i;
			if (indexCol <0 || indexRow >= rowCount) { break; }

			if(map[indexCol][indexRow] == label) { ++countNve; }
			else { break; }
		}
		if (countPve + countNve - 1 >= num) { return true; }

		//Diagonal (slash)'/'
		countPve = 0; countNve = 0;
		for (int i = 0;; i++) {
			int indexCol = (wrap == 0) ? (col + i) : ((col + i) % colCount);
			int indexRow = row + i;
			if (indexCol >= colCount || indexRow >= rowCount) { break; }

			if (map[indexCol][indexRow] == label) { ++countPve; }
			else { break; }
		}
		for (int i = 0;; i++) {
			int indexCol = (wrap == 0) ? (col - i) : ((col - i + colCount) % colCount);
			int indexRow = row - i;
			if (indexCol < 0 || indexRow < 0) { break; }

			if (map[indexCol][indexRow] == label) { ++countNve; }
			else { break; }
		}
		if (countPve + countNve - 1 >= num) { return true; }

		return false;
	}

	bool isFull() {
		return (piecesNum == colCount * rowCount) ? true : false;
	}
	bool isEmpty() {
		return piecesNum == 0 ? true : false;
	}
};

#pragma region GET PLAYER INPUT
string getString() {
	for (;;) {
		string str = "";
		getline(cin, str);
		cin.clear();
		if (str.length() > 0) { return str; }
		else { cout << "Invalid Input please try again:"; }
	}
}

bool getBoolean() {
	for (;;) {
		cout << "(y/n):";
		string str = getString();
		if (str.length() > 1) { continue; }
		char ch = str[0];
		if (ch == 'y' || ch == 'Y') { return true; }
		if (ch == 'n' || ch == 'N') { return false; }
	}
}

int getInteger() {
	bool success = false;
	string str = "";
	do {
		success = false;
		str = getString();
		char* chs = new char[str.length() + 1];
		strcpy_s(chs, str.length() + 1, str.c_str());
		for (int i = 0; i < str.length(); i++) {
			int tmp = (int)chs[i];
			if (tmp < 48 || tmp > 57) {
				cout << "Not an Integer! Please enter a Integer:";
				success = true;
				break;
			}
		}
	} while (success);
	return stoi(str);
}


int getNumber(int min, int max) {
	int num = 0;
	for (;;) {
		cout << "(between " << min << " and " << max << "):";
		num = getInteger();
		if (num >= min && num <= max) { return num; }
		else {
			cout << "Invalid Input" << endl;
		}
	}
}
#pragma endregion


int main() {
	bool restart = true;
	do{
		int col = 0, row = 0;
		int win = 0;
		bool wrapFlag = false;
		bool canRemove = false;

	#pragma region SETUP
		cout << "Columns ";
		col = getNumber(4, 20);

		cout << "\nRows ";
		row = getNumber(4, 20);

		cout << "\nRequired to win ";
		win = getNumber(3, 20);

		cout << "\nWrap around ";
		wrapFlag = getBoolean();

		cout << "\nCan remove from bottom ";
		canRemove = getBoolean();
	#pragma endregion

	#pragma region GAME LOOP

		bool gameEnd = true;

		Map* map = new Map(col, row);

		do {
			system("CLS");
			//Show current player
			cout << "Player " << player[curtPlayer] << "'s turn. " << endl;

			//Show map
			map->show();

			//Player Input
			int cIndex = 0, rIndex = 0;
			bool removeFlag = false;
			if (canRemove && !map->isEmpty()) {
				cout << "Do you want to remove from the bottom? ";
				removeFlag = getBoolean();
			}
			if (canRemove && map->isFull()) {
				removeFlag = true;
			}
			// Add piece to selected column
			if (!removeFlag) {
				for (;;) {
					cout << "Please Enter a column to insert ";
					cIndex = getNumber(1, col) - 1;
					rIndex = map->append(cIndex, player[curtPlayer]);
					if (rIndex == -1) {
						cout << "This column is full! Try another one." << endl;
					}
					else { break; }
				}
				system("CLS");
				map->show();

				//Game End?
				if (map->checkLink(cIndex, rIndex, win, wrapFlag)) {
					cout << "Player " << player[curtPlayer] << " win!!!" << endl;
					gameEnd = false;
				}
			}
			// Remove piece from selected column
			else {
				for (;;) {
					cout << "Please Enter a column to remove ";
					cIndex = getNumber(1, col) - 1;
					rIndex = map->remove(cIndex);
					if (rIndex == -1) {
						cout << "This column is empty! Try another one." << endl;
					}
					else { break; }
				}
				system("CLS");
				map->show();

				//Game End?
				for (int i = 0; i < rIndex; i++) {
					cout << i << endl;
					if (map->checkLink(cIndex, i, win, wrapFlag)) {
						cout << "Player " << map->getLabel(cIndex, i) << " win!!!" << endl;
						gameEnd = false;
						break;
					}
				}
			}

			if (map->isFull() && !canRemove) {
				cout << "Draw!!!" << endl;
				gameEnd = false;
			}
			//Next Player
			curtPlayer = (curtPlayer + 1) % 2;
		} while (gameEnd);
		map->~Map();
	#pragma endregion

		// Ask player to restart game or not.
		for (;;) {
			cout << "Restart?  ";
			bool tmp = getBoolean();
			if (!tmp) { restart = false; }
			break;
		}

	} while (restart);

	return 0;
}
