#include "functionality.h"

/*
 * Main.cpp
 *
 * The file that contains the main workflow of the Minesweeper game
 *
 */


/*
 * global var for row and column size
 * as it is reused on many functions
 */
int ROW_SIZE, COL_SIZE;

int main(void)
{
	//initiating default row, column size, and mine quantity
	ROW_SIZE = 10; 
	COL_SIZE = 10;
	int mineQty = 20;
	char initOption = 'n';
	int mineLeft;
	string statusMessage ="not hit";
	vector<vector<Tile>> Board(ROW_SIZE, vector<Tile>(COL_SIZE, Tile()));
	//initial playing area configurations
	cout << "Welcome to Minesweeper\n" << endl;
	cout << "Do you want to change the board size? (Default= 10x10) (Y/N)  ";
	cin >> initOption;
	if (initOption == 'Y' || initOption == 'y')
	{
		BoardResize(Board);
		ROW_SIZE = Board.size();
		COL_SIZE = Board[0].size();
	};
	//initial playing difficulty configuration
	cout << "Do you want to change the mine quantity? (Default = 20) (Y/N)  ";
	cin >> initOption;
	if (initOption == 'Y' || initOption == 'y')
	{
		mineQty = mineNumber(ROW_SIZE, COL_SIZE);
	};
	mineLeft = mineQty;//setting unmarked mine quantity == mine quantity
	mineGen(Board, mineQty);//mine generation
	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COL_SIZE; j++)
		{
			tileCount(Board, i, j);//counting the mines around the tile
		}
	};
	BoardPrinting(Board, mineLeft);//printing the board for the first time
	gameInput(statusMessage, Board, mineQty, mineLeft);//initiating game input function
	std::system("pause");
	return 0;
};
