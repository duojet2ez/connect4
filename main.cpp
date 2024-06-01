#include<iostream>
#include<vector>
using namespace std;

enum class Player{
    red,
    yellow
};

enum class Color{
    red,
    yellow,
    empty
};

class Board{
    private:
        const int row = 6;
        const int column = 7; 
        vector<vector<Color>> board;
    public:
        Board(){
            board = vector<vector<Color>>(row, vector<Color>(column, Color::empty));
        }
        //set new board
        void reset(){

        }
        //function that returns the row # of the cell to change, return -1 if not valid column full 
        int cellToChange(int column){
            //move row by row down column until hit a filled cell return up 1 row if not out of bounds 
            
        }
        //display board
        void print(){
            for(int i = 0; i < row; i++){
                for(int j = 0; j < column; j++){
                    if(board[i][j] == Color::empty) cout << "# ";
                    else if(board[i][j] == Color::red) cout << "R ";
                    else cout << "Y "; 
                }
                cout << '\n';
            }
        }
        void dropPiece(int column, Player player){
            if(player == Player::red){
                column--;
                //determine which cell coordinate to change if any 
                int rowValue = cellToChange(column); 
                //not a valid move
                if(rowValue == -1){
                    //player must be prompted to go again
                }
                board[rowValue][column] = Color::red;

                player = Player::yellow;
            }
            else{
                column--; 
                board[cellToChange(column)][column] = Color::yellow;
                player = Player::red;
            }
            
        }

        bool checkWin(){
            return true;
        }
};


class Game{
    private:
        int columnSelection; 
        void initializeGame(){
            cout << "Set up game" << '\n';

        }
        Player currentPlayer; //track player turn
    public:
        Game(){currentPlayer = Player::red;}
        Board board;
        void askUserInput(){
            cout << '\n'  << "Enter a column (1 - 7) to drop your piece: " << '\n';
            cin >> columnSelection;
        }
        void playGame(){
            while(true){
                board.print();
                askUserInput(); 
                board.dropPiece(columnSelection, currentPlayer);
                //board.checkWin(); 
            }
        }
};


int main(){
    Game game;
    Board b1;


    game.playGame();
    return 0;
}