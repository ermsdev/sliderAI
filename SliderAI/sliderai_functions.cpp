//
//  sliderai_functions.cpp
//  SliderAI
//
//  Created by Aaron Covrig on 2/24/17.
//  Copyright © 2017 Stephen. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <map>
#include "sliderai_functions.h"


using namespace std;


tile::tile(int r, int c){
    row = r;
    column = c;
}

int board_score(const vector< vector < int > > &target_board, const vector< vector < int > > current_board, const int &numRows, const int &numColumns){
    int target = 0; // stores the variable to hunt for here
    int current = 0; // stores the present value in the curren_board here
    int seekRow = 0; // searching through the 'current' board
    int seekColumn = 0; // ^
    int score = 0; // Stores the total 'score' here
    for(int row = 0; row < numRows; row++){
        for(int column = 0; column < numColumns; column++){
            target = target_board[row][column];
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
    //cout << "Total score: " << score << endl;
    return(score);
}

void targetSearch(const int &targetValue, const vector<vector <int > > &searchBoard, const int &num_rows, const int &num_columns, tile &foundTile){
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < num_columns; j++){
            if(searchBoard[i][j] == targetValue){
                foundTile.row = i;
                foundTile.column = j;
                return;
            }
        }
    }
}

void childMutate(const vector< vector < int > > &target_board, const vector< vector < int > > current_board, const int &numRows, const int &numColumns, vector< vector < int > > &bestChild, tile &blankTile){
    // running through tile arrangements and identifying where the possible tile shifts are
    // (checking to see if at the edge of a board)
    if(blankTile.column == 0){
        if(blankTile.row == 0){ //! Spawn 2 children, right and down
            vector< vector < int > > childRIGHT;
            tile swapRIGHT = blankTile;
            swapRIGHT.column = blankTile.column + 1;
            spawnChild(current_board, childRIGHT, blankTile, swapRIGHT);
            
            vector< vector < int > > childDOWN;
            tile swapDOWN = blankTile;
            swapDOWN.row = blankTile.row + 1;
            spawnChild(current_board, childDOWN, blankTile, swapDOWN);
            
            int scoreRIGHT = board_score(target_board, childRIGHT, numRows, numColumns);
            int scoreDOWN = board_score(target_board, childDOWN, numRows, numColumns);

            if(scoreRIGHT < scoreDOWN){
                bestChild = childRIGHT;
                blankTile = swapRIGHT;
                return;
            }
            else if(scoreRIGHT > scoreDOWN){
                bestChild = childDOWN;
                blankTile = swapDOWN;
                return;
            }
            else{
                cout << "Error: failed to identify best child" << endl;
            }
        }
        else if(blankTile.row == (numRows -1)){ //! Spawn 2 children; right and up
            vector< vector < int > > childRIGHT;
            tile swapRIGHT = blankTile;
            swapRIGHT.column = blankTile.column + 1;
            spawnChild(current_board, childRIGHT, blankTile, swapRIGHT);
            
            vector< vector < int > > childUP;
            tile swapUP = blankTile;
            swapUP.row = blankTile.row - 1;
            spawnChild(current_board, childUP, blankTile, swapUP);
            
            int scoreRIGHT = board_score(target_board, childRIGHT, numRows, numColumns);
            int scoreUP = board_score(target_board, childUP, numRows, numColumns);

            if(scoreRIGHT < scoreUP){
                bestChild = childRIGHT;
                blankTile = swapRIGHT;
                return;
            }
            else if(scoreRIGHT > scoreUP){
                bestChild = childUP;
                blankTile = swapUP;
                return;
            }
            else{
                cout << "Error: failed to identify best child" << endl;
            }
        }
        else{ //! Spawn 3 children, right, up, and down
            vector< vector < int > > childRIGHT;
            tile swapRIGHT = blankTile;
            swapRIGHT.column = blankTile.column + 1;
            spawnChild(current_board, childRIGHT, blankTile, swapRIGHT);
            
            vector< vector < int > > childUP;
            tile swapUP = blankTile;
            swapUP.row = blankTile.row - 1;
            spawnChild(current_board, childUP, blankTile, swapUP);
            
            vector< vector < int > > childDOWN;
            tile swapDOWN = blankTile;
            swapDOWN.row = blankTile.row + 1;
            spawnChild(current_board, childDOWN, blankTile, swapDOWN);
            
            int scoreRIGHT = board_score(target_board, childRIGHT, numRows, numColumns);
            int scoreUP = board_score(target_board, childUP, numRows, numColumns);
            int scoreDOWN = board_score(target_board, childDOWN, numRows, numColumns);

            if((scoreRIGHT < scoreUP) && (scoreRIGHT < scoreDOWN)){
                bestChild = childRIGHT;
                blankTile = swapRIGHT;
                return;
            }
            else if((scoreUP < scoreRIGHT) && (scoreUP < scoreDOWN)){
                bestChild = childUP;
                blankTile = swapUP;
                return;
            }
            else if((scoreDOWN < scoreRIGHT) && (scoreDOWN < scoreUP)){
                bestChild = childDOWN;
                blankTile = swapDOWN;
                return;
            }
            else{
                cout << "Error: failed to identify best child" << endl;
            }
        }
    }
    else if(blankTile.column == (numColumns - 1)){
        if(blankTile.row == 0){ //! Spawn 2 children; left and down
            vector< vector < int > > childLEFT;
            tile swapLEFT = blankTile;
            swapLEFT.column = blankTile.column - 1;
            spawnChild(current_board, childLEFT, blankTile, swapLEFT);
            
            vector< vector < int > > childDOWN;
            tile swapDOWN = blankTile;
            swapDOWN.row = blankTile.row + 1;
            spawnChild(current_board, childDOWN, blankTile, swapDOWN);
            
            int scoreLEFT = board_score(target_board, childLEFT, numRows, numColumns);
            int scoreDOWN = board_score(target_board, childDOWN, numRows, numColumns);

            if(scoreLEFT < scoreDOWN){
                bestChild = childLEFT;
                blankTile = swapLEFT;
                return;
            }
            else if(scoreLEFT > scoreDOWN){
                bestChild = childDOWN;
                blankTile = swapDOWN;
                return;
            }
            else{
                cout << "Error: failed to identify best child" << endl;
            }
        }
        else if(blankTile.row == (numRows -1)){ //! Spawn 2 children; left and up
            vector< vector < int > > childLEFT;
            tile swapLEFT = blankTile;
            swapLEFT.column = blankTile.column - 1;
            spawnChild(current_board, childLEFT, blankTile, swapLEFT);
            
            vector< vector < int > > childUP;
            tile swapUP = blankTile;
            swapUP.row = blankTile.row - 1;
            spawnChild(current_board, childUP, blankTile, swapUP);
            
            int scoreLEFT = board_score(target_board, childLEFT, numRows, numColumns);
            int scoreUP = board_score(target_board, childUP, numRows, numColumns);

            if(scoreLEFT < scoreUP){
                bestChild = childLEFT;
                blankTile = swapLEFT;
                return;
            }
            else if(scoreLEFT > scoreUP){
                bestChild = childUP;
                blankTile = swapUP;
                return;
            }
            else{
                cout << "Error: failed to identify best child" << endl;
            }
        }
        else{ //! Spawn 3 children; left, up, and down
            vector< vector < int > > childLEFT;
            tile swapLEFT = blankTile;
            swapLEFT.column = blankTile.column - 1;
            spawnChild(current_board, childLEFT, blankTile, swapLEFT);
            
            vector< vector < int > > childUP;
            tile swapUP = blankTile;
            swapUP.row = blankTile.row - 1;
            spawnChild(current_board, childUP, blankTile, swapUP);
            
            vector< vector < int > > childDOWN;
            tile swapDOWN = blankTile;
            swapDOWN.row = blankTile.row + 1;
            spawnChild(current_board, childDOWN, blankTile, swapDOWN);
            
            int scoreLEFT = board_score(target_board, childLEFT, numRows, numColumns);
            int scoreUP = board_score(target_board, childUP, numRows, numColumns);
            int scoreDOWN = board_score(target_board, childDOWN, numRows, numColumns);

            if((scoreLEFT < scoreUP) && (scoreLEFT < scoreDOWN)){
                bestChild = childLEFT;
                blankTile = swapLEFT;
                return;
            }
            else if((scoreUP < scoreLEFT) && (scoreUP < scoreDOWN)){
                bestChild = childUP;
                blankTile = swapUP;
                return;
            }
            else if((scoreDOWN < scoreLEFT) && (scoreDOWN < scoreUP)){
                bestChild = childDOWN;
                blankTile = swapDOWN;
                return;
            }
            else{
                cout << "Error: failed to identify best child" << endl;
            }
        }
    }
    else if((blankTile.column != 0) && (blankTile.column != numColumns - 1) && (blankTile.row == 0)){ //! spawn 3 children; left, right, down
        vector< vector < int > > childLEFT;
        tile swapLEFT = blankTile;
        swapLEFT.column = blankTile.column - 1;
        spawnChild(current_board, childLEFT, blankTile, swapLEFT);
        
        vector< vector < int > > childRIGHT;
        tile swapRIGHT = blankTile;
        swapRIGHT.column = blankTile.column + 1;
        spawnChild(current_board, childRIGHT, blankTile, swapRIGHT);
        
        vector< vector < int > > childDOWN;
        tile swapDOWN = blankTile;
        swapDOWN.row = blankTile.row + 1;
        spawnChild(current_board, childDOWN, blankTile, swapDOWN);
        
        int scoreLEFT = board_score(target_board, childLEFT, numRows, numColumns);
        int scoreRIGHT = board_score(target_board, childRIGHT, numRows, numColumns);
        int scoreDOWN = board_score(target_board, childDOWN, numRows, numColumns);
        
        if((scoreLEFT < scoreRIGHT) && (scoreLEFT < scoreDOWN)){
            bestChild = childLEFT;
            blankTile = swapLEFT;
            return;
        }
        else if((scoreRIGHT < scoreLEFT) && (scoreRIGHT < scoreDOWN)){
            bestChild = childRIGHT;
            blankTile = swapRIGHT;
            return;
        }
        else if((scoreDOWN < scoreLEFT) && (scoreDOWN < scoreRIGHT)){
            bestChild = childDOWN;
            blankTile = swapDOWN;
            return;
        }
        else{
            cout << "Error: failed to identify best child" << endl;
        }
    }
    else if((blankTile.column != 0) && (blankTile.column != numColumns - 1) && (blankTile.row == numRows - 1)){ //! spawn 3 children; left, right, up
        vector< vector < int > > childLEFT;
        tile swapLEFT = blankTile;
        swapLEFT.column = blankTile.column - 1;
        spawnChild(current_board, childLEFT, blankTile, swapLEFT);
        
        vector< vector < int > > childUP;
        tile swapUP = blankTile;
        swapUP.row = blankTile.row - 1;
        spawnChild(current_board, childUP, blankTile, swapUP);
        
        vector< vector < int > > childRIGHT;
        tile swapRIGHT = blankTile;
        swapRIGHT.column = blankTile.column + 1;
        spawnChild(current_board, childRIGHT, blankTile, swapRIGHT);
        
        int scoreLEFT = board_score(target_board, childLEFT, numRows, numColumns);
        int scoreUP = board_score(target_board, childUP, numRows, numColumns);
        int scoreRIGHT = board_score(target_board, childRIGHT, numRows, numColumns);

        if((scoreLEFT < scoreUP) && (scoreLEFT < scoreRIGHT)){
            bestChild = childLEFT;
            blankTile = swapLEFT;
            return;
        }
        else if((scoreUP < scoreLEFT) && (scoreUP < scoreRIGHT)){
            bestChild = childUP;
            blankTile = swapUP;
            return;
        }
        else if((scoreRIGHT < scoreLEFT) && (scoreRIGHT < scoreUP)){
            bestChild = childRIGHT;
            blankTile = swapRIGHT;
            return;
        }
        else{
            cout << "Error: failed to identify best child" << endl;
        }
    }
    else{ //! Spawn 4 children; left, right, up, and down
        vector< vector < int > > childRIGHT;
        tile swapRIGHT = blankTile;
        swapRIGHT.column = blankTile.column + 1;
        spawnChild(current_board, childRIGHT, blankTile, swapRIGHT);
        
        vector< vector < int > > childLEFT;
        tile swapLEFT = blankTile;
        swapLEFT.column = blankTile.column - 1;
        spawnChild(current_board, childLEFT, blankTile, swapLEFT);
        
        vector< vector < int > > childUP;
        tile swapUP = blankTile;
        swapUP.row = blankTile.row - 1;
        spawnChild(current_board, childUP, blankTile, swapUP);
        
        vector< vector < int > > childDOWN;
        tile swapDOWN = blankTile;
        swapDOWN.row = blankTile.row + 1;
        spawnChild(current_board, childDOWN, blankTile, swapDOWN);
        
        int scoreLEFT = board_score(target_board, childLEFT, numRows, numColumns);
        int scoreRIGHT = board_score(target_board, childRIGHT, numRows, numColumns);
        int scoreUP = board_score(target_board, childUP, numRows, numColumns);
        int scoreDOWN = board_score(target_board, childDOWN, numRows, numColumns);

        if((scoreRIGHT < scoreLEFT) && (scoreRIGHT < scoreUP) && (scoreRIGHT < scoreDOWN)){
            bestChild = childRIGHT;
            blankTile = swapRIGHT;
            return;
        }
        else if((scoreLEFT < scoreRIGHT) && (scoreLEFT < scoreUP) && (scoreLEFT < scoreDOWN)){
            bestChild = childLEFT;
            blankTile = swapLEFT;
            return;
        }
        else if((scoreUP < scoreRIGHT) && (scoreUP < scoreLEFT) && (scoreUP < scoreDOWN)){
            bestChild = childUP;
            blankTile = swapUP;
            return;
        }
        else if((scoreDOWN < scoreRIGHT) && (scoreDOWN < scoreLEFT) && (scoreDOWN < scoreUP)){
            bestChild = childDOWN;
            blankTile = swapDOWN;
            return;
        }
        else{
            cout << "Error: failed to identify best child" << endl;
        }
    }
    bestChild = current_board;
    return;
}

