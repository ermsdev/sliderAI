//
//  main.cpp
//  SliderAI
//

#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <ctime>
#include <queue>
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
    int size;
    vector<char> pastMoves;
public:
    static vector<vector<int>> goal;
    //board();
    board(vector<vector<int>> l, char m = NULL, int pMov = 0, vector<char> pastMoves = {});
    board(board const &b);
    int scoreBoard();
    //void spawnChildren(const vector< vector<int>> &boardLayout, vector<board> &children);
    vector<board> spawnChildren(const vector< vector<int>> &boardLayout);
    vector<vector<int>> getLayout() const {return layout;}
    bool isGoal();
    bool isSameAs(board& b);
    char getMove(){return move;}
    void coutBoard();
    //board& operator=(const board& rightSide);
    vector<vector<int>> getLayout(){return layout;}
    void setLayout(vector<vector<int>> l){layout = l;}
    int get_pMov(){return previousMoveCount;}
    int getSize(){return(size);}
    int getMoveCount(){return(pastMoves.size());}
    vector<char> getPastMoves(){return(pastMoves);}
};

class compare{
public:
    bool operator()(board a, board b){
        return a.scoreBoard() > b.scoreBoard();
    }
};

void consoleEntry(board &unsolvedBoard); //! Called to enter puzzle

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

board::board(vector<vector<int>> l, char m, int pMov, vector<char> priorMoves){
    layout = l;
    move = m;
    previousMoveCount = pMov;
    size = l.size();
    pastMoves = priorMoves;
    pastMoves.push_back(m);
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

vector<board> board::spawnChildren(const vector< vector<int>> &boardLayout){
//void board::spawnChildren(const vector< vector<int>> &boardLayout, vector<board> &children){
    //children.clear(); // clearing old children and freeing up memory
    vector<board> children;
    { //up
        if ((blankR-1)>(-1)) { // only need to check if it went outside the board on the top side
            vector<vector<int>> childLayout = layout;
            childLayout[blankR][blankC] = layout[blankR-1][blankC];
            childLayout[blankR-1][blankC] = layout[blankR][blankC];
            board childBoard(childLayout, 'U', previousMoveCount++, pastMoves);
            children.push_back(childBoard);
        }
    }
    { //down
        if ((blankR+1)< boardLayout.size()) {
            vector<vector<int>> childLayout = layout;
            childLayout[blankR][blankC] = layout[blankR+1][blankC];
            childLayout[blankR+1][blankC] = layout[blankR][blankC];
            board childBoard(childLayout, 'D', previousMoveCount++, pastMoves);
            children.push_back(childBoard);
        }
    }
    { //left
        if ((blankC-1)>(-1)) {
            vector<vector<int>> childLayout = layout;
            childLayout[blankR][blankC] = layout[blankR][blankC-1];
            childLayout[blankR][blankC-1] = layout[blankR][blankC];
            board childBoard(childLayout, 'L', previousMoveCount++, pastMoves);
            children.push_back(childBoard);
        }
    }
    { //right
        if ((blankC+1)<boardLayout[0].size()) {
            vector<vector<int>> childLayout = layout;
            childLayout[blankR][blankC] = layout[blankR][blankC+1];
            childLayout[blankR][blankC+1] = layout[blankR][blankC];
            board childBoard(childLayout, 'R', previousMoveCount++, pastMoves);
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

void consoleEntry(board &unsolvedBoard){
    int size;
    cout << "Please enter the number of rows/columns you would like to use: ";
    cin >> size;
    cin.ignore();
    cout << endl;
    cout << "You entered: " << size << " we will now solve a " << size << "x" << size << " puzzle" << endl;
}

//-----------------------------------------------------

vector<vector<int>> board::goal = {{1,2,3},{4,5,6},{7,8,0}}; //setting static goal
//vector<vector<int>> board::goal = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}};; //setting static goal


int main (){
    std::queue<board> boardQueue;
    clock_t begin = clock();
    // setting up queue and putting initial state in
    priority_queue<board, deque<board>, compare> boardList;
    //vector<vector<int>> startLayout = {{0,1,3},{4,2,6},{7,5,8}}; // solves in 4 moves: R, D, D, R
    vector<vector<int>> startLayout = {{5,0,7},{8,2,3},{1,4,6}}; // solves in less than 38 moves
    //vector<vector<int>> startLayout = {{1,2,3},{4,5,6},{7,0,8}};
    //vector<vector<int>> startLayout = {{5,1,3,4},{0,2,6,8},{9,10,7,11},{13,14,15,12}};
    board startBoard(startLayout);
    boardList.push(startBoard);
    vector<board> childBoards;
    int moveCount = 0;
    bool foundGoal;
    board lastParent(startBoard);
    do{
        board poppedBoard(boardList.top());
        boardList.pop();
        boardQueue.push(poppedBoard);
        
        childBoards = poppedBoard.spawnChildren(startLayout);
        //poppedBoard.spawnChildren(startLayout, childBoards);
        //int parentScore = lastParent.scoreBoard();
        for (int i=0; i<childBoards.size(); i++) {
            {
                //if ((childBoards.at(i).getLayout() != lastParent.getLayout()) && (childBoards.at(i).scoreBoard() < lastParent.scoreBoard())){
                if(childBoards.at(i).getLayout() != lastParent.getLayout()){
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
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << elapsed_secs << endl;
    
    board finalBoard(boardList.top());
    cout << finalBoard.getMoveCount() << endl;
    cout << finalBoard.getMove() << endl;
    vector<char> pastMoveList = finalBoard.getPastMoves();
    for(int i = 0; i < finalBoard.getMoveCount(); i++){
        cout << pastMoveList[i] << endl;
    }
    
    /*
    cout << "Real moves needed: " << boardQueue.size() << endl;
    cout << "My moves: " << endl;
    long size = boardQueue.size();
    for(int i = 0; i < size; i++){
    board outBoard(boardQueue.front());
    boardQueue.pop();
    cout << "----------------" << endl;
    outBoard.coutBoard();
    cout << "----------------" << endl;
    }
    */
    
    return 0;
}
