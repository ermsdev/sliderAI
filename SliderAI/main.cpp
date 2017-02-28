//
//  main.cpp
//  SliderAI
//

#include <vector>
#include <map>


#include "sliderai.h"
#include "sliderai_functions.h"


using namespace std;

int main( ) {
    
    // testing stuff
    //vector<vector <int > > boardstart = {{2,1,3},{4,5,6},{7,8,9}};
    //vector<vector <int > > boardend = {{1,2,3},{4,5,6},{7,8,9}};
    //tile tz = {1,1};
    //map<int,char> example = {{1,'a'},{2,'b'}};
    
    map<int, tile> boardstart;
    //boardstart[key] = tile(row, column) ?
    boardstart[1] = tile(1,1);
    boardstart[0] = tile(1,2);
    boardstart[2] = tile(1,3);
    boardstart[8] = tile(2,1);
    boardstart[5] = tile(2,2);
    boardstart[4] = tile(2,3);
    boardstart[6] = tile(3,1);
    boardstart[7] = tile(3,2);
    boardstart[3] = tile(3,3);
    
    
    map<int, tile> boardend;
    boardend[0] = tile(1,1);
    boardend[1] = tile(1,2);
    boardend[2] = tile(1,3);
    boardend[3] = tile(2,1);
    boardend[4] = tile(2,2);
    boardend[5] = tile(2,3);
    boardend[6] = tile(3,1);
    boardend[7] = tile(3,2);
    boardend[8] = tile(3,3);

    
    int score = 0;
    board_map_score(boardstart, boardend, score);
    cout << score << endl;

    
    //board_score(boardstart, boardend, 3, 3, score);
    
    //int rootLayout[9] = {1,0,2,4,6,3,7,5,8}; //solvable in <10 moves, index = boardPosition
    
    //board tb1(rootLayout, 1);
    
    //tb1.coutLayout();
    
    //board tb2(tb1);
    
    //tb2.coutLayout();
    
    return 0;
}
