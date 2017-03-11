//
//  slider_Board.h
//  SliderAI.exe
//
//  Created by Aaron Covrig on 3/10/17.
//  Copyright © 2017 Stephen. All rights reserved.
//

#ifndef slider_Board_h
#define slider_Board_h

#include <vector>
#include <string>

using namespace std;

class board {
private:
    int blankR;
    int blankC;
    vector<vector<int>> layout;
    char move; //character indicating what move was used to get to this board, null for first board
    int previousMoveCount; //I forgot about this part of the algotithm, the correct scoring function is (manhattan + previousMoveCount)
    long size;
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
    long getSize(){return(size);}
    long getMoveCount(){return(pastMoves.size());}
    vector<char> getPastMoves(){return(pastMoves);}
};

class compare{
public:
    bool operator()(board a, board b){
        return a.scoreBoard() > b.scoreBoard();
    }
};

#endif /* slider_Board_h */
