//
//  sliderai.h
//  SliderAI
//

#ifndef sliderai_h
#define sliderai_h


#include <iostream>
#include <string>
using namespace std;

class board {
private:
    int layout[9];
    int blankLocation; // so we don't have to search through board for the blank tile
public:
    board(int *n, int bL);
    board(board &b /*, int move*/);
    int* getLayout(){return layout;}
    void coutLayout();
    //char* listMoves();
};

#endif /* sliderai_h */
