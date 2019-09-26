#include <iostream>

using namespace std;
char player = 'X';
char grid[3][3] = 
{'1', '2', '3',
'4', '5', '6', 
'7', '8', '9'};
int counter;

void Draw() {
	system("cls");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
}

void Input(){
	int a;
	cout << "It's"<<player<<" turn \n" << "press the number of the cell you want to change: ";
	cin >> a;

	if (a == 1){
		if (grid[0][0] == '1')		{
			grid[0][0] = player;
		}
		else{
			cout << "Cell Occupied input another cell: " << endl;
			Input();
		}
	}
	if (a == 2) {
		if (grid[0][1] == '2') {
			grid[0][1] = player;
		}
		else {
			cout << "Cell Occupied input another cell: " << endl;
			Input();
		}
	}
	if (a == 3) {
		if (grid[0][2] == '3') {
			grid[0][2] = player;
		}
		else {
			cout << "Cell Occupied input another cell: " << endl;
			Input();
		}
	}
	if (a == 4) {
		if (grid[1][0] == '4') {
			grid[1][0] = player;
		}
		else {
			cout << "Cell Occupied input another cell: " << endl;
			Input();
		}
	}
	if (a == 5) {
		if (grid[1][1] == '5') {
			grid[1][1] = player;
		}
		else {
			cout << "Cell Occupied input another cell: " << endl;
			Input();
		}
	}
	if (a == 6) {
		if (grid[1][2] == '6') {
			grid[1][2] = player;
		}
		else {
			cout << "Cell Occupied input another cell: " << endl;
			Input();
		}
	}
	if (a == 7) {
		if (grid[2][0] == '7') {
			grid[2][0] = player;
		}
		else {
			cout << "Cell Occupied input another cell: " << endl;
			Input();
		}
	}
	if (a == 8) {
		if (grid[2][1] == '8') {
			grid[2][1] = player;
		}
		else {
			cout << "Cell Occupied input another cell: " << endl;
			Input();
		}
	}
	if (a == 9) {
		if (grid[2][2] == '9') {
			grid[2][2] = player;
		}
		else {
			cout << "Cell Occupied input another cell: " << endl;
			Input();
		}
	}
}

void TurnManager()
{
	if (player == 'X')	{
		player = 'O';
	}
	else {
		player = 'X';
	}
}
char Win() {
	/*FIRST PLAYER*/
	//check Row
	if (grid[0][0] == 'X' && grid[0][1] == 'X' && grid[0][2] == 'X'){
		return 'X';
	}
	if (grid[1][0] == 'X' && grid[1][1] == 'X' && grid[1][2] == 'X'){
		return 'X';
	}
	if (grid[2][0] == 'X' && grid[2][1] == 'X' && grid[2][2] == 'X'){
		return 'X';
	}

	//Check Column
	if (grid[0][0] == 'X' && grid[1][0] == 'X' && grid[2][0] == 'X') {
		return 'X';
	}
	if (grid[0][1] == 'X' && grid[1][1] == 'X' && grid[2][1] == 'X') {
		return 'X';
	}
	if (grid[0][2] == 'X' && grid[1][2] == 'X' && grid[2][2] == 'X') {
		return 'X';
	}
	//Check Diagonals
	if (grid[0][0] == 'X' && grid[1][1] == 'X' && grid[2][2] == 'X') {
		return 'X';
	}
	if (grid[0][2] == 'X' && grid[1][1] == 'X' && grid[2][0] == 'X') {
		return 'X';
	}

	/*SECOND PLAYER*/
	if (grid[0][0] == 'O' && grid[0][1] == 'O' && grid[0][2] == 'O') {
		return 'O';
	}
	if (grid[1][0] == 'O' && grid[1][1] == 'O' && grid[1][2] == 'O') {
		return 'O';
	}
	if (grid[2][0] == 'O' && grid[2][1] == 'O' && grid[2][2] == 'O') {
		return 'O';
	}

	//Check Column
	if (grid[0][0] == 'O' && grid[1][0] == 'O' && grid[2][0] == 'O') {
		return 'O';
	}
	if (grid[0][1] == 'O' && grid[1][1] == 'O' && grid[2][1] == 'O') {
		return 'O';
	}
	if (grid[0][2] == 'O' && grid[1][2] == 'O' && grid[2][2] == 'O') {
		return 'O';
	}
	//Check Diagonals
	if (grid[0][0] == 'O' && grid[1][1] == 'O' && grid[2][2] == 'O') {
		return 'O';
	}
	if (grid[0][2] == 'O' && grid[1][1] == 'O' && grid[2][0] == 'O') {
		return 'O';
	}

	return '/';
}

int main()
{
	counter = 0;
	Draw();
	while (1)
	{
		counter++;
		Input();
		Draw();
		if (Win() == 'X') {
			cout << "PLayer one Wins!" << endl;
			break;
		}
		else if (Win() == 'O'){
			cout << "Player Two Wins!" << endl;
			break;
		}
		else if (Win() == '/' && counter == 9)
		{
			cout << "Draw!!" << endl;
			break;
		}
		TurnManager();
	}
	system("pause");
	return 0;
}