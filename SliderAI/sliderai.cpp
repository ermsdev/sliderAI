//
//  sliderai.cpp
//  SliderAI
//

#include "sliderai.h"

//creates board with layout based on input array
board::board(int *n, int bL){
    for(int i=0; i<(9); i++){
        layout[i] = n[i];
    }
    blankLocation = bL;
}

//creates new board identical to input but with pos1 and pos2 swapped
/*board::board(board &b, int pos1, int pos2){
    for (int i=0; i<(9); i++) {
        layout[i] = b.getLayout()[i];
    }
    int temp = layout[pos1];
    layout[pos1] = layout[pos2];
    layout[pos2] = temp;
}
*/

board::board(board &b /*, int move  //no paradigm for indicating moves yet */){
    //copies layout and blankLocation from input to new board
    for (int i=0; i<(9); i++) {
        layout[i] = b.getLayout()[i];
    }
    blankLocation = b.blankLocation;
    
    //asuming move is Down, the program would do something like this:
    layout[blankLocation] = b.getLayout()[blankLocation+3];
    layout[blankLocation+3] = b.getLayout()[blankLocation];
    blankLocation = blankLocation+3;
}

void board::coutLayout(){
    // I've been struggling with 2D arrays, so here I'm using pointer arithmetic, 2D arrays may be better
    // - stephen
    for(int i=0; i<(3); i++){
        for (int j=i*3; j<((i*3)+3); j++) {
            cout << layout[j];
        }
        cout << endl;
    }
    cout << endl;
}


/*
int* listMoves(){
    layout[]
}
*/
