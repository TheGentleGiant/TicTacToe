#include <iostream>
#include <string>
#include <stdlib.h>

#define GRID_SIZE 3
using namespace std;

class Game {
private :
	char grid[GRID_SIZE][GRID_SIZE];
public:
	Game() {
		GenerateGrid();
		DrawGrid();
		CheckVictory();
		while (true)
		{
			ChectTurn();
			DrawGrid();
			CheckVictory();

			CPUTurn();
			DrawGrid();
			CheckVictory();
		}
	}

	void CPUTurn() {
		
		while (true)
		{
			int CPUChoice = (rand() % 9) + 1;
			

			int row = (CPUChoice - 1) / GRID_SIZE;
			int column = (CPUChoice - 1) % GRID_SIZE;

			char gridPos = grid[row][column];

			if (gridPos == 'X'|| gridPos == '0')
			{
				continue;
			}
			else
			{
				printf("CPU choice was: %d \n", CPUChoice);
				grid[row][column] = 'O';
				break;
			}
		}
	}

	void CheckVictory() {
		const char* PossibleWinCombinations[8] = {
			"123",
			"456",
			"789",
			"147",
			"258",
			"369",
			"159",
			"753",
		};

		for (int  i = 0; i < 8; i++)
		{
			bool hasWon = true;
			char previousValue = '0';
			const char* WinningMove = PossibleWinCombinations[i];
			
			for (int j = 0; j < 3; j++)
			{
				char character = WinningMove[j];

				int enteredNumber = character - '0';
				int gridSpace = enteredNumber - 1;
				int row = gridSpace / GRID_SIZE;
				int column = gridSpace % GRID_SIZE;

				char gridChar = grid[row][column];

				if (previousValue == '0')
				{
					previousValue = gridChar;
				}
				else if (previousValue == gridChar)
				{
					continue;
				}
				else {
					hasWon = false;
					break;
				}
			}
			if (hasWon)
			{
				puts("!!!! We Have A Winner !!!!");
				printf("Looks like %c won, Greetings!!", previousValue);

				exit(0);
				break;

			}

		}
		
	}

	void GenerateGrid() {
		int counter = 1;
		for (int x = 0; x < GRID_SIZE; ++x)
		{
			for (int  y = 0; y < GRID_SIZE; y++)
			{
				grid[x][y] = to_string(counter).c_str()[0];
				counter++;
			}
		}
	}
	void DrawGrid() {
		system("cls");
		printf("---------------\n");
		for (int x = 0; x < GRID_SIZE; ++x)
		{
			for (int y = 0; y < GRID_SIZE; y++)
			{
				printf(" %c |", grid[x][y]);
			}
			printf("\n---------------\n");
		}
	}
	void ChectTurn() {
		string input;
		while (true)
		{
			puts("In which cell would you like to play?");
			getline(cin, input);

			if (input != "")
			{
				char entered = input.c_str()[0];
				if (entered >= '1' && entered <= '9')
				{
					int enteredNumber = entered - '0';
					int index = enteredNumber - 1;

					int row = index / GRID_SIZE;
					int column = index % GRID_SIZE;

					char gridPos = grid[row][column];
					//printf("you want to play at position: %c \n", gridPos);
					if (gridPos == 'X' || gridPos == 'O')
					{
						puts("That cell is already occupied!");
					}
					else {
						grid[row][column] = 'X';
						break;
					}
				}
				else {
					puts("please enter a valid number between 1 and 9!");
				}
			}
			else {
				puts("please type something!");
			}
		}
	}
};
int main()
{
	Game game;

	system("pause");
	return 0;
}