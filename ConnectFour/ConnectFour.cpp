#include <iostream>
#include <vector>
using namespace std;


const char player[2] = { 'O','X' };
int curtPlayer = 0;

class Map {
private:
	int colCount = 7, rowCount = 6;
	char** map;
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
	~Map() { }

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
				return i;
			}
		}
		return -1;
	}

	bool checkLink(int col, int row, int num) {
		int count = 1;
		char label = map[col][row];
		//Vertical
		for (int i = row - 1; i >= 0; i--) {
			if (map[col][i] == label) { ++count; }
			else { break; }
		}
		if (count >= num) { cout << "V"; return true; }

		//Horizontal
		int countPve = 1; int countNve = 0;
		for (int i = col + 1; i<colCount; i++) {
			if (map[i][row] == label) { ++countPve; }
			else { break; }
		}
		for (int i = col - 1; i >=0; i--) {
			if (map[i][row] == label) { ++countNve; }
			else { break; }
		}
		if (countPve + countNve >= num) { cout << "H"; return true; }

		//Diagonal (backslash)
		countPve = 1; countNve = 0;
		for (int i = 1;; i++) {
			int indexCol = col + i;
			int indexRow = row - i;
			if (indexCol >= colCount || indexRow < 0) { break; }

			if (map[indexCol][indexRow] == label) { ++countPve; }
			else { break; }
		}

		for (int i = 1;; i++) {
			int indexCol = col - i;
			int indexRow = row + i;
			if (indexCol <0 || indexRow >= rowCount) { break; }

			if(map[indexCol][indexRow] == label) { ++countNve; }
			else { break; }
		}
		if (countPve + countNve >= num) { cout << "backslash"; return true; }

		//Diagonal (slash)
		countPve = 1; countNve = 0;
		for (int i = 1;; i++) {
			int indexCol = col + i;
			int indexRow = row + i;
			if (indexCol >= colCount || indexRow >= rowCount) { break; }

			if (map[indexCol][indexRow] == label) { ++countPve; }
			else { break; }
		}

		for (int i = 1;; i++) {
			int indexCol = col - i;
			int indexRow = row - i;
			if (indexCol < 0 || indexRow < 0) { break; }

			if (map[indexCol][indexRow] == label) { ++countNve; }
			else { break; }
		}
		if (countPve + countNve >= num) { return true; }

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


#pragma region GET PLAYER INPUT
char getSingleChar() {

	char ch = ' ';
	for (;;) {
		cin >> ch;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error! ";
		}
		else {
			return ch;
		}
	}
}

bool getBool() {
	char ch = ' ';
	for (;;) {
		cout << "(y/n):";
		cin >> ch;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error! ";
		}
		else if (ch == 'y' || ch == 'Y' ) {
			return true;
		}
		else if (ch == 'n' || ch == 'N') {
			return false;
		} 
	}
}
int getNumber() {
	int num = 0;
	for (;;) {
		cin >> num;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid Input!" << endl;
		}
		else {
			return num;
		}
	}
}
int getNumber(int min, int max) {
	int num = 0;
	for (;;) {
		cout << "(between " << min << " and " << max << "):";
		cin >> num;
		if (cin.fail() || num<min || num>max) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid Input!" << endl;
		}
		else {
			return num;
		}
	}
}
#pragma endregion


void gameSetup(int s[5]) {
	system("CLS");
	cout << "Columns ";
	int col = getNumber(4, 20);
	s[0] = col;

	cout << "Rows ";
	int row = getNumber(4, 20);
	s[1] = row;

	cout << "Required to win ";
	int win = getNumber(3, 20);
	s[2] = win;

	cout << "Wrap around ";
	int wrap = getBool() ? 1 : 0;
	s[4] = wrap;

	cout << "Can remove from bottom ";
	int remove = getBool() ? 1 : 0;
	s[5] = remove;
	return;
}

void gameLoop(int args[5]) {
	Map* map = new Map(args[0], args[1]);
	
	for (;;) {
		system("CLS");
		//Show current player
		cout << "Player " << player[curtPlayer] << "'s turn. " << endl;

		//Show map
		map->show();

		//Player Input
		int col = 0, row = 0;
		for (;;) {
			cout << "Please Enter an integer ";
			col = getNumber(1, args[0]);
			row = map->addPiece(col - 1, player[curtPlayer]);
			if (row == -1) {
				cout << "This column is full! Try another one." << endl;
			}
			else { break; }
		}
		system("CLS");
		map->show();

		//Game End?
		if (map->checkLink(col - 1, row, args[2])) {
			cout << "Player " << player[curtPlayer] << " win!!!" << endl;
			break;
		}
		if (map->isFull()) {
			cout << "Draw!!!" << endl;
			break;
		}
		//Next Player
		curtPlayer = (curtPlayer + 1) % 2;
	}

	return;
}

int main() {
	bool restart = true;
	do{
		int setting[5] = { 7,6,4,0,0 };
		gameSetup(setting);
		//gameLoop(setting);

		Map* map = new Map(setting[0], setting[1]);

		//Game Loop
		for (;;) {
			system("CLS");
			//Show current player
			cout << "Player " << player[curtPlayer] << "'s turn. " << endl;

			//Show map
			map->show();

			//Player Input
			int col = 0, row = 0;
			for (;;) {
				cout << "Please Enter an integer ";
				col = getNumber(1, setting[0]);
				row = map->addPiece(col - 1, player[curtPlayer]);
				if (row == -1) {
					cout << "This column is full! Try another one." << endl;
				}
				else { break; }
			}
			system("CLS");
			map->show();

			//Game End?
			if (map->checkLink(col - 1, row, setting[2])) {
				cout << "Player " << player[curtPlayer] << " win!!!" << endl;
				break;
			}
			if (map->isFull()) {
				cout << "Draw!!!" << endl;
				break;
			}
			//Next Player
			curtPlayer = (curtPlayer + 1) % 2;
		}

		// Ask player to restart game or not.
		for (;;) {
			cout << "Restart?  ";

			//bool tmp = getBool();
			//if (!tmp) { restart = false; }
			//cout << "end" << endl;
			//break;
			char c = ' ';
			cin >> c;
			if (c == 'Y' || c == 'y') { restart = true; break; }
			else if (c == 'N' || c == 'n') { restart = false; break; }
			else { 
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue; 
			}
		}

	} while (restart);
	return 0;
}
