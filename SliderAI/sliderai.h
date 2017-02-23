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
    int layout[3];
public:
    //inline functions to be moved to implementation when working
    board(int *n);
    board(board &b, int pos1, int pos2);
    int* getLayout(){return layout;}
    void coutLayout();
};

#endif /* sliderai_h */
