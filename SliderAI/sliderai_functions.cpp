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
//#include <cmath>
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

void targetSearch(const int &targetValue, const vector<vector <int > > &searchBoard, const int &num_rows, const int &num_columns, tile &blankTile){
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < num_columns; j++){
            if(searchBoard[i][j] == targetValue){
                blankTile.row = i;
                blankTile.column = j;
                return;
            }
        }
    }
}

//! \brief This function is used to mutate and select the best child
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
void childMutate(const vector< vector < int > > &target_board, const vector< vector < int > > current_board, const int &numRows, const int &numColumns, vector< vector < int > > &bestChild, tile &blankTile){
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
            /*
            cout << "scoreRight = " << scoreRIGHT << endl;
            cout << "scoreDown = " << scoreDOWN << endl;
            */
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
            /*
            cout << "scoreRight = " << scoreRIGHT << endl;
            cout << "scoreUP = " << scoreUP << endl;
            */
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
            /*
            cout << "scoreRight = " << scoreRIGHT << endl;
            cout << "scoreUp = " << scoreUP << endl;
            cout << "scoreDown = " << scoreDOWN << endl;
            */
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
            /*
            cout << "scoreLeft = " << scoreLEFT << endl;
            cout << "scoreDown = " << scoreDOWN << endl;
            */
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
            /*
            cout << "scoreLeft = " << scoreLEFT << endl;
            cout << "scoreUp = " << scoreUP << endl;
            */
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
            /*
            cout << "scoreLeft = " << scoreLEFT << endl;
            cout << "scoreUp = " << scoreUP << endl;
            cout << "scoreDown = " << scoreDOWN << endl;
            */
            /*
            cout << "Left: " << endl;
            printBoard(childLEFT, numRows, numColumns);
            cout << "UP: " << endl;
            printBoard(childUP, numRows, numColumns);
            cout << "Down: " << endl;
            printBoard(childDOWN, numRows, numColumns);
            cout << endl;
            */
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
        /*
        cout << "scoreLeft = " << scoreLEFT << endl;
        cout << "scoreRight = " << scoreRIGHT << endl;
        cout << "scoreDown = " << scoreDOWN << endl;
        */
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
        /*
        cout << "scoreLeft = " << scoreLEFT << endl;
        cout << "scoreUp = " << scoreUP << endl;
        cout << "scoreRight = " << scoreRIGHT << endl;
        */
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
        /*
        cout << "scoreLeft = " << scoreLEFT << endl;
        cout << "scoreRight = " << scoreRIGHT << endl;
        cout << "scoreUp = " << scoreUP << endl;
        cout << "scoreDown = " << scoreDOWN << endl;
        */
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

//! \brief Passes parent and child matrixes by reference
//
// Takes the new blank location in swapTile and the current blank location in blankTile
// and then switches them in the child_board
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
