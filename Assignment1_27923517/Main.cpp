#include <iostream>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>   
#include <string>
#include <vector>


using namespace std;
struct Tile;
void tileCount(vector< vector<Tile> > &Board, int row, int col);
void Printing(vector< vector<Tile> > &Board);
string uncover(vector< vector<Tile> > &Board, int row, int col);
void mark(vector< vector<Tile> > &Board, int row, int col);
void input(string statusMessage, vector< vector<Tile> > &Board);
void mineGen(vector< vector<Tile> > &Board, int mineQty);
void BoardInit(vector< vector<Tile> > &Board, int rowsize, int colsize);


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
	vector<vector<Tile>> Board(COL, vector<Tile>(COL, Tile()));
	//BoardInit(Board, ROW, COL);
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
	input(statusMessage, Board);
	std::system("pause");
	return 0;
};

void tileCount(vector< vector<Tile> > &Board, int row, int col)
{
	int const ROW_SIZE = Board.size();
	int const COL_SIZE = Board[0].size();
	int i, j, mineAround = 0;
	for (i = row - 1; i <= row + 1; i++)
	{
		for (j = col - 1; j <= col + 1; j++)
		{
			if ((i >= 0 || i < ROW_SIZE) && (j >= 0 || j < COL_SIZE) && Board[i][j].isMine == true)
			{
				mineAround += 1;
			}
		}
	}
	Board[row][col].mineAround = mineAround;
};

void Printing(vector< vector<Tile> > &Board)
{
	int const ROW_SIZE = Board.size();
	int const COL_SIZE = Board[0].size();
	cout << "Welcome to Minesweeper beta\n" << endl;
	for (int a = 0; a < ROW_SIZE; a++)
	{
		cout << "    " << a;
	}
	cout << endl;
	for (int i = 0; i < ROW_SIZE; i++)
	{
		cout << i << "  ";
		for (int j = 0; j < COL_SIZE; j++)
		{
			if (Board[i][j].isMarked)
			{
				cout << "[M]" << "  ";
			}
			else if (Board[i][j].isCovered)
			{
				cout << "[ ]" << "  ";
			}
			else
			{
				if (Board[i][j].isMine)
				{
					cout << "[*]" << "  ";
				}
				else
				{
					cout << "[" << Board[i][j].mineAround << "]" << "  ";
				}
			};
		};
		cout << endl;
	};
	cout << endl;
};

string uncover(vector< vector<Tile> > &Board, int row, int col)
{
	int const ROW_SIZE = Board.size();
	int const COL_SIZE = Board[0].size();
	string statusMessage = "not hit";
	if (Board[row][col].isMarked == true)
	{
		statusMessage = "Can't uncover marked tile";
	}
	else if (Board[row][col].mineAround == 0)
	{
		Board[row][col].isCovered = false;
		for (int i = row - 1; i < row + 2; i++)
		{
			for (int j = col - 1; j < col + 2; j++)
			{
				if ((i >= 0 || i < ROW_SIZE) && (j >= 0 || j < COL_SIZE) && !Board[i][j].isMine && Board[i][j].isCovered)
				{
					//Board[i][j].uncoverCheck = true;
					uncover(Board, i, j);
				}
			}
		}
	}
	else if (Board[row][col].isMine == true)
	{
		Board[row][col].isCovered = false;
		statusMessage = "hit";
	}
	else
	{
		Board[row][col].isCovered = false;
	};
	return statusMessage;
}

void mark(vector< vector<Tile> > &Board, int row, int col)
{
	if (Board[row][col].isMarked == false)
	{
		Board[row][col].isMarked = true;
	}
	else
	{
		Board[row][col].isMarked = false;
	};
}

void input(string statusMessage, vector< vector<Tile> > &Board)
{
	char command;
	string commandText;
	int inputRow, inputCol;
	int const ROW_SIZE = Board.size();
	int const COL_SIZE = Board[0].size();
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
			if ((inputRow < 0 || inputRow >= ROW_SIZE) || (inputCol < 0 || inputCol >= COL_SIZE))
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
		std::system("cls");
		Printing(Board);
	};
}

void mineGen(vector< vector<Tile> > &Board, int mineQty)
{
	int currentMineCount = 0;
	int rowGen, colGen;
	int rowSize = Board.size();
	int colSize = Board[0].size();
	while (currentMineCount < mineQty)
	{
		rowGen = rand() % rowSize;
		colGen = rand() % colSize;
		if (!Board[rowGen][colGen].isMine)
		{
			Board[rowGen][colGen].isMine = true;
			currentMineCount++;
		}
	};
}

void BoardInit(vector< vector<Tile> > &Board, int rowsize, int colsize)
{
	for (int i = 0; i < Board.size(); i++)
	{
		for (int j = 0; j < Board[i].size(); j++)
		{
			//Board[i][j]=new Tile();
		}
	}
};

