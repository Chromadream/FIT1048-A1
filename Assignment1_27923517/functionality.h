#pragma once

#include <iostream>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>   
#include <string>
#include <vector>


using namespace std;
struct Tile;
void tileCount(vector< vector<Tile> > &Board, int row, int col);
void BoardPrinting(vector< vector<Tile> > &Board);
string uncover(vector< vector<Tile> > &Board, int row, int col);
void mark(vector< vector<Tile> > &Board, int row, int col);
void gameInput(string statusMessage, vector< vector<Tile> > &Board);
void mineGen(vector< vector<Tile> > &Board, int mineQty);
void BoardResize(vector< vector<Tile> > &Board);


struct Tile
{
	bool isCovered = true;
	bool isMarked = false;
	bool isMine = false;
	int mineAround = 0;
};