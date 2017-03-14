//
//  slider_Board.cpp
//  SliderAI.exe
//
//  Aaron Covrig
//  Stephen Ermshar
//

#include <stdio.h>
#include <fstream>

#include "slider_Board.h"

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
    score = scoreBoard();
}

board::board(board const &b){
    size = b.size;
    blankR = b.blankR;
    blankC = b.blankC;
    layout = b.layout;
    move = b.move;
    pastMoves = b.pastMoves;
    score = scoreBoard();
    //previousMoveCount = b.previousMoveCount;
}

board::board(){
    move = NULL;
    do{
        cout << "Please enter the number of rows/columns you would like to use: ";
        cin >> size;
    }while(!cin);
    cin.ignore();
    cout << endl;
    cout << "You entered: " << size << " we will now solve a " << size << "x" << size << " puzzle" << endl;
    do {
        cout << "Enter your layout as a list of " << size*size << " integers seperated by spaces: ";
        for (int i=0; i<size; i++) {
            layout.push_back(vector<int>(size, 0));
            for (int j=0; j<size; j++) {
                cin >> layout[i][j];
                if (layout[i][j] == 0) {
                    blankR = i;
                    blankC = j;
                }
            }
        }
    }while(!cin);
    
}

//! \brief Scores the board based on the Manhattan distance
//
// Iterative loop that currently runs through all tiles to score
// the board, a suggested future improvement would reference a
// stored score and only check the change in value caused by the
// two tiles that are to be swapped.  This should drastically
// reduce run time by reducing the exponential relationship n*n to
// a constant 2 comparison.
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

vector<board> board::spawnChildren(){
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
        if ((blankR+1)< size) {
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
        if ((blankC+1)<size) {
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

int board::inversionCount(void){
    vector<vector<int>> search_board = layout;
    int target = 0;
    int present = 0;
    long numRows = size;
    long numColumns = numRows; //! This currently limits us to n*n, probably have other areas that do the same
    int inversion_count = 0;
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numColumns; j++){
            target = goal[i][j];
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
    }while(!cin);
    goal = layout;
    int goalmaker = 1;
    for (int i = 0; i<size; i++) {
        for (int j = 0; j<size; j++) {
            goal[i][j] = goalmaker;
            goalmaker++;
        }
    }
    goal[size-1][size-1] = 0;
    score = scoreBoard();
    }
    return(inversion_count);
}
/*
bool board::isSolvable(){
    bool isSolvable = false;
    vector<vector<int>> search_board = layout;
    int target = 0;
    int present = 0;
    long numRows = size;
    long numColumns = numRows; //! This currently limits us to n*n, probably have other areas that do the same
    int inversion_count = 0;
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numColumns; j++){
            target = goal[i][j];
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
 */
bool board::isSolvable(){
    bool isSolvable = false;
    vector<vector<int>> search_board = layout;
    long numRows = size;
    long numColumns = numRows; //! This currently limits us to n*n, probably have other areas that do the same
    int inversion_count = inversionCount(); //! Finding the number of inversions
    
    if(numRows != numColumns){
        cout << "This version of the solver only supports square boards at this time" << endl;
    }
    else if(((numColumns % 2) != 0) && ((inversion_count % 2) == 0)){ //! Checking if the board is odd and number of inversions is even
        isSolvable = true;
    }
    else if((numRows % 2) == 0){    //! Checking if board is divisible by 2 (even)
        if(((blankR) % 2 == 0) && (inversion_count % 2 != 0)){ //! Checking if on even row and number of inversions is odd
            isSolvable = true;
        }
        else if(((blankR) % 2 == 1) && (inversion_count % 2 == 0)){
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

void board::writeFile(string filename, const board &startBoard){
    ofstream outputFile;
    outputFile.open (filename);
    if ( !outputFile ) {
        cout << "Unable to openfile, will try again" << endl;
        if ( !outputFile ) {
            cout << "Unable to openfile, 2nd failed attempt, ending" << endl;
            return; // Won't write output to file
        }
    }
    // Outputing the Goal layout
    outputFile << "Goal board:\n";
    outputFile << "----------Begin----------\n";
    for (int i=0; i<goal.size(); i++) {
        for (int j=0; j<goal.at(i).size(); j++) {
            outputFile << goal.at(i).at(j) << '\t';
        }
        outputFile << endl;
    }
    outputFile << "-----------End-----------\n";
    // Outputing the intial board layout
    outputFile << "Inital board:\n";
    outputFile << "----------Begin----------\n";
    for (int i=0; i<layout.size(); i++) {
        for (int j=0; j<layout.at(i).size(); j++) {
            outputFile << layout.at(i).at(j) << '\t';
        }
        outputFile << endl;
    }
    outputFile << "Board complexity: " << startBoard.inversionCount() << " total inversions \n";
    outputFile << "-----------End-----------\n";
    outputFile << "Moves needed to solve board:\n";
    outputFile << "----------Begin----------\n";
    vector<char> requiredMoves = getPastMoves();
    for(int i = 0; i < requiredMoves.size(); i++){
        outputFile << requiredMoves[i] << "\n";
    }
    outputFile << "-----------End-----------\n";
    outputFile.close();
}
