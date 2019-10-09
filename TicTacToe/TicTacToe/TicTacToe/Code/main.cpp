#include <iostream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <algorithm>
#include <limits>

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
	bool IsADraw() {
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
			/*Horizontal*/
			if (grid[i][0] == player && grid[i][1] == player && grid[i][2] == player)
			{
				return true;
			}
			/*Vertical*/
			if (grid[0][i] == player && grid[1][i] == player && grid[2][i] == player)
			{
				return true;
			}
		}
		if (grid[0][0] == player && grid[1][1] == player && grid[2][2] == player)
		{
			return true;
		}
		/*Vertical*/
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
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
			if (turn == 0)
			{
				GetPlayerMove();

				if (CheckVictory(Player::player))
				{
					puts("Player wins! ");
					endGame = true;
				}
			}
			else
			{
				puts("CPU move: ");
				Move AIMove = minimax();
				printf("CPU Move: %d, %d", AIMove.x, AIMove.y);
				grid[AIMove.x][AIMove.y] = Player::cpu;

				if (CheckVictory(Player::cpu))
				{
					puts("CPU Wins.... You Suck! XP");
					endGame = true;
				}
			}

			if (IsADraw())
			{
				puts("IT'S A DRAW!!");
				endGame = true;
			}

			turn ^= 1;
			DrawGrid();


		} while (!endGame);
	}

};
int main()
{
	Game game;
	game.PlayGame();
	cin.ignore();
}