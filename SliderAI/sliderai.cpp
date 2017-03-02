//
//  sliderai.cpp
//  SliderAI
//

#include "sliderai.h"

tile::tile(){
    row = -9;
    column = -9;
}
//tile::tile(int v, int r, int c){
tile::tile(int r, int c){
    //ID = v;
    row = r;
    column = c;
}

//void board::getMap(map<int, map<int, int>> &mapOut){
//    mapOut = boardmap;
//}


/*
int* listMoves(){
    layout[]
}
*/

// Board Class Methods:
board::board(int a[], int size){
    for (int i=0; i<size; i++) {
        layout[a[i]] = tile((i/3)+1, (i+1)/3);
    }
}

int board::scoreBoard(){
    int score = 0;
    for(int i = 0; i < goal.size(); i++){
        //int temp = mapCurrent.find(2);
        //cout << mapCurrent.find(1)->second.row;
        
        
        //auto search = mapCurrent.find(2);
        auto search = layout.find(i); //! We currently can't skip around (not sure how to access key value), see following line
        //auto search = mapCurrent.find(mapTarget.at(i)); // how to do this?
        //tile test = mapCurrent.find(1);
        score += abs(goal[i].row - layout[search->first].row) + abs(goal[i].column - layout[search->first].column);
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
    return score;
}

void board::defineBoard(){
    //only to be used when making the first board
    
}

void board::reDefineGoal(){
    cout << "Use this map to enter your custom goal state: \n1 2 3\n4 5 6\n7 8 9\n";
    //http://www.geeksforgeeks.org/check-instance-15-puzzle-solvable/
    //contains instructions on checking solvability, along with some example code
    
}


// compareBoards class method
bool compareBoards::operator() (board b1, board b2){
    return b1.scoreBoard() < b2.scoreBoard();
}
