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

void board_score(const vector< vector < int > > &target_board, const vector< vector < int > > current_board, const int numRows, const int numColumns, int &score){
    int target = 0; //! stores the variable to hunt for here
    int current = 0; //! stores the present value in the curren_board here
    int seekRow = 0; //! searching through the 'current' board
    int seekColumn = 0; //! searching through the 'current' board
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

void board_map_score(map<int, tile> &mapCurrent, map<int, tile> &mapTarget, int &score){
    score = 0;
    for(int i = 0; i < mapTarget.size(); i++){
        //int temp = mapCurrent.find(2);
        //cout << mapCurrent.find(1)->second.row;
        
        
        //auto search = mapCurrent.find(2);
        auto search = mapCurrent.find(i); //! We currently can't skip around (not sure how to access key value), see following line
        //auto search = mapCurrent.find(mapTarget.at(i)); // how to do this?
        //tile test = mapCurrent.find(1);
        score += abs(mapTarget[i].row - mapCurrent[search->first].row) + abs(mapTarget[i].column - mapCurrent[search->first].column);
        //score += ((mapTarget[i].row - mapCurrent[search->first].row) * (mapTarget[i].row - mapCurrent[search->first].row) + (mapTarget[i].column - mapTarget[search->first].column) * (mapTarget[i].column - mapTarget[search->first].column));
        /*
        cout << "Search value: " << search->first << endl;
        cout << "Item row number: " << mapCurrent[search->first].row << endl;
        cout << "Target row number: " << mapTarget[search->first].row << endl;
        cout << "Item column number: " << mapCurrent[search->first].column << endl;
        cout << "Target column number: " << mapTarget[search->first].column << endl;
        cout << (abs(mapTarget[i].row - mapCurrent[search->first].row) + abs(mapTarget[i].column - mapCurrent[search->first].column)) << endl;
        */
        
        //score += abs(mapTarget[i].row - mapCurrent[search].row) + abs(mapTarget[i].column - mapTarget[search].column);
        //score += abs(mapTarget[i].row - mapCurrent[search->first].row);
    }
    cout << score << endl;
}
