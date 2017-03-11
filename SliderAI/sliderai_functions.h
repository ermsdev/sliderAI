//
//  sliderai_functions.h
//  SliderAI
//
//  Created by Aaron Covrig on 2/24/17.
//  Copyright © 2017 Stephen. All rights reserved.
//

// NOT USING THIS FILE, currently only to reference old functions

#ifndef sliderai_functions_h
#define sliderai_functions_h


#include <vector>
#include <iostream>


using namespace std;

struct tile {
    int row;
    int column;
    
    tile(int r, int c);
};

//! Scores the target_board using the Manhattan distance in relation to the current_board
int board_score(const vector< vector < int > > &target_board, const vector< vector < int > > current_board, const int &numRows, const int &numColumns);

//! Finds a specific target value and returns a tile structure (foundTile) containing the row and column of the element
void targetSearch(const int &targetValue, const vector<vector <int > > &searchBoard, const int &num_rows, const int &num_columns, tile &foundTile);

//! \brief Creates several children (see spawnChild) and selects the best one (using the Manhattan distance, see board_score) and returns it
//
// The matrix layout is as follows:
//  ROW 1       C C C
//  ROW 2       O O O
//  ROW 3       L L L
//              U U U
//              M M M
//              N N N
//              1 2 3
//
void childMutate(const vector< vector < int > > &target_board, const vector< vector < int > > current_board, const int &numRows, const int &numColumns, vector< vector < int > > &bestChild, tile &BlankTile);

//! Creates a child board where the blankTile and the swapTile are switched in the new child
//
// Takes the new blank location in swapTile and the current blank location in blankTile
// and then switches them in the child_board
void spawnChild(const vector< vector < int > > &Parent_board, vector< vector < int > > &child_board, tile blankTile, tile swapTile);

//! displays the board arrangement on the console
void printBoard(const vector< vector <int> > &theBoard, const int &num_rows, const int &num_columns);

bool isSolvable(const vector<vector <int > > &search_board, const vector <vector <int> > &target_board, const int &numRows, const int &numColumns, tile blankTile);

#endif /* sliderai_functions_h */
