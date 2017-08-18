#include "functionality.h"

/*
 * Function tileCount()
 * Description: the function that counts the mines around a tile
 * 
 * Input:
 * 
 * vector< vector<Tile> > &Board: 2D vector of Minesweeper playing area
 * int row: integer that refers to the row of the playing area that will be accessed
 * int col: integer that refers to the column of the playing area that will be accessed
 *
 * The function does not return anything, since changes are done in the Tile struct.
 */

void tileCount(vector< vector<Tile> > &Board, int row, int col)
{
	int i, j;
	int mineAround = 0;
	for (i = row - 1; i <= row + 1; i++)
	{
		for (j = col - 1; j <= col + 1; j++)
		{
			if ((i >= 0 && i < ROW_SIZE) && (j >= 0 && j < COL_SIZE))
			//checking whether i and j is in the Board vector
			{
				if (Board[i][j].isMine == true)
				{
					mineAround += 1;//counting the mines
				}
			}
		}
	}
	Board[row][col].mineAround = mineAround;//modifying the mineAround property of the struct
};

/*
 * Function BoardPrinting()
 * Description: Functions that prints the playing area in a specified way
 * The function also prints the amount of mines left unmarked
 *
 * Input:
 * 
 * vector< vector<Tile> > &Board: 2D vector of Minesweeper playing area
 * int &mineLeft: int that stores the amount of mines left unmarked by player
 *
 * The function does not return anything, since changes are done on the stdout
 */

void BoardPrinting(vector< vector<Tile> > &Board, int &mineLeft)
{
	std::system("cls");//clearing the screen first
	//printing first line, and how many mines left
	cout << "Welcome to Minesweeper\n" << endl;
	cout << "There are "<<mineLeft<<" mines left\n" << endl;
	for (int a = 0; a < COL_SIZE; a++)
	{
		cout << "    " << a;//printing column count
	}
	cout << endl;
	for (int i = 0; i < ROW_SIZE; i++)
	{
		cout << i << "  ";//print the row number
		for (int j = 0; j < COL_SIZE; j++)
		{
			if (Board[i][j].isMarked)
			{
				cout << "[M]" << "  ";//print marked tile
			}
			else if (Board[i][j].isCovered)
			{
				cout << "[ ]" << "  ";//print covered tile
			}
			else
			{
				if (Board[i][j].isMine)
				{
					cout << "[*]" << "  ";//print uncovered, isMine tile
				}
				else
				{
					cout << "[" << Board[i][j].mineAround << "]" << "  ";//print uncovered, notMine tile
				}
			};
		};
		cout << endl;
	};
	cout << endl;
};

/*
 * Function uncover()
 * Description: The function to uncover the tile picked by player
 *
 * Additional functionality:
 * Uncovering tile with 0 mines around will uncover all other tiles with 0 mines around that tile.
 * Works like an actual Minesweeper game.
 *
 * Input:
 * vector< vector<Tile> > &Board: 2D vector of Minesweeper playing area
 * int row: integer that refers to the row of the playing area that will be accessed
 * int col: integer that refers to the column of the playing area that will be accessed
 * int &coveredTiles: integer that stores the quantity of tiles still covered
 * 
 * The function returns a string: statusMessage, that shows whether the player uncover a mine, or not.
 */

string uncover(vector< vector<Tile> > &Board, int row, int col, int &coveredTiles)
{
	string statusMessage = "not hit";
	if (Board[row][col].isMarked == true)
	{
		statusMessage = "Can't uncover marked tile";
	}
	else if (Board[row][col].mineAround == 0)
	{
		Board[row][col].isCovered = false;
		--coveredTiles;
		for (int i = row - 1; i < row + 2; i++)
		{
			for (int j = col - 1; j < col + 2; j++)
			{
				if ((i >= 0 && i < ROW_SIZE) && (j >= 0 && j < COL_SIZE))
				{
					if (!Board[i][j].isMine && Board[i][j].isCovered)
					{
						uncover(Board, i, j, coveredTiles);
					}
				}
			}
		}
	}
	else if (Board[row][col].isMine == true)
	{
		Board[row][col].isCovered = false;
		statusMessage = "hit";
		--coveredTiles;
	}
	else
	{
		Board[row][col].isCovered = false;
		--coveredTiles;
	};
	return statusMessage;
}

