//
//  main.cpp
//  SliderAI
//

#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <ctime>

#include "slider_Board.h"

using namespace std;

// Unfinished components {

void consoleEntry(board &unsolvedBoard); //! Called to enter puzzle


void consoleEntry(board &unsolvedBoard){
    int size;
    cout << "Please enter the number of rows/columns you would like to use: ";
    cin >> size;
    cin.ignore();
    cout << endl;
    cout << "You entered: " << size << " we will now solve a " << size << "x" << size << " puzzle" << endl;
}

// End unfinished components }

//-----------------------------------------------------

vector<vector<int>> board::goal = {{1,2,3},{4,5,6},{7,8,0}}; //setting static goal
//vector<vector<int>> board::goal = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}};; //setting static goal


int main (){
    //clock_t begin = clock();
    // setting up queue and putting initial state in
    priority_queue<board, deque<board>, compare> boardList;
    //vector<vector<int>> startLayout = {{0,1,3},{4,2,6},{7,5,8}}; // solves in 4 moves: R, D, D, R
    //vector<vector<int>> startLayout = {{1,0,3},{4,2,5},{7,8,6}};
    vector<vector<int>> startLayout = {{5,0,7},{8,2,3},{1,4,6}}; // solves in less than 38 moves
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
    board startBoard(startLayout);
    boardList.push(startBoard);
    vector<board> childBoards;
    int moveCount = 0;
    bool foundGoal;
    board lastParent(startBoard);
    do{
        board poppedBoard(boardList.top());
        boardList.pop();
        if(poppedBoard.isGoal() == true){
            break;
        }
        
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
    
    //cout << "I found the answer in " << moveCount-1 << " moves!\n\n";
    cout << "I found the answer in " << moveCount << " moves!\n\n";
    //clock_t end = clock();
    //double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    //cout << elapsed_secs << endl;
    
    board finalBoard(boardList.top());
    cout << "My real moves needed: " << finalBoard.getMoveCount() << endl;
    //cout << finalBoard.getMove() << endl;
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
