//
//  main.cpp
//  SliderAI
//
//  Aaron Covrig
//  Stephen Ermshar
//

#include "slider_Board.h"

using namespace std;

//vector<vector<int>> board::goal = {{1,2,3},{4,5,6},{7,8,0}}; //setting static goal
//vector<vector<int>> board::goal = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}}; //setting static goal

vector<vector<int>> board::goal = {{0}}; //setting static goal

int main (){
    clock_t begin = clock();
    // setting up queue and putting initial state in
    //priority_queue<board, deque<board>, compare> boardList;
    //board startBoard(startLayout);
    board startBoard;
    priority_queue<board, deque<board>, compare> boardList;
    bool canSolveBoard = startBoard.isSolvable();
    if(canSolveBoard){
        cout << "This is a valid board" << endl;
        cout << "Solving: " << endl;
    }
    else{
        cout << "This board can not be solved" << endl;
        return(0);
    }
    
    boardList.push(startBoard);
    vector<board> childBoards;
    int moveCount = 0;
    bool foundGoal;
    
    //! Relations, used to speed up searches
    //vector<board> relations;
    //int totalRelatives = 2;
    board lastParent(startBoard);
    board lastGrandParent(startBoard);
    board lastGreatGrandParent(startBoard);
    //relations.push_back(lastParent);
    
    board finalBoard = lastParent;
    do{
        board poppedBoard(boardList.top());
        boardList.pop();
        
        childBoards = poppedBoard.spawnChildren();
        for (int i=0; i<childBoards.size(); i++) {
            {
                if((childBoards[i].getLayout() != lastParent.getLayout()) && (childBoards[i].getLayout() != lastGrandParent.getLayout()) && (childBoards[i].getLayout() != lastGreatGrandParent.getLayout())){
                    boardList.push(childBoards.at(i));
                }
                /*
                for(int j = 0; j < relations.size(); j++){
                    if(childBoards[i].getLayout() != relations[j].getLayout()){
                        boardList.push(childBoards[i]);
                    }
                }
                */
                
            }
        }
        
        foundGoal = poppedBoard.isGoal();
        moveCount++;
        
        poppedBoard.coutBoard();
        cout << "score: " << poppedBoard.scoreBoard() << endl;
        cout << "move: " << poppedBoard.getMove() << endl;
        cout << "count: " << poppedBoard.getMoveCount() << endl << endl;
        
        if(foundGoal){
            finalBoard = poppedBoard; // some weird work around to get the actual final board
        }
        // THIS DOES NOT KEEP BLANK UPDATED! if we decide later that we need to use blank in lastParent we'll have to set that up then.
        lastGreatGrandParent.setLayout(lastGrandParent.getLayout());
        lastGrandParent.setLayout(lastParent.getLayout());
        // Part of broken attempt to allow for dynamic family size control
        /*
        if(relations.size() < totalRelatives){
            relations.push_back(lastParent);
        }
        else{
            relations[0] = lastParent;
            rotate(relations.begin(), relations.end() -1, relations.end());
        }
        */
        lastParent.setLayout(poppedBoard.getLayout());
    }while(!foundGoal);
    
    cout << "I found the answer in " << moveCount << " moves!\n\n";
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << elapsed_secs << endl;
    
    cout << "My real moves needed: " << finalBoard.getMoveCount() << endl;
    vector<char> pastMoveList = finalBoard.getPastMoves();
    for(int i = 0; i < finalBoard.getMoveCount(); i++){
        cout << pastMoveList[i] << endl;
    }
    finalBoard.writeFile(startBoard);
    
    return 0;
}


//-------------------------------------------------------------
// Start boards with known results
//-------------------------------------------------------------

//vector<vector<int>> startLayout = {{0,1,3},{4,2,6},{7,5,8}}; // solves in 4 moves: R, D, D, R
//vector<vector<int>> startLayout = {{1,0,3},{4,2,5},{7,8,6}};
//vector<vector<int>> startLayout = {{5,0,7},{8,2,3},{1,4,6}}; // solves in less than 38 moves
//vector<vector<int>> startLayout = {{1,2,3},{4,5,6},{7,0,8}};
/*
 vector<vector<int>> startLayout = {{2,8,3},
 {1,5,0},
 {4,7,6}};
 */
/*
 vector<vector<int>> startLayout = {{2,8,3},
 {1,0,5},
 {4,7,6}};
 */
/*
 vector<vector<int>> startLayout = {{2,6,8}, // solves only with += previousMoveCount
 {5,4,7},
 {3,0,1}};
 */
/*
 vector<vector<int>> startLayout = {{2,6,8}, // solves only with += previousMoveCount
 {5,4,7},
 {3,0,1}};
 */
/*
 vector<vector<int>> startLayout = {{1,2,3},
 {4,5,6},
 {7,8,0}};
 */
//vector<vector<int>> startLayout = {{5,1,3,4},{0,2,6,8},{9,10,7,11},{13,14,15,12}};
//vector<vector<int>> startLayout = {{1,2,3,4},{5,6,7,8},{9,10,0,12},{13,14,11,15}};
/*
 vector<vector<int>> startLayout = {{1,2,3,4},
 {5,6,7,8},
 {9,10,11,12},
 {13,14,15,0}};
 */
/*
 vector<vector<int>> startLayout = {{3,9,1,15}, // Impossible to solve board
 {14,11,4,6},
 {13,0,10,12},
 {2,7,8,5}};
 */