void mark(vector< vector<Tile> > &Board, int row, int col, int &mineLeft)
{
	if (Board[row][col].isMarked == false)
	{
		Board[row][col].isMarked = true;
		mineLeft--;
	}
	else
	{
		Board[row][col].isMarked = false;
		mineLeft++;
	};
}

void gameInput(string statusMessage, vector< vector<Tile> > &Board, int mineQty, int &mineLeft)
{
	char command;
	string commandText;
	int inputRow, inputCol;
	int coveredTiles = ROW_SIZE*COL_SIZE;
	while (statusMessage != "hit"&& coveredTiles > mineQty)
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
				commandText = "mark: ";
			}
			else if (command == 'U')
			{
				commandText = "uncover: ";
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
					statusMessage = uncover(Board, inputRow, inputCol, coveredTiles);
				}
				else if (command == 'M')
				{
					mark(Board, inputRow, inputCol, mineLeft);
				};
			};
		};
		BoardPrinting(Board, mineLeft);
	};
	endgameHandling(coveredTiles,statusMessage,mineQty);
}

/*
 * Function mineGen()
 * Description: The function that generates mines randomly
 * on the playing area with a certain quantity
 * 
 * Input:
 *
 * vector< vector<Tile> > &Board: 2D vector of Minesweeper playing area
 * int mineQty: the amount of mines to be generated on the playing area
 * 
 * The function does not return anything, since changes are done in the Tile struct.
 */

void mineGen(vector< vector<Tile> > &Board, int mineQty)
{
	int currentMineCount = 0;
	int rowGen, colGen;
	while (currentMineCount < mineQty)
	{
		rowGen = rand() % ROW_SIZE;//generates random number from range 0-(ROW_SIZE-1)
		colGen = rand() % COL_SIZE;//generates random number from range 0-(COL_SIZE-1)
		if (!Board[rowGen][colGen].isMine)
		{
			Board[rowGen][colGen].isMine = true;//setting isMine boolean on struct
			currentMineCount++;//incrementing mine count
		}
	};
}

/*
 * Function boardResize()
 * Description: The function that resizes the 2D vector size
 * of the playing field if the player wants it.
 *
 * Input:
 *
 * vector< vector<Tile> > &Board: 2D vector of Minesweeper playing area
 *
 * The function does not return anything, since changes are done in the vector.
 */

void BoardResize(vector<vector<Tile>>& Board)
{
	int row, col;
	cout << "Please enter the size of board.(row, col separated by space): ";
	cin >> row >> col;
	Board.resize(row); //resizes the row ot the vector
	for (int i = 0; i < row; i++)
	{
		Board[i].resize(col);//resizes each column of the vector
	}
}

/*
 * Function endgameHandling()
 * Description: The function that determines whether the player wins or loses
 * and prints the correct message to the player.
 *
 * Input:
 *
 * int &coveredTiles: integer that stores how many covered tiles are left
 * string statusMessage: string that stores current status of the game
 * int mineQty: integer that stores how many mines are being played
 *
 * The function returns nothing.
 * 
 */

void endgameHandling(int &coveredTiles, string statusMessage, int mineQty)
{
	if (coveredTiles == mineQty && statusMessage == "not hit")
	//win condition: the only covered tiles are the mine tiles, and none have been hit.
	{
		cout << "Game completed, you win." << endl;
	}
	else
	{
		//the case where a mine is hit.
		cout << "You hit a mine. Game over." << endl;
	}
}

/*
 * Function mineNumber()
 * Description: The function that changes the quantity of mines played.
 * The function will first do a checking on the validity of the number.
 *
 * Input:
 *
 * int rowsize: integer that stores the row size of the vector
 * int colsize: integer that stores the column size of the vector
 *
 * The function returns nothing.
 */

int mineNumber(int rowsize, int colsize)
{
	bool numberValidity = false;
	int mineQty;
	while (!numberValidity)
	{
		cout << "Please enter the amount of mine. ";
		cin >> mineQty;
		if (mineQty <= 0)
		{
			cout << "Mine can't be zero or less" << endl;
		}
		else if (mineQty >= rowsize*colsize)
		{
			cout << "Mine quantity can't be more than number of tiles in the board" << endl;
		}
		else
		{
			numberValidity = true;
		}
	};
	return mineQty;
}
