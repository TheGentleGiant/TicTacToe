#include <iostream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <windows.h>

#define GRID_SIZE 3
using namespace std;

class Game {
	enum class Player {
		empty = '-',
		player = 'X',
		cpu = 'O',
	};

	struct Move {
		unsigned int x = 0;
		unsigned int y = 0;
	};

	Player grid[GRID_SIZE][GRID_SIZE];

public:
	Game() {
		for (unsigned int x = 0; x < GRID_SIZE; x++)
		{
			for (unsigned int y = 0; y < GRID_SIZE; y++)
			{
				grid[x][y] = Player::empty;
			}
		}
	}

	void DrawGrid() {
		system("cls");
		printf("---------------\n");
		for (unsigned int x = 0; x < GRID_SIZE; ++x)
		{
			for (unsigned int y = 0; y < GRID_SIZE; y++)
			{
				printf(" %c |", grid[x][y]);
			}
			printf("\n---------------\n");
		}
	}
	bool CanPlay(Player grid[GRID_SIZE][GRID_SIZE]) {
		for (int i =0; i < GRID_SIZE; i++)
		{
			for (int j =0; j < GRID_SIZE; j++)
			{
				if (grid[i][j] == Player::empty)
				{
					return true;
				}
			}
		}
		return false;
	}

	//
	int CheckVictory( Player grid[GRID_SIZE][GRID_SIZE]) {
		
		/*Horizontal*/
		for (int r = 0; r < GRID_SIZE; r++)
		{
			if (grid[r][0] == grid[r][1] && grid[r][1] == grid[r][2])
			{
				if (grid[r][0] == Player::player)
				{
					return +10;
				}
				else if (grid[r][0] == Player::cpu) {
					return -10;
				}
			}
		}
		/*Vertical*/
		for (int c = 0; c < GRID_SIZE; c++)
		{
			if (grid[0][c] == grid[1][c] && grid[1][c] == grid[2][c])
			{
				if (grid[0][c] == Player::player)
				{
					return +10;
				}
				else if (grid[0][c] == Player::cpu) {
					return -10;
				}
			}
		}
		//Diagonals
		if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
		{
			if (grid[0][0] == Player::player)
			{
				return +10;
			}
			else if (grid[0][0] == Player::cpu)
			{
				return -10;
			}
		}
		if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
		{
			if (grid[0][2] == Player::player)
			{
				return +10;
			}
			else if (grid[0][2] == Player::cpu)
			{
				return -10;
			}
		}

		return 0;
	}

	int Minimax(Player grid[GRID_SIZE][GRID_SIZE], int depth, bool bIsMaxValue) {
		int score = CheckVictory(grid);
		if (score == 10)
		{
			return score;
		}

		if (score == -10)
		{
			return score;
		}

		if (CanPlay(grid) == false)
		{
			return 0;
		}

		if (bIsMaxValue)
		{
			int bestValue = -1000;

			for (int i =0; i< GRID_SIZE; i++)
			{
				for (int j =0; j < GRID_SIZE; j++ )
				{
					if (grid[i][j] == Player::empty)
					{
						grid[i][j] = Player::player;
						bestValue = max(bestValue, Minimax(grid, depth + 1, !bIsMaxValue));
						grid[i][j] = Player::empty;
					}
				}
			}
			return bestValue;

		}
		else {
			int bestValue = 1000;
			for (int i =0;i < GRID_SIZE; i++)
			{
				for (int j =0; j < GRID_SIZE; j++)
				{
					if (grid[i][j] == Player::empty)
					{
						grid[i][j] = Player::cpu;
						bestValue = min(bestValue, Minimax(grid, depth + 1, !bIsMaxValue));
						grid[i][j] = Player::empty;
					}
				}
			}
			return bestValue;
		}
	}

	Move GetCPUMove(Player grid[GRID_SIZE][GRID_SIZE])
	{
		int bestValue = -1000;
		Move bestPossibleMove;
		bestPossibleMove.x = -1;
		bestPossibleMove.y = -1;

		for (int i =0; i < GRID_SIZE; i++)
		{
			for (int j =0; j < GRID_SIZE; j++)
			{
				if (grid[i][j] == Player::empty)
				{
					grid[i][j] = Player::player;
					int temp = Minimax(grid, 0, false);

					grid[i][j] = Player::empty;
					if (temp > bestValue)
					{
						bestPossibleMove.x = i;
						bestPossibleMove.y = j;
						bestValue = temp;
					}
				}
			}
		}
		printf("CPU move value is : %d \n", bestValue);
		return bestPossibleMove;
	}

