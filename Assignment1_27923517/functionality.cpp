#include "functionality.h"

void tileCount(vector< vector<Tile> > &Board, int row, int col)
{
	int const ROW_SIZE = Board.size();
	int const COL_SIZE = Board[0].size();
	int i, j;
	int mineAround = 0;
	for (i = row - 1; i <= row + 1; i++)
	{
		for (j = col - 1; j <= col + 1; j++)
		{
			if ((i >= 0 && i < ROW_SIZE) && (j >= 0 && j < COL_SIZE))
			{
				if (Board[i][j].isMine == true)
				{
					mineAround += 1;
				}
			}
		}
	}
	Board[row][col].mineAround = mineAround;
};

void BoardPrinting(vector< vector<Tile> > &Board)
{
	int const ROW_SIZE = Board.size();
	int const COL_SIZE = Board[0].size();
	std::system("cls");
	cout << "Welcome to Minesweeper\n" << endl;
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

string uncover(vector< vector<Tile> > &Board, int row, int col, int &uncoveredTiles)
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
		uncoveredTiles--;
		for (int i = row - 1; i < row + 2; i++)
		{
			for (int j = col - 1; j < col + 2; j++)
			{
				if ((i >= 0 && i < ROW_SIZE) && (j >= 0 && j < COL_SIZE))
				{
					if (!Board[i][j].isMine && Board[i][j].isCovered)
					{
						uncover(Board, i, j, uncoveredTiles);
					}
				}
			}
		}
	}
	else if (Board[row][col].isMine == true)
	{
		Board[row][col].isCovered = false;
		statusMessage = "hit";
		uncoveredTiles--;
	}
	else
	{
		Board[row][col].isCovered = false;
		uncoveredTiles--;
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

void gameInput(string statusMessage, vector< vector<Tile> > &Board, int mineQty)
{
	char command;
	string commandText;
	int inputRow, inputCol;
	int const ROW_SIZE = Board.size();
	int const COL_SIZE = Board[0].size();
	int uncoveredTiles = ROW_SIZE*COL_SIZE;
	while (statusMessage != "hit"|| uncoveredTiles != mineQty)
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
					statusMessage = uncover(Board, inputRow, inputCol, uncoveredTiles);
				}
				else if (command == 'M')
				{
					mark(Board, inputRow, inputCol);
				};
			};
		};
		BoardPrinting(Board);
	};
	endgameHandling(uncoveredTiles,statusMessage,mineQty);
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

void BoardResize(vector<vector<Tile>>& Board)
{
	int row, col, mineQty = 10;
	cout << "Please enter the size of board.(row, col separated by space): ";
	cin >> row >> col;
	Board.resize(row);
	for (int i = 0; i < row; i++)
	{
		Board[i].resize(col);
	}
}

void endgameHandling(int &uncoveredTiles, string statusMessage, int mineQty)
{
	if (uncoveredTiles == mineQty || statusMessage == "not hit")
	{
		cout << "Game completed, you win." << endl;
	}
	else
	{
		cout << "You hit a mine. Game over." << endl;
	}
}
