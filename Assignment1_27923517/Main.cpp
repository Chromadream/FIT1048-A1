#include "functionality.h"

int main(void)
{
	int ROW = 10;
	int COL = 10;
	int mineQty = 10;
	char initOption = 'n';
	string statusMessage ="not hit";
	vector<vector<Tile>> Board(ROW, vector<Tile>(COL, Tile()));
	cout << "Welcome to Minesweeper\n" << endl;
	cout << "Do you want to change the board size? (Default= 10x10) (Y/N)";
	cin >> initOption;
	if (initOption == 'Y' || initOption == 'y')
	{
		BoardResize(Board);
		ROW = Board.size();
		COL = Board[0].size();
	};
	cout << "Do you want to change the mine quantity? (Default = 10) (Y/N)";
	cin >> initOption;
	if (initOption == 'Y' || initOption == 'y')
	{
		cout << "Please enter the amount of mine. ";
		cin >> mineQty;
	};
	srand(time(NULL));
	mineGen(Board, mineQty);//mine generation
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			tileCount(Board, i, j);//counting the mines around the tile
		}
	};
	BoardPrinting(Board);//printing the board for the first time
	gameInput(statusMessage, Board, mineQty);
	std::system("pause");
	return 0;
};
