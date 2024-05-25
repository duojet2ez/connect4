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
        
    }
    //function to toggle between players

};


class Board{
    private:
        const int row = 6;
        const int column = 7; 
        enum class Color{
            red = 'R',
            yellow = 'Y',
            empty = '#'
        };
        Color playerToColor(Player player){
            //possibly use a switch statment here 
        }
    public:
        Board(){
            vector<vector<Color>>(7, vector<Color>(6, Color::empty));
        }
    //set new board
        void reset(){

        }
        //display board
        void print(){
            for(int i = 0; i < row; i++){
                for(int j = 0; j < column; j++){
                    cout << static_cast<char>(Color::empty) << " "; 
                }
                cout << '\n';
            }

        }
        void dropPiece(int column, Player player){ //player turn can be an enum
            //need to figure out which player is going 
            //find lowest cell and set 
        // playerToColor(); 
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