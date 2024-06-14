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

bool playerMustSelectAnotherColumn = false; 

class Board{
    private:
        const int row = 6;
        const int column = 7; 
        vector<vector<Color>> board;
    public:
        Board(){
            board = vector<vector<Color>>(row, vector<Color>(column, Color::empty));
        }
        //function that returns the row # of the cell to change, return -1 if not valid column full 
        int cellToChange(int column){
            //move row by row down column until hit a filled cell return up 1 row if not out of bounds 
            for(int i = 0; i < row; i++){
                if(i == row - 1 && board[i][column] == Color::empty) return i; 
                if(board[i][column] == Color::red || board[i][column] == Color::yellow){
                    if(i == 0) return -1; //all rows filled
                    return i -1; 
                }
            }
            return -1;     
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
        void dropPiece(int column, Player &player){
            column--; 
            int rowValue = cellToChange(column); 
            if(player == Player::red){
                //not a valid move1
                if(rowValue == -1){
                    playerMustSelectAnotherColumn = true;
                    return;
                }
                board[rowValue][column] = Color::red;
                player = Player::yellow;

            }
            else{
                if(rowValue == -1){
                    playerMustSelectAnotherColumn = true;
                    return;
                }
                board[rowValue][column] = Color::yellow;
                player = Player::red;
            }   
            playerMustSelectAnotherColumn = false;       
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
            if(playerMustSelectAnotherColumn ==  true){cout << "Column full please select again: "<< '\n'; cin >> columnSelection; return;}
            cout << '\n'  << "Enter a column (1 - 7) to drop your piece: " << '\n';
            cin >> columnSelection;
            while(columnSelection <= 0 || columnSelection >7){
                cout << "That's not a valid column. Select again (1 - 7): " << '\n';
                cin >> columnSelection; 
            }
        }
        void playGame(){
            while(true){
                board.print();
                askUserInput(); 
                board.dropPiece(columnSelection, currentPlayer);
                while(playerMustSelectAnotherColumn){askUserInput(); board.dropPiece(columnSelection, currentPlayer);}
                //board.checkWin(); 
            }
        }
};


int main(){
    Game game;
    game.playGame();
    return 0;
}