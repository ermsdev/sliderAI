//
//  main.cpp
//  SliderAI
//

#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

//-----------------------------------------------------
// header
//-----------------------------------------------------

class board {
private:
    int blankR;
    int blankC;
    vector<vector<int>> layout;
    char move; //character indicating what move was used to get to this board, null for first board
    int previousMoveCount; //I forgot about this part of the algotithm, the correct scoring function is (manhattan + previousMoveCount)
public:
    static vector<vector<int>> goal;
    //board();
    board(vector<vector<int>> l, char m = NULL, int pMov = 0);
    board(board const &b);
    int scoreBoard();
    vector<board> spawnChildren(const vector< vector<int>> &boardLayout, vector<board> &children);
    vector<vector<int>> getLayout() const {return layout;}
    bool isGoal();
    bool isSameAs(board& b);
    char getMove(){return move;}
    void coutBoard();
    //board& operator=(const board& rightSide);
    vector<vector<int>> getLayout(){return layout;}
    void setLayout(vector<vector<int>> l){layout = l;}
    int get_pMov(){return previousMoveCount;}
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

/*
 board::board(){
 layout = {{NULL,NULL,NULL},{NULL,NULL,NULL},{NULL,NULL,NULL}};// this constructor makes a null board, if it gets used without being edited it should throw an error
 blankR = NULL;
 blankC = NULL;
 move = NULL;
 
 }
 */

board::board(vector<vector<int>> l, char m, int pMov){
    layout = l;
    move = m;
    previousMoveCount = pMov;
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
    blankR = b.blankR;
    blankC = b.blankC;
    layout = b.layout;
    move = b.move;
    previousMoveCount = b.previousMoveCount;
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
    score += previousMoveCount;
    return score;
}

vector<board> board::spawnChildren(const vector< vector<int>> &boardLayout, vector<board> &children){
    children.clear(); // clearing old children and freeing up memory
    { //up
        if ((blankR-1)>(-1)) { // only need to check if it went outside the board on the top side
            vector<vector<int>> childLayout = layout;
            childLayout[blankR][blankC] = layout[blankR-1][blankC];
            childLayout[blankR-1][blankC] = layout[blankR][blankC];
            board childBoard(childLayout, 'U', previousMoveCount++);
            children.push_back(childBoard);
        }
    }
    { //down
        if ((blankR+1)< boardLayout.size()) {
            vector<vector<int>> childLayout = layout;
            childLayout[blankR][blankC] = layout[blankR+1][blankC];
            childLayout[blankR+1][blankC] = layout[blankR][blankC];
            board childBoard(childLayout, 'D', previousMoveCount++);
            children.push_back(childBoard);
        }
    }
    { //left
        if ((blankC-1)>(-1)) {
            vector<vector<int>> childLayout = layout;
            childLayout[blankR][blankC] = layout[blankR][blankC-1];
            childLayout[blankR][blankC-1] = layout[blankR][blankC];
            board childBoard(childLayout, 'L', previousMoveCount++);
            children.push_back(childBoard);
        }
    }
    { //right
        if ((blankC+1)<boardLayout[0].size()) {
            vector<vector<int>> childLayout = layout;
            childLayout[blankR][blankC] = layout[blankR][blankC+1];
            childLayout[blankR][blankC+1] = layout[blankR][blankC];
            board childBoard(childLayout, 'R', previousMoveCount++);
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

//-----------------------------------------------------

//vector<vector<int>> board::goal = {{1,2,3},{4,5,6},{7,8,0}}; //setting static goal
vector<vector<int>> board::goal = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}};; //setting static goal


int main (){
    
    // setting up queue and putting initial state in
    priority_queue<board, deque<board>, compare> boardList;
    //vector<vector<int>> startLayout = {{0,1,3},{4,2,6},{7,5,8}}; // solves in 4 moves: R, D, D, R
    //vector<vector<int>> startLayout = {{5,0,7},{8,2,3},{1,4,6}}; // solves in less than 38 moves
    vector<vector<int>> startLayout = {{5,1,3,4},{0,2,6,8},{9,10,7,11},{13,14,15,12}};
    board startBoard(startLayout);
    boardList.push(startBoard);
    vector<board> childBoards;
    int moveCount = 0;
    bool foundGoal;
    board lastParent(startBoard);
    do{
        board poppedBoard(boardList.top());
        boardList.pop();
        
        poppedBoard.spawnChildren(startLayout, childBoards);
        
        for (int i=0; i<childBoards.size(); i++) {
            {
                if (childBoards.at(i).getLayout() != lastParent.getLayout()) {
                    boardList.push(childBoards.at(i));
                }
            }
        }
        
        foundGoal = poppedBoard.isGoal();
        moveCount++;
        poppedBoard.coutBoard();
        cout << "score: " << poppedBoard.scoreBoard() << endl;
        cout << "move: " << poppedBoard.getMove() << endl;
        cout << "count: " << poppedBoard.get_pMov() << endl << endl;
        
        // THIS DOES NOT KEEP BLANK UPDATED! if we decide later that we need to use blank in lastParent we'll have to set that up then.
        lastParent.setLayout(poppedBoard.getLayout());
    }while(!foundGoal);
    
    cout << "I found the answer in " << moveCount-1 << " moves!\n\n";
    
    
    return 0;
}
