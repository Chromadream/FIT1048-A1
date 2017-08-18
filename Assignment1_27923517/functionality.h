#pragma once

#include <iostream>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>   
#include <string>
#include <vector>
using namespace std;


//Tile struct definition
struct Tile
{
	bool isCovered = true;
	bool isMarked = false;
	bool isMine = false;
	int mineAround = 0;
};


//function prototype definition
void tileCount(vector< vector<Tile> > &Board, int row, int col);
void BoardPrinting(vector< vector<Tile> > &Board, int &mineLeft);
string uncover(vector< vector<Tile> > &Board, int row, int col, int &coveredTiles);
void mark(vector< vector<Tile> > &Board, int row, int col, int &mineLeft);
void gameInput(string statusMessage, vector< vector<Tile> > &Board, int mineQty, int &mineLeft);
void mineGen(vector< vector<Tile> > &Board, int mineQty);
void BoardResize(vector< vector<Tile> > &Board);
int mineNumber(int rowsize, int colsize);
void endgameHandling(int &uncoveredTiles, string statusMessage, int mineQty);

//Global variable definition
extern int ROW_SIZE;
extern int COL_SIZE;



