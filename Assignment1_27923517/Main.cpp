#include <iostream>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>   
#include <string>
#include <vector>


using namespace std;
struct Tile;

void tileCount(vector< vector<Tile> > &matrix, int row, int col)
{
	int i,j, mineAround = 0;
	for (i = row - 1; i <= row + 1; i++)
	{
		for (j = col - 1; j <= col + 1; j++)
		{
			if ((i >= 0 || i < rows) && (j >= 0 || j < cols) && array[i][j].isMine == true)
			{
				mineAround += 1;
			}
		}
	}
	array[row][col].mineAround = mineAround;
};

void Printing(vector< vector<Tile> > &matrix)
{
	cout << "Welcome to Minesweeper beta\n" << endl;
	for (int a = 0; a < rows; a++)
	{
		cout << "    " << a;
	}
	cout << endl;
	for (int i = 0; i < rows; i++)
	{
		cout << i << "  ";
		for (int j = 0; j < cols; j++)
		{
			if (array[i][j].isMarked)
			{
				cout << "[M]" << "  ";
			}
			else if (array[i][j].isCovered)
			{
				cout << "[ ]" << "  ";
			}
			else 
			{
				if (array[i][j].isMine)
				{
					cout << "[*]" << "  ";
				}
				else
				{
					cout << "["<<array[i][j].mineAround<<"]" << "  ";
				}
			};
		};
		cout << endl;
	};
	cout << endl;
};

string uncover(vector< vector<Tile> > &matrix, int row, int col)
{
	string statusMessage = "not hit";
	if (array[row][col].isMarked == true)
	{
		statusMessage = "Can't uncover marked tile";
	}
	else if (array[row][col].mineAround == 0)
	{
		array[row][col].isCovered = false;
		for (int i = row - 1; i < row + 2; i++)
		{
			for (int j = col - 1; j < col + 2; j++)
			{
				if ((i >= 0 || i < rows) && (j >= 0 || j < cols) && !array[i][j].isMine && array[i][j].isCovered)
				{
					//array[i][j].uncoverCheck = true;
					uncover(array,i,j);
				}
			}
		}
	}
	else if (array[row][col].isMine == true)
	{
		array[row][col].isCovered = false;
		statusMessage = "hit";
	}
	else
	{
		array[row][col].isCovered = false;
	};
	return statusMessage;
}

void mark(vector< vector<Tile> > &matrix, int row, int col)
{
	if (array[row][col].isMarked == false)
	{
		array[row][col].isMarked = true;
	}
	else
	{
		array[row][col].isMarked = false;
	};
}


void input(string statusMessage, vector< vector<Tile> > &matrix, int rowsize, int colsize)
{
	char command;
	string commandText;
	int inputRow, inputCol;
	while (statusMessage != "hit")
	{
		if (statusMessage != "hit" && statusMessage != "not hit")
		{
			cout << statusMessage << endl << endl;
		}
		cout << "Please enter the desired command. (M)ark/unmark or (U)ncover: ";
		cin >> command;
		if (command != 'M' && command != 'U')
		{
			statusMessage = "Invalid command";
		}
		else
		{
			if (command == 'M')
			{
				commandText = "mark";
			}
			else if (command == 'U')
			{
				commandText = "uncover:";
			}
			cout << "Please enter the desired area you want to " << commandText << endl;
			cin >> inputRow >> inputCol;
			if ((inputRow < 0 || inputRow >= ARRAY_SIZE) || (inputCol < 0 || inputCol >= ARRAY_SIZE))
			{
				statusMessage = "Input outside of board size range.";
			}
			else
			{
				if (command == 'U')
				{
					statusMessage = uncover(Board, inputRow, inputCol);
				}
				else if (command == 'M')
				{
					mark(Board, inputRow, inputCol);
				};
			};
		};
		system("cls");
		Printing(Board);
	};
}

void mineGen(vector< vector<Tile> > &matrix, int mineQty)
{
	int currentMineCount = 0;
	int rowGen, colGen;
	while (currentMineCount < mineQty)
	{
		rowGen = rand() % mineQty;
		colGen = rand() % mineQty;
		if (!Board[rowGen][colGen].isMine)
		{
			Board[rowGen][colGen].isMine = true;
			currentMineCount++;
		}
	};
}

struct Tile
{
	bool isCovered = true;
	bool isMarked = false;
	bool isMine = false;
	int mineAround = 0;
};

int main(void)
{
	const int ROW = 10;
	const int COL = 10;
	int currentMine = 0, mineQty = 10;
	string statusMessage ="not hit";
	char command;
	string commandText;
	vector<vector<Tile>> Board(ROW, vector<Tile>(COL));
	srand(time(NULL));
	mineGen(Board, mineQty);//mine generation
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			tileCount(Board, i, j);//counting the mines around the tile
		}
	};
	Printing(Board);//printing the board for the first time
	input(statusMessage, Board, ROW, COL);
	system("pause");
	return 0;
};
