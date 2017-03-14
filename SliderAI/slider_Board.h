//
//  slider_Board.h
//  SliderAI.exe
//
//  Aaron Covrig
//  Stephen Ermshar
//

#ifndef slider_Board_h
#define slider_Board_h

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <ctime>
#include <fstream>

using namespace std;

class board {
private:
    int blankR;
    int blankC;
    vector<vector<int>> layout;
    char move; //character indicating what move was used to get to this board, null for first board
    long size;
    vector<char> pastMoves;
    int score;
public:
    static vector<vector<int>> goal;
    //------------------------------
    // constructors
    //------------------------------
    board(vector<vector<int>> l, char m = NULL, vector<char> pastMoves = {});
    board(board const &b);
    board();
    //------------------------------
    // accessor / mutator functions
    //------------------------------
    char getMove(){return move;}
    vector<vector<int>> getLayout(){return layout;}
    long getSize() const {return(size);}
    long getMoveCount() const {return(pastMoves.size());}
    vector<char> getPastMoves(){return(pastMoves);}
    int getBlankRow() const {return(blankR);}
    int getBlankColumn() const {return(blankC);}
    vector<vector<int>> getLayout() const {return layout;}
    int getScore(){return score;}
    void setLayout(vector<vector<int>> l){layout = l;}
    void setGoal(vector<vector<int>> g){goal = g;}
    //------------------------------
    // "the cool part..." functions
    //------------------------------
    int scoreBoard(void);
    vector<board> spawnChildren(void);
    bool isGoal(void);
    bool isSameAs(board& b);
    void coutBoard(void);
    long inversionCount(void) const;
    bool isSolvable(void);
    void writeFile(const board &referenceBoard, string filename = "sliderAIoutput.txt");
    
};

class compare{
public:
    bool operator()(board a, board b){
        return a.getScore() > b.getScore();
    }
};

#endif /* slider_Board_h */
