//
//  sliderai.h
//  SliderAI
//

#ifndef sliderai_h
#define sliderai_h


#include <iostream>
#include <string>
#include <map>
using namespace std;

//class board {
//private:
    //int layout[9];
    //int blankLocation; // so we don't have to search through board for the blank tile
    
    // Lets try storing the tile identifier in the first int
    // and the coordinates in the 2nd nested map (row, column)
    //map<int, map<int, int>> boardmap;
//public:
    //void getMap(map<int, map<int, int>> &mapOut);
    
//};

// structure for each tile coordinate
struct tile{
    //int ID; //
    int row;
    int column;

    tile(); //! initializes with -9, meaning unintialized
    //tile(int ID, int row, int column);
    tile(int row, int column);
};

/*
class board{
    private:
    
    public:
        void setTile();
        void printTile();
};
*/

#endif /* sliderai_h */
