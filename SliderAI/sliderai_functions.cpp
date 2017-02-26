//
//  sliderai_functions.cpp
//  SliderAI
//
//  Created by Aaron Covrig on 2/24/17.
//  Copyright © 2017 Stephen. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "sliderai_functions.h"

using namespace std;

void board_score(const vector< vector < int > > &target_board, const vector< vector < int > > current_board, const int numRows, const int numColumns, int &score){
    int target = 0; // stores the variable to hunt for here
    int current = 0; // stores the present value in the curren_board here
    int seekRow = 0; // searching through the 'current' board
    int seekColumn = 0; // ^
    score = 0; // Stores the total 'score' here
    for(int row = 0; row < numRows; row++){
        for(int column = 0; column < numColumns; column++){
            target = target_board[row][column];
            cout << "Current target: " << target << endl;
            for(seekRow = 0; seekRow < numRows; seekRow++){
                for(seekColumn = 0; seekColumn < numColumns; seekColumn++){
                    if(current_board[seekRow][seekColumn] == target){
                        current = current_board[seekRow][seekColumn];
                        score += abs(row - seekRow) + abs(column - seekColumn);
                    }
                }
            }
        }
    }
    cout << "Total score: " << score << endl;
}