void spawnChild(const vector< vector < int > > &Parent_board, vector< vector < int > > &child_board, tile blankTile, tile swapTile){
    child_board = Parent_board;
    
    child_board[swapTile.row][swapTile.column] = Parent_board[blankTile.row][blankTile.column];
    child_board[blankTile.row][blankTile.column] = Parent_board[swapTile.row][swapTile.column];
    
}

void printBoard(const vector< vector <int> > &theBoard, const int &num_rows, const int &num_columns){
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < num_columns; j++){
            cout << theBoard[i][j] << ",";
        }
        cout << endl;
    }
}

bool boardSolvable(const vector<vector <int > > &search_board, const vector <vector <int> > &target_board, const int &numRows, const int &numColumns, tile blankTile){
    bool isSolvable = false;
    int target = 0;
    int present = 0;
    int inversion_count = 0;
    for(int i = 0; i < numColumns; i++){
        for(int j = 0; j < numRows; j++){
            target = target_board[j][i];
            if(target != 0){    //! skipping the blank tile
                while(present != target){   //! checking to see if we reached the target value
                    for(int y = 0; y < numColumns; y++){
                        for(int z = 0; z < numRows; z++){
                            present = search_board[z][y];
                            if(present > target){
                                inversion_count++;
                            }
                        }
                    }
                }
            }
        }
    }
    if(numRows != numColumns){
        cout << "This version of the solver only supports square boards at this time" << endl;
    }
    else if((numColumns % 2) == 1){ //! Checking if the board is odd
        isSolvable = true;
    }
    else if((numRows % 2) == 0){    //! Checking if board is divisible by 2 (even)
        if((inversion_count % 2) == 0){ //! Checking if even number of inversions
            if((blankTile.row % 2 == 0) && (inversion_count % 2 == 1)){
                isSolvable = true;
            }
        }
        else if((blankTile.row % 2 == 1) && (inversion_count % 2 == 1)){
            
        }
    }
    else{   //! Some check to see if something strange happened when determining if board is even or odd
        cout << "Something weird happened when determining board dimensions..." << endl;
    }
    return(isSolvable);
}