	void GetPlayerMove() {
		bool failedMove = true;
		unsigned int x = -1, y = -1;

		do
		{
			puts("Player Move: ");
			char move;
			std::cin >> move;
			x = move - '0';
			std::cin >> move;
			y = move - '0';

			failedMove = grid[x][y] != Player::empty;

			std::cin.clear();
		} while (failedMove);

		grid[x][y] = Player::player;
	}

	void PlayGame() {
		unsigned int turn = 0;
		bool endGame = false;

		DrawGrid();
		puts("Enter the ROW and COLUMN you wish to play in: ");

		do
		{
			if (turn %2 == 0)
			{
				GetPlayerMove();

				if (CheckVictory(grid))
				{
					puts("Player wins! ");
					endGame = true;
				}
			}
			else
			{
				puts("CPU move: ");
				Move m = GetCPUMove(grid);
				grid[m.x][m.y] = Player::cpu;
				if (CheckVictory(grid))
				{
					puts("CPU Wins.... You Suck! XP");
					endGame = true;
				}
			}
			DrawGrid();
			turn++;

		} while (!endGame);
	}
	/*bool IsADraw() {
		for (unsigned int i = 0; i < GRID_SIZE; i++)
		{
			if (grid[i][0] == Player::empty||grid[i][1] == Player::empty||grid[i][2]== Player::empty)
			{
				return false;
			}
		}
		return true;
	}

	bool CheckVictory(Player player) {
		for (unsigned int i = 0; i < GRID_SIZE; i++)
		{
			/ *Horizontal* /
			if (grid[i][0] == player && grid[i][1] == player && grid[i][2] == player)
			{
				return true;
			}
			/ *Vertical* /
			if (grid[0][i] == player && grid[1][i] == player && grid[2][i] == player)
			{
				return true;
			}
		}
		if (grid[0][0] == player && grid[1][1] == player && grid[2][2] == player)
		{
			return true;
		}
		/ *Vertical* /
		if (grid[0][2] == player && grid[1][1] == player && grid[2][0] == player)
		{
			return true;
		}

		return false;
	}

	Move minimax() {
		int score = std::numeric_limits<int>::max();
		Move move;

		for (unsigned int i = 0; i < GRID_SIZE; i++)
		{
			for (unsigned int j = 0; j < GRID_SIZE; j++)
			{
				if (grid[i][j] == Player::empty)
				{
					grid[i][j] = Player::cpu;
					
					int temp = MaxSearch();

					if (temp < score)
					{
						score = temp;
						move.x = i;
						move.y = j;
					}

					grid[i][j] = Player::empty;
				}
			}
		}
		return move;
	}

	int MaxSearch() {
		if (CheckVictory(Player::player))
		{
			return 10;
		}
		else if (CheckVictory(Player::cpu))
		{
			return -10;
		}
		else if (IsADraw())
		{
			return 0;
		}

		int score = std::numeric_limits<int>::min();

		for (unsigned int i = 0; i < GRID_SIZE; i++)
		{
			for  (unsigned int j = 0; j < GRID_SIZE; j++)
			{
				if (grid[i][j] == Player::empty)
				{
					grid[i][j] = Player::player;
					score = std::max(score, MinSearch());
					grid[i][j] = Player::empty;
				}
			}
		}

		return score;
	}
	int MinSearch() {
		if (CheckVictory(Player::player))
		{
			return 10;
		}
		else if (CheckVictory(Player::cpu))
		{
			return -10;
		}
		else if (IsADraw())
		{
			return 0;
		}

		int score = std::numeric_limits<int>::max();

		for (unsigned int i = 0; i < GRID_SIZE; i++)
		{
			for (unsigned int j = 0; j < GRID_SIZE; j++)
			{
				if (grid[i][j] == Player::empty)
				{
					grid[i][j] = Player::cpu;
					score = std::max(score, MaxSearch());
					grid[i][j] = Player::empty;
				}
			}
		}

		return score;
	}

	
*/

};
int main()
{
	Game game;
	game.PlayGame();
	cin.ignore();
}