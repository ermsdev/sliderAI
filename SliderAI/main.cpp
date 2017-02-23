//
//  main.cpp
//  SliderAI
//

#include "sliderai.h"

int main( ) {
    
    int rootLayout[9] = {1,0,2,4,6,3,7,5,8}; //solvable in <10 moves, index = boardPosition
    
    board tb1(rootLayout);
    
    tb1.coutLayout();
    
    board tb2(tb1, 0, 2);
    
    tb2.coutLayout();
    
    return 0;
}
