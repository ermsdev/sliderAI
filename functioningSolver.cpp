//
//  main.cpp
//  SliderAI2
//
//  Created on 2/26/17.
//

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

//-----------------------------------------------------
// header
//-----------------------------------------------------

class board {
private:
    int blank[2];
    vector<vector<int>> layout;
    char move; //character indicating what move was used to get to this board, null for first board
public:
    static vector<vector<int>> goal;
    board(vector<vector<int>> l, char m = NULL);
    board(board const &b);
    int scoreBoard();
    vector<board> spawnChildren();
    vector<vector<int>> getLayout() const {return layout;}
    bool isGoal();
    char getMove(){return move;}
};

class compare{
public:
    bool operator()(board a, board b){
        return a.scoreBoard() > b.scoreBoard();
    }
};

//-----------------------------------------------------


//-----------------------------------------------------
// implementation
//-----------------------------------------------------

board::board(vector<vector<int>> l, char m){
    layout = l;
    move = m;
    //updates the blank tile location, I would make it a function, but this is the only usage:
    for (int i=0; i<layout.size(); i++) {
        for (int j=0; j<layout.at(i).size(); j++) {
            if (layout.at(i).at(j) == 0) {
                blank[0] = i;
                blank[1] = j;
            }
        }
    }
}

board::board(board const &b){
    blank[0] = b.blank [0];
    blank[1] = b.blank[1];
    layout = b.layout;
    move = b.move;
}

int board::scoreBoard(){
    int target = 0; // stores the variable to hunt for here
    int score = 0; // Stores the total 'score' here
    for(int r=0; r<layout.size(); r++){
        for(int c=0; c<layout.at(r).size(); c++){
            target = goal[r][c];
            for(int sr=0; sr<layout.size(); sr++){
                for(int sc=0; sc<layout.at(sr).size(); sc++){
                    if(layout[sr][sc] == target){
                        score += abs(r - sr) + abs(c - sc);
                    }
                }
            }
        }
    }
    //cout << "score: " << score << endl;
    return score;
}

vector<board> board::spawnChildren(){
    vector<board> children;
    
    { //up
        int i=blank[0]-1, j=blank[1];
        if (i<3 && i>(-1)) {
            vector<vector<int>> childLayout = layout;
            childLayout[blank[0]][blank[1]] = layout[i][j];
            childLayout[i][j] = layout[blank[0]][blank[1]];
            board childBoard(childLayout, 'U');
            children.push_back(childBoard);
        }
    }
    { //down
        int i=blank[0]+1, j=blank[1];
        if (i<3 && i>(-1)) {
            vector<vector<int>> childLayout = layout;
            childLayout[blank[0]][blank[1]] = layout[i][j];
            childLayout[i][j] = layout[blank[0]][blank[1]];
            board childBoard(childLayout, 'D');
            children.push_back(childBoard);
        }
    }
    { //left
        int i=blank[0], j=blank[1]-1;
        if (i<3 && i>(-1)) {
            vector<vector<int>> childLayout = layout;
            childLayout[blank[0]][blank[1]] = layout[i][j];
            childLayout[i][j] = layout[blank[0]][blank[1]];
            board childBoard(childLayout, 'L');
            children.push_back(childBoard);
        }
    }
    { //right
        int i=blank[0], j=blank[1]+1;
        if (i<3 && i>(-1)) {
            vector<vector<int>> childLayout = layout;
            childLayout[blank[0]][blank[1]] = layout[i][j];
            childLayout[i][j] = layout[blank[0]][blank[1]];
            board childBoard(childLayout, 'R');
            children.push_back(childBoard);
        }
    }
    
    /*
     //I forgot tiles can't move diagonaly, so this for loop won't work, but it might be useful to save
        for (int i=blank[0]-1; i<blank[0]+1; i++) {
        for (int j=blank[1]-1; j<blank[1]+1; j++) {
            if ((i<3 && i>(-1)) && (j<3 && j>(-1))) {
                vector<vector<int>> childLayout = layout;
                childLayout[blank[0]][blank[1]] = layout[i][j];
                childLayout[i][j] = layout[blank[0]][blank[1]];
                board childBoard(childLayout);
                children.push_back(childBoard);
            }
        }
    }
     */
    
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

//-----------------------------------------------------


vector<vector<int>> board::goal = {{1,2,3},{4,5,6},{7,8,0}}; //setting static goal


int main (){
    
    // setting up queue and putting initial state in
    priority_queue<board, deque<board>, compare> boardList;
    vector<vector<int>> startLayout = {{0,1,3},{4,2,6},{7,5,8}}; //solves in 4 moves: R, D, D, R
    board startBoard(startLayout);
    boardList.push(startBoard);
    
    int moveCount = 0;
    bool foundGoal;
    do{
        board poppedBoard(boardList.top());
        boardList.pop();
        
        vector<board> childBoards = poppedBoard.spawnChildren();
        
        for (int i=0; i<childBoards.size(); i++) {
            boardList.push(childBoards.at(i));
        }
        
        foundGoal = poppedBoard.isGoal();
        moveCount++;
        cout << poppedBoard.getMove() << endl << endl;
    }while(!foundGoal);
    
    cout << "I found the answer in " << moveCount-1 << " moves!\n\n";
    
    
    return 0;
}
