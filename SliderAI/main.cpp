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
    int num_rows = 3;
    int num_columns = 3;
    
    tile blankTile(0,0); //! Declairing the location of the empty tile to save time
    
    vector<vector <int > > boardstart = {{1,2,3},{0,5,6},{4,7,8}};
    vector<vector <int > > boardend = {{1,2,3},{4,5,6},{0,7,8}};
    
    targetSearch(0, boardstart, num_rows, num_columns, blankTile);
    
    cout << "Location of blank tile: " << blankTile.row << " " << blankTile.column << endl;
    
    //int score = board_score(boardstart, boardend, num_rows, num_columns);
    
    vector<vector <int > > betterchild;
    childMutate(boardend, boardstart, num_rows, num_columns, betterchild, blankTile);
    
    int scoreStart = board_score(boardstart, boardend, num_rows, num_columns);
    int scoreNXT = board_score(betterchild, boardend, num_rows, num_columns);
    
    /*
    cout << "Starting score = " << scoreStart << endl;
    cout << "Next score = " << scoreNXT << endl;
    
    cout << "Next blank row: " << blankTile.row << endl;
    cout << "Next blank column: " << blankTile.column << endl;
    
    cout << "Starting board: " << endl;
    printBoard(boardstart, num_rows, num_columns);
    cout << endl;
    cout << "Next board: " << endl;
    printBoard(betterchild, num_rows, num_columns);
    cout << endl;
    
    
    
    // more tests
    
    vector<vector <int > > board1 = {{1,2,3},{4,5,0},{7,8,6}};
    vector<vector <int > > board2 = {{1,2,3},{4,5,6},{7,8,0}};
    vector<vector <int > > board3 = {{1,2,3},{4,5,6},{7,8,0}};
    
    int score1 = board_score(board1, board3, num_rows, num_columns);
    int score2 = board_score(board2, board3, num_rows, num_columns);
    
    cout << "Score 1: " << score1 << endl;
    cout << "Score 2: " << score2 << endl;
    */
    //int rootLayout[9] = {1,0,2,4,6,3,7,5,8}; //solvable in <10 moves, index = boardPosition
    
    //board tb1(rootLayout, 1);
    
    //tb1.coutLayout();
    
    //board tb2(tb1);
    
    //tb2.coutLayout();
    
    return 0;
}
