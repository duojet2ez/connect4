#include<iostream>
#include<vector>
#include<optional> 
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
        int piecesUsed;
        //function that returns the row # of the cell to change, and if the column is full returns nullopt
        //HOW THIS WORKS optional wraps the value returned in an object that tracks if either valid return or not valid return 'nullopt'
        optional<int> cellToChange(int column){
            //move row by row down column until hit a filled cell return up 1 row if not out of bounds 
            for(int i = 0; i < row; i++){
                if(board[i][column] == Color::red || board[i][column] == Color::yellow){
                    if(i == 0) return nullopt; //all rows filled
                    return i -1; 
                }
            }
            //returns bottom row when empty column detected
            return row - 1;     
        }
    public:
        Board(){
            board = vector<vector<Color>>(row, vector<Color>(column, Color::empty));
            piecesUsed = 0; 
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
        bool dropPiece(int column, Player &player){
            column--; 
            optional<int> rowValue = cellToChange(column);  //rowValue is an object that either contains a valid number (row to drop) or not 
            if(player == Player::red){
                //not a valid move
                if (!rowValue.has_value()) return false;
                
                board[rowValue.value()][column] = Color::red;
                player = Player::yellow;
            }
            else{
                if(!rowValue.has_value()) return false;
                
                board[rowValue.value()][column] = Color::yellow;
                player = Player::red;
            }   
            piecesUsed++;  
            return true; 
        }
        //returns true if win condition met with enum color set for color that wins. If color is empty than no winner
        bool checkWin(Color &winningColor){
            //no winner condition 
            if(piecesUsed == 42){
                winningColor = Color::empty; 
                return true; 
            }
            //iterate over each piece checking for 4 in a row
            for(int i = 0; i < row; i++){
                for(int j = 0; j < column; j++){
                    //make sure NOT starting on an empty cell 
                    if(board[i][j] != Color::empty){
                                            //check up if not out of bounds by furthest point
                    if(i - 3 >= 0){
                        if(board[i][j] == board[i - 1][j] && board[i][j] == board[i - 2][j] && board[i][j] == board[i - 3][j]){
                            //set winner 
                            winningColor = board[i][j]; 
                            return true;
                        }
                    }
                    //check down if not out of bounds by furthest point
                    if(i + 3 <= 5){
                        if(board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j] && board[i][j] == board[i + 3][j]){
                            //set winner 
                            winningColor = board[i][j]; 
                            return true;
                        }
                    }
                    //check left if not out of bounds by furthest point
                    if(j - 3 >=  0){
                        if(board[i][j] == board[i][j - 1] && board[i][j] == board[i][j - 2] && board[i][j] == board[i][j - 3]){
                            //set winner 
                            winningColor = board[i][j]; 
                            return true;
                        }
                    }
                    //check right if not out of bounds by furthest point
                    if(j + 3 <=  6){
                        if(board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2] && board[i][j] == board[i][j + 3]){
                            //set winner 
                            winningColor = board[i][j]; 
                            return true;
                        }
                    }
                    //check horizontal upLeft if not out of bounds by furthest point
                    if(i - 3 >= 0 && j - 3 >= 0){
                        if(board[i][j] == board[i - 1][j - 1] && board[i][j] == board[i - 2][j - 2] && board[i][j] == board[i - 3][j - 3]){
                            winningColor = board[i][j];
                            return true;
                        }
                    }
                    //check horizontal up right if not out of bounds by furthest point
                    if(i - 3 >= 0 && j + 3 <= 6){
                        if(board[i][j] == board[i - 1][j + 1] && board[i][j] == board[i - 2][j + 2] && board[i][j] == board[i - 3][j + 3]){
                            winningColor = board[i][j];
                            return true;
                        }
                    }
                    //check horizontal down left if not out of bounds by furthest point
                    if(i + 3 <= 5 && j - 3 >= 0){
                        if(board[i][j] == board[i + 1][j - 1] && board[i][j] == board[i + 2][j - 2] && board[i][j] == board[i + 3][j - 3]){
                            winningColor = board[i][j];
                            return true;
                        }
                    }
                    //check horizontal down right if not out of bounds by furthest point
                    if(i + 3 <= 5 && j + 3 <= 6){
                        if(board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2] && board[i][j] == board[i + 3][j + 3]){
                            winningColor = board[i][j];
                            return true;
                            }
                        }
                    }
                }
            }
            return false;
        }
};

class Game{
    private:
        bool endCondition;
        int columnSelection; 
        Player currentPlayer; //track player turn
        Color winningColor; 
    public:
        Game(){currentPlayer = Player::red; endCondition = false;}
        Board board;
        void askUserInput(){
            cout << '\n'  << "Enter a column (1 - 7) to drop your piece: " << '\n';
            cin >> columnSelection;
            while(columnSelection <= 0 || columnSelection >7){
                cout << "That's not a valid column. Select again (1 - 7): " << '\n';
                cin >> columnSelection; 
            }
        }
        void playGame(){
            while(!endCondition){
                board.print();
                askUserInput(); 
                while(!board.dropPiece(columnSelection, currentPlayer)) askUserInput(); 
                if(board.checkWin(winningColor)){
                    endCondition = true;
                    //determine who wins 
                    if(winningColor == Color::empty){
                        cout << "It is a tie no one wins!" << '\n';
                    }
                    else if(winningColor == Color::red){
                        cout << "Red Wins!" << '\n';
                    }
                    else{
                        cout << "Yellow Wins!" << '\n'; 
                    }
                } 
            }
        }
};

int main(){
    Game game;
    game.playGame();
    return 0;
}