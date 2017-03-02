//
//  sliderai.h
//  SliderAI
//

#ifndef sliderai_h
#define sliderai_h


#include <iostream>
#include <string>
#include <map>
#include <queue>
using namespace std;


// structure for each tile coordinate
struct tile{
    //int ID; //
    int row;
    int column;
    tile(); //! initializes with -9, meaning unintialized
    //tile(int ID, int row, int column);
    tile(int row, int column);
};


class board{
private:
    map<int, tile> layout;
    static map<int, tile> goal;
public:
    board(int a[], int size);
    int scoreBoard();
    
    //unfinished method functions
    void defineBoard();
    void reDefineGoal();
};


// comparison class
class compareBoards{
public:
    bool operator()(board b1, board b2); //don't know why, but it needs the double parentheses
};

#endif /* sliderai_h */
