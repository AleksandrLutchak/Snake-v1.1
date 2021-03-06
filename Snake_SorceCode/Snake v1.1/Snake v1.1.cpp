#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

void gameSettings();
void levelOfDiff(short n);
void board();
void snake();
int food();
void kbCheck();
int GameOver();
void restart();

const int _boardX = 20;
const int _boardY = 20;
const int _Nsnake = 100;

char _boardLines	= '#';
char _snakeSym		= 'O';
char _foodSym		= '*';
char _sprFoodSym	= '@';
char _board[_boardX][_boardY]{};

short _scale;

int _sleepScale = 0;
int tailX[_Nsnake]{}; int tailY[_Nsnake]{};
int _snake, _snakeX, _snakeY;
int _foodX, _foodY;
int Score = 0;

bool _exitGame = true, checkFood, _quitTheGame = false;

enum Moves {DEF, UP, DOWN, LEFT, RIGHT};
Moves control;
enum difficulty { EASY, MEDIUM, HARD };
difficulty _diffScale;

int main()
{
	srand(time(NULL));
	
	if (_exitGame)
	{
		cout << "Snake. v1.1\n\nInput is 'WASD', only on English keyboard!\n\nChoose the difficulty level: " << endl ;
		cout << "(Press number, which equals to your level, or enter any symbol for exit.)" << endl;
		cout << "1.Easy    " << "2.Medium    " << "3.Hard\n";
		cin >> _scale;
		cout << "You can exit from the game, during your playing." << endl;

		if (_scale == 1 || _scale == 2 || _scale == 3)
		{
			_scale--;
			gameSettings();
			_exitGame = false;
		}
		else
			return 0;
		
	}

	while (!_exitGame)
	{
		Sleep(_sleepScale);
		system("cls");
		board();
		kbCheck();
		snake();
	}
	GameOver();
	return 0;
}

void gameSettings()
{
	control = DEF;
	_snakeX = _boardX / 2;
	_snakeY = _boardY / 2;
	food();
	levelOfDiff(_scale);
}

void levelOfDiff(short n)
{
	if		(EASY == n)
		_sleepScale = 150;
	else if (MEDIUM == n)
		_sleepScale = 50;
	else if (HARD == n)
		_sleepScale = 10;
}

void board()
{
	for (int x = 0; x < _boardX; x++)
	{
		for (int y = 0; y < _boardY; y++)
		{
			if (x == 0 || x == _boardX - 1 || y == 0 || y == _boardY - 1)
			{
				_board[x][y] = _boardLines;
				cout << _board[x][y];
			}
			else if (x == _snakeX && y == _snakeY)
				cout << _snakeSym;
			else if (x == _foodX && y == _foodY)
			{
				if(checkFood)
				cout << _foodSym;
			}
			else
			{
				bool print = false;
				for (int z = 0; z < _snake; z++)
				{
					if (tailX[z] == x && tailY[z] == y)
					{
						print = true;
						cout << "o";
					}
				}
				if(!print)
					cout << " ";
			}
		}
		cout << endl;
	}
	cout << "Score: " << Score << endl;
}

void kbCheck()
{
	if (_kbhit())
		switch (_getch())
		{
		case 'w':
			if (control == DOWN)
				break;
			else
			control = UP;
			break;

		case 's':
			if (control == UP)
				break;
			else
			control = DOWN;
			break;

		case 'a':
			if (control == RIGHT)
				break;
			else
			control = LEFT;
			break;

		case 'd':
			if (control == LEFT)
				break;
			else
			control = RIGHT;
			break;

		case 'q':
			_exitGame = true;
			_quitTheGame = true;
			break;
		}
}

void snake()
{
	if (_snakeX == _foodX && _snakeY == _foodY)
	{
		food();
		Score++;
		_snake++;
	}

	switch (control)
	{
	case UP:
		if (_snakeX >= _boardX)
			_snakeX = 1;
		else if (_snakeX < 1)
			_snakeX = _boardX - 1;
		else
			if (_snakeY >= _boardY - 1)
			{
				_snakeY = 1;
				_snakeX--;
			}
			else if (_snakeY < 1)
			{
				_snakeY = _boardY - 2;
				_snakeX--;
			}
			else
				_snakeX--;

		cout << "UP";
		break;

		
	case DOWN:
		if (_snakeX >= _boardX)
			_snakeX = 1;
		else if (_snakeX < 1)
			_snakeX = _boardX - 1;
		else
			if (_snakeY >= _boardY - 1 )
			{
				_snakeY = 1;
				_snakeX++;
			}
			else if (_snakeY < 1)
			{
				_snakeY = _boardY - 2;
				_snakeX++;
			}
			else
				_snakeX++;

		cout << "DOWN";
		break;

	case LEFT:
		if (_snakeY >= _boardY - 1)
			_snakeY = 1;
		else if (_snakeY < 1)
			_snakeY = _boardY - 2;
		else
			if (_snakeX >= _boardX - 1)
			{
				_snakeX = 1;
				_snakeY--;
			}

			else if (_snakeX < 1)
			{
				_snakeX = _boardX - 2;
				_snakeY--;
			}
			else
				_snakeY--;
		cout << "LEFT";
		break;

	case RIGHT:
		if (_snakeY >= _boardY - 1)
			_snakeY = 1;
		else if (_snakeY < 1)
			_snakeY = _boardY - 2;
		else
			if (_snakeX >= _boardX - 1)
			{
				_snakeX = 1;
				_snakeY--;
			}

			else if (_snakeX < 1)
			{
				_snakeX = _boardX - 2;
				_snakeY++;
			}
			else
				_snakeY++;
		cout << "RIGHT";
		break;

	}

	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = _snakeX;
	tailY[0] = _snakeY;

	for (int i = 1; i <= _snake; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
		if (tailX[i] == _snakeX && tailY[i] == _snakeY)
		{
			_exitGame = true;
			GameOver();
		}
	}
}

int food()
{
	_foodX = rand() % _boardX - 1;
	_foodY = rand() % _boardY - 1;

	for (int i = 0; i <= _snake; i++)
		if (_foodX < _boardX && _foodY < _boardY && _foodX > 0 && _foodY > 0 && tailX[i] != _foodX && tailY[i] != _foodY)
		{
			checkFood = true;
		}
		else
			return food();
}

int GameOver()
{
	char again;
	if (_quitTheGame)
	{
		_exitGame = false;
		cout << "\nAre you shure??? y/n " << endl;
		cin >> again;
		if (again == 'y')
		{
			cout << "\nTRY AGAIN? y/n.\n";
			cin >> again;
			if (again == 'y')
			{
				restart();
				main();
			}
			else if (again == 'n')
				return 0;
		}
		else
		{
			/*_exitGame = false;*/
			_quitTheGame = false;
			main();
		}
	}
	
	if (_exitGame)
	{
		cout << "\nGAME OVER!!!\nYOUR SCORE: " << Score
			<< "\nTRY AGAIN? y/n or 'q' for quit the game\n";
		cin >> again;
		if (again == 'y')
		{
			restart();
			main();
		}
		else
			
			return 0;
	}
}
 
void restart()
{
	for (int i = 0; i <= _snake; i++)
	{
		tailX[i] = 0;
		tailY[i] = 0;
	}
	Score = 0;
	_sleepScale = 0;
	_snake = 0;
	_exitGame = true;
	system("cls");
}