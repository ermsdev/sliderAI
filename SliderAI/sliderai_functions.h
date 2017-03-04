//
//  sliderai_functions.h
//  SliderAI
//
//  Created by Aaron Covrig on 2/24/17.
//  Copyright © 2017 Stephen. All rights reserved.
//

#ifndef sliderai_functions_h
#define sliderai_functions_h


#include <vector>
#include <iostream>
#include "sliderai.h"

using namespace std;

struct tile {
    int row;
    int column;
    
    tile(int r, int c);
};

//void board_score(vector< vector < int > > &target_board, vector< vector < int > > current_board, int numRows, int numColumns, int &score);
int board_score(const vector< vector < int > > &target_board, const vector< vector < int > > current_board, const int &numRows, const int &numColumns);

void childMutate(const vector< vector < int > > &target_board, const vector< vector < int > > current_board, const int &numRows, const int &numColumns, vector< vector < int > > &bestChild, tile &BlankTile);

void spawnChild(const vector< vector < int > > &Parent_board, vector< vector < int > > &child_board, tile blankTile, tile swapTile);

void printBoard(const vector< vector <int> > &theBoard, const int &num_rows, const int &num_columns);

#endif /* sliderai_functions_h */
