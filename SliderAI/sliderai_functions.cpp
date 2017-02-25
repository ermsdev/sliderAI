//
//  sliderai_functions.cpp
//  SliderAI
//
//  Created by Aaron Covrig on 2/24/17.
//  Copyright © 2017 Stephen. All rights reserved.
//

#include <stdio.h>
#include "sliderai_functions.h"

void board_score(vector< vector < int > > &target_board, vector< vector < int > > current_board, int numRows, int numColumns, int &score){
    int target = 0; // stores the variable to hunt for here
    int current = 0; // stores the present value in the curren_board here
    int seekRow = 0; // searching through the 'current' board
    int seekColumn = 0; // ^
    score = 0; // Stores the total 'score' here
    for(int row = 0; row < numRows; row++){
        for(int column = 0; column < numColumns; column++){
            target = target_board[row][column];
            
            while((current != target)){
                if((seekColumn == numColumns) && (seekRow == numRows)){
                    cout << "Error: reached end of input" << endl;
                }
                if(seekColumn < numColumns){
                    seekColumn++;
                }
                else{
                    seekColumn = 0;
                    seekRow++;
                }
                current = current_board[seekRow][seekColumn];
            }
            score += current_board[seekRow][seekColumn] * (abs((row - seekRow)) + abs((column - seekColumn)));
        }
    }
}
