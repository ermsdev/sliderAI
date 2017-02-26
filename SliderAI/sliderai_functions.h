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

using namespace std;

//void board_score(vector< vector < int > > &target_board, vector< vector < int > > current_board, int numRows, int numColumns, int &score);
void board_score(const vector< vector < int > > &target_board, const vector< vector < int > > current_board, const int numRows, const int numColumns, int &score);


#endif /* sliderai_functions_h */
