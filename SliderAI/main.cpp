//
//  main.cpp
//  SliderAI
//

#include "sliderai.h"
#include "sliderai_functions.h"
#include <vector>

using namespace std;

int main( ) {
    
    // testing stuff
    vector<vector <int > > boardstart = {{2,1,3},{4,5,6},{7,8,9}};
    vector<vector <int > > boardend = {{1,2,3},{4,5,6},{7,8,9}};
    
    int score = 0;
    board_score(boardstart, boardend, 3, 3, score);
    
    //int rootLayout[9] = {1,0,2,4,6,3,7,5,8}; //solvable in <10 moves, index = boardPosition
    
    //board tb1(rootLayout, 1);
    
    //tb1.coutLayout();
    
    //board tb2(tb1);
    
    //tb2.coutLayout();
    
    return 0;
}
