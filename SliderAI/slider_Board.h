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
    static vector<vector<int>> goal; //! Goal Layout
    board(vector<vector<int>> goalBoard, vector<vector<int>> unsolvedBoard);
    //board();
    board(vector<vector<int>> l, char m = NULL, int pMov = 0, vector<char> pastMoves = {});
    board(board const &b);
    int scoreBoard();
    void FindandSetBlank(void); //! Finds the blank tile in the current layout and updates the blankR and blankC values
    vector<board> spawnChildren(const vector< vector<int>> &boardLayout); //! Spawns child boards
    vector<vector<int>> getLayout() const {return layout;} //! Returns the current layout
    bool isGoal(); //! Checks to see if the current layout is the same as the goal layout
    bool isSameAs(board& b); //! Checks to see if two boards are the same
    char getMove(){return move;} //! Gets the last move to create the board
    void coutBoard(); //! Prints the current board layout to the console
    //board& operator=(const board& rightSide);
    vector<vector<int>> getLayout(){return layout;} //! Returns a vector of the current board layout
    void setLayout(vector<vector<int>> l){layout = l;} //! Modifies the vector of the current board layout
    int get_pMov(){return previousMoveCount;} //! Returns the number of moves to create the board/find the board
    long getSize() const {return(size);} //! Returns the row/column size of the board
    long getMoveCount() const {return(pastMoves.size());} //! Returns the number of real moves to the present board
    vector<char> getPastMoves(){return(pastMoves);} //! Returns the required steps to create the present board
    int getBlankRow() const {return(blankR);} //! Returns the current blank row
    int getBlankColumn() const {return(blankC);} //! Returns the current blank column
    void setBlankRow(int row){blankR = row;} //! Sets the current blank row
    void setBlankColumn(int column){blankC = column;} //! Sets the current blank column
};

class compare{
public:
    bool operator()(board a, board b){
        return a.scoreBoard() > b.scoreBoard();
    }
};

#endif /* slider_Board_h */
