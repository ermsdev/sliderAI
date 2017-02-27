//
//  sliderai.h
//  SliderAI
//

#ifndef sliderai_h
#define sliderai_h


#include <iostream>
#include <string>
#include <map>
#include <queue>
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



class board{
private:
    map<int, tile> layout;
    static map<int, tile> goal;
public:
    board(int a[], int size){
        for (int i=0; i<size; i++) {
            layout[a[i]] = tile((i/3)+1, (i+1)/3);
        }
    }
    int scoreBoard(){
        int score = 0;
        for(int i = 0; i < goal.size(); i++){
            //int temp = mapCurrent.find(2);
            //cout << mapCurrent.find(1)->second.row;
            
            
            //auto search = mapCurrent.find(2);
            auto search = layout.find(i); //! We currently can't skip around (not sure how to access key value), see following line
            //auto search = mapCurrent.find(mapTarget.at(i)); // how to do this?
            //tile test = mapCurrent.find(1);
            score += abs(goal[i].row - layout[search->first].row) + abs(goal[i].column - layout[search->first].column);
            //score += ((mapTarget[i].row - mapCurrent[search->first].row) * (mapTarget[i].row - mapCurrent[search->first].row) + (mapTarget[i].column - mapTarget[search->first].column) * (mapTarget[i].column - mapTarget[search->first].column));
            /*
             cout << "Search value: " << search->first << endl;
             cout << "Item row number: " << mapCurrent[search->first].row << endl;
             cout << "Target row number: " << mapTarget[search->first].row << endl;
             cout << "Item column number: " << mapCurrent[search->first].column << endl;
             cout << "Target column number: " << mapTarget[search->first].column << endl;
             cout << (abs(mapTarget[i].row - mapCurrent[search->first].row) + abs(mapTarget[i].column - mapCurrent[search->first].column)) << endl;
             */
            
            //score += abs(mapTarget[i].row - mapCurrent[search].row) + abs(mapTarget[i].column - mapTarget[search].column);
            //score += abs(mapTarget[i].row - mapCurrent[search->first].row);
        }
        return score;
    }
};


//comparison class
class compareBoards{
public:
    bool operator() (board b1, board b2){
        return b1.scoreBoard() < b2.scoreBoard();
    }
};



//priority_queue<map<tile>> boardList;



#endif /* sliderai_h */
