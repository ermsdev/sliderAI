//
//  sliderai.cpp
//  SliderAI
//

#include "sliderai.h"

//creates board with layout based on input array
board::board(int *n){
    for(int i=0; i<(9); i++){
        layout[i] = n[i];
    }
}

//creates new board identical to input but with pos1 and pos2 swapped
board::board(board &b, int pos1, int pos2){
    for (int i=0; i<(9); i++) {
        layout[i] = b.getLayout()[i];
    }
    int temp = layout[pos1];
    layout[pos1] = layout[pos2];
    layout[pos2] = temp;
}

void board::coutLayout(){
    for(int i=0; i<(9); i++){
        cout << layout[i] << endl;
    }
}
