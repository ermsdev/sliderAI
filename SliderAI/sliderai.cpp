//
//  sliderai.cpp
//  SliderAI.exe
//
//  Created by Aaron Covrig on 3/12/17.
//  Copyright © 2017 Stephen. All rights reserved.
//

#include <iostream>

#include "sliderai.hpp"

bool isSolvable(const board startingBoard){
    bool isSolvable = false;
    vector<vector<int>> search_board = startingBoard.getLayout();
    int target = 0;
    int present = 0;
    long numRows = startingBoard.getSize();
    long numColumns = numRows; //! This currently limits us to n*n, probably have other areas that do the same
    int inversion_count = 0;
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numColumns; j++){
            target = startingBoard.goal[i][j];
            if(target != 0){    //! skipping the blank tile
                for(int y = 0; present != target; y++){
                    if(y == numRows){
                        break;
                    }
                    for(int z = 0; present != target; z++){
                        if(z == numColumns){
                            break;
                        }
                        present = search_board[y][z];
                        //cout << "Target: " << target << endl;
                        //cout << "Present: " << present << endl;
                        //cout << "Inversion count: " << inversion_count << endl;
                        if(present > target){
                            inversion_count++;
                        }
                    }
                }
            }
        }
    }
    
    if(numRows != numColumns){
        cout << "This version of the solver only supports square boards at this time" << endl;
    }
    else if(((numColumns % 2) != 0) && ((inversion_count % 2) == 0)){ //! Checking if the board is odd and number of inversions is even
        isSolvable = true;
    }
    else if((numRows % 2) == 0){    //! Checking if board is divisible by 2 (even)
        if(((startingBoard.getBlankRow() + 2) % 2 == 0) && (inversion_count % 2 != 0)){ //! Checking if on even row and number of inversions is odd
            isSolvable = true;
        }
        else if(((startingBoard.getBlankRow() + 2) % 2 == 1) && (inversion_count % 2 == 0)){
            isSolvable = true;
            cout << "2" << endl;
        }
        else{
            isSolvable = false;
        }
    }
    else{   //! Some check to see if something strange happened when determining if board is even or odd
        cout << "Something weird happened when determining board dimensions..." << endl;
    }
    //cout << "This board is: " << isSolvable << endl;
    //cout << "Inversion count: " << inversion_count << endl;
    return(isSolvable);
}
