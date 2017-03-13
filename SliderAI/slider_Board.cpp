//
//  slider_Board.cpp
//  SliderAI.exe
//
//  Aaron Covrig
//  Stephen Ermshar
//

#include <stdio.h>
#include "slider_Board.h"

/*
 board::board(){
 layout = {{NULL,NULL,NULL},{NULL,NULL,NULL},{NULL,NULL,NULL}};// this constructor makes a null board, if it gets used without being edited it should throw an error
 blankR = NULL;
 blankC = NULL;
 move = NULL;
 
 }
 */

board::board(vector<vector<int>> l, char m, vector<char> priorMoves){
    layout = l;
    move = m;
    //previousMoveCount = pMov;
    size = l.size();
    pastMoves = priorMoves;
    if(m != NULL){
        pastMoves.push_back(m);
    }
    //updates the blank tile location, I would make it a function, but this is the only usage:
    for (int i=0; i<layout.size(); i++) {
        for (int j=0; j<layout.at(i).size(); j++) {
            if (layout.at(i).at(j) == 0) {
                blankR = i;
                blankC = j;
            }
        }
    }
}

board::board(board const &b){
    size = b.size;
    blankR = b.blankR;
    blankC = b.blankC;
    layout = b.layout;
    move = b.move;
    pastMoves = b.pastMoves;
    //previousMoveCount = b.previousMoveCount;
}

int board::scoreBoard(){
    int target = 0; // stores the variable to hunt for here
    int score = 0; // Stores the total 'score' here
    for(int r=0; r<layout.size(); r++){
        for(int c=0; c<layout.at(r).size(); c++){
            target = goal[r][c];
            for(int sr=0; sr<layout.size(); sr++){
                for(int sc=0; sc<layout.at(sr).size(); sc++){
                    if((layout[sr][sc] == target) && (layout[sr][sc] != 0)){ // blank tile is not counted
                        score += abs(r - sr) + abs(c - sc);
                    }
                }
            }
        }
    }
    //cout << "score: " << score << endl;
    //score += previousMoveCount;
    score += pastMoves.size();
    return score;
}

vector<board> board::spawnChildren(const vector< vector<int>> &boardLayout){
    //void board::spawnChildren(const vector< vector<int>> &boardLayout, vector<board> &children){
    //children.clear(); // clearing old children and freeing up memory
    vector<board> children;
    { //up
        if ((blankR-1)>(-1)) { // only need to check if it went outside the board on the top side
            vector<vector<int>> childLayout = layout;
            childLayout[blankR][blankC] = layout[blankR-1][blankC];
            childLayout[blankR-1][blankC] = layout[blankR][blankC];
            board childBoard(childLayout, 'U', pastMoves);
            children.push_back(childBoard);
        }
    }
    { //down
        if ((blankR+1)< boardLayout.size()) {
            vector<vector<int>> childLayout = layout;
            childLayout[blankR][blankC] = layout[blankR+1][blankC];
            childLayout[blankR+1][blankC] = layout[blankR][blankC];
            board childBoard(childLayout, 'D', pastMoves);
            children.push_back(childBoard);
        }
    }
    { //left
        if ((blankC-1)>(-1)) {
            vector<vector<int>> childLayout = layout;
            childLayout[blankR][blankC] = layout[blankR][blankC-1];
            childLayout[blankR][blankC-1] = layout[blankR][blankC];
            board childBoard(childLayout, 'L', pastMoves);
            children.push_back(childBoard);
        }
    }
    { //right
        if ((blankC+1)<boardLayout[0].size()) {
            vector<vector<int>> childLayout = layout;
            childLayout[blankR][blankC] = layout[blankR][blankC+1];
            childLayout[blankR][blankC+1] = layout[blankR][blankC];
            board childBoard(childLayout, 'R', pastMoves);
            children.push_back(childBoard);
        }
    }
    return children;
}

bool board::isGoal(){
    for (int i=0; i<layout.size(); i++) {
        for (int j=0; j<layout.at(i).size(); j++) {
            if (layout.at(i).at(j) != goal.at(i).at(j)) {
                return false;
            }
        }
    }
    return true;
}

bool board::isSameAs(board& b){
    for (int i=0; i<layout.size(); i++) {
        for (int j=0; j<layout.at(i).size(); j++) {
            if (layout.at(i).at(j) != b.layout.at(i).at(j)) {
                return false;
            }
        }
    }
    return true;
}

void board::coutBoard(){
    for (int i=0; i<layout.size(); i++) {
        for (int j=0; j<layout.at(i).size(); j++) {
            cout << layout.at(i).at(j) << '\t';
        }
        cout << endl;
    }
}

/*
 board& board::operator=(const board& rightSide){
 if (this != &rightSide) {
 blankR = rightSide.blankR;
 blankC = rightSide.blankC;
 layout = rightSide.layout;
 move = rightSide.move;
 }
 
 return *this;
 }
 */
