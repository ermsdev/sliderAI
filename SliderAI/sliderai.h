//
//  sliderai.h
//  SliderAI
//

#ifndef sliderai_h
#define sliderai_h


#include <iostream>
#include <string>
#include <vector>

using namespace std;


class board {
    private:
        int num_rows;
        int num_colums;

    public:
        vector < vector <int > > board;
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
