#include<iostream>
#include<vector>
using namespace std;

enum class Player{
    red,
    yellow
};

class Game{
    private:
        void initializeGame(){
            cout << "Set up game" << '\n';

        }
        Player currentPLayer; //track player turn
    public:
    void playGame(){
        //game loop
        //initialize game here
        int i = 0; 
        while(true){
        }
    }
    //function to toggle between players
    
};


class Board{
    private:
        enum class Color{
            red,
            yellow,
            empty
        };
        vector<vector<Color>> board(7, vector<Color>(6, Color::empty)); 
        Color playerToColor(Player player){
            //possibly use a switch statment here 

        }
    public:
    //set new board
    void reset(){

    }
    void print(){
        //display board
    }
    void dropPiece(int column, Player player){ //player turn can be an enum
        //need to figure out which player is going 
        //find lowest cell and set 
        playerToColor(); 
        

    }

    bool checkWin(){

    }


};

//maybe a rewind after all is done

int main(){
    Game game;
    game.playGame();
    return 0;
}