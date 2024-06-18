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
        int piecesUsed;
    public:
        Board(){
            board = vector<vector<Color>>(row, vector<Color>(column, Color::empty));
            piecesUsed = 0; 
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
            piecesUsed++;  
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
            return false;
        }
};


class Game{
    private:
    bool endCondition;
        int columnSelection; 
        void initializeGame(){
            cout << "Set up game" << '\n';

        }
        Player currentPlayer; //track player turn
        Color winningColor; 
    public:
        Game(){currentPlayer = Player::red; endCondition = false;}
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
            while(!endCondition){
                board.print();
                askUserInput(); 
                board.dropPiece(columnSelection, currentPlayer);
                while(playerMustSelectAnotherColumn){askUserInput(); board.dropPiece(columnSelection, currentPlayer);}
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