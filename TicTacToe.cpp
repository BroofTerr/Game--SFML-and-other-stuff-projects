#include <iostream>
#include <string>
#include <ctime>
#include <random>
using namespace std;

void printBoard (string *sign){
    string board = "\n    |  |  \n  -----------\n    |  |  \n  -----------\n    |  |  "; ///board template
    int signSpot = 0; const int boardSpot = 4; ///signSpot used to get the needed value from signs array, boardSpot is a constant to help locating the needed place in "board" string
    for (int i = 1; i <= 17; i+= 7){ /// 17 comes from the multiplication in the comments below to get the needed place value on our board. +7 is needed to access needed char in the board template.
        for (int j = i; j <= i+2; j++){ ///This for declaration is needed to get the needed i value in intervals of 3
            board.insert(boardSpot*j, *(sign+signSpot));
            signSpot++;
        }
    }
    /*board.insert(4, *sign);     /// 4
    board.insert(8, *(sign+1));   /// 4*2
    board.insert(12, *(sign+2));  /// 4*3
    board.insert(32, *(sign+3));  /// 4*8
    board.insert(36, *(sign+4));  /// 4*9
    board.insert(40, *(sign+5));  /// 4*10
    board.insert(60, *(sign+6));  /// 4*15
    board.insert(64, *(sign+7));  /// 4*16
    board.insert(68, *(sign+8));  /// 4*17*/
    cout << board << endl;
}

bool isAvailable (string* sign, int playerMove){
    if (*(sign+(playerMove-1)) != "X" && *(sign+(playerMove-1)) != "O") return true; ///Check if the space is not occupied already
    else if (playerMove == -1) return false; /// A check for "out of bounds" option
    else return false;
}

 ///Doesn't let the player win so easily
int blockMove(string* s){ /// Checks if there are any 2 out of 3 signs in a row/column/diagonal and blocks the first one it finds
    for (int i = 0; i < 9; i+= 3){ ///Checks if player X could win horizontally
        if (*(s+i+1) == "X" && *(s+i+2) == "X" && *(s+i) != "O"){
            return i+1;
        }
        if (*(s+i) == "X" && *(s+i+2) == "X" && *(s+i+1) != "O"){
            return i+2;
        }
        if (*(s+i) == "X" && *(s+i+1) == "X" && *(s+i+2) != "O"){
            return i+3;
        }
    }
    for (int i = 0; i < 3; i++){ ///Checks if player X could win vertically
        if (*(s+i+3) == "X" && *(s+i+6) == "X" && *(s+i) != "O"){
            return i+1;
        }
        if (*(s+i) == "X" && *(s+i+6) == "X" && *(s+i+3) != "O"){
            return i+4;
        }
        if (*(s+i) == "X" && *(s+i+3) == "X" && *(s+i+6) != "O"){
            return i+7;
        }
    }
    if (*(s+4) == "X" && *(s+8) == "X" && *s != "O"){      ///Checks if player X could win diagonally (1-5-9)
        return 1;
    }
    else if (*s == "X" && *(s+8) == "X" && *(s+4) != "O"){      ///Checks if player X could win diagonally (1-5-9)
        return 5;
    }
    else if (*s == "X" && *(s+4) == "X" && *(s+8) != "O"){      ///Checks if player X could win diagonally (1-5-9)
        return 9;
    }
    else if (*(s+4) == "X" && *(s+6) == "X" && *(s+2) != "O"){  ///Checks if player X could win diagonally (3-5-7)
        return 3;
    }
    else if (*(s+2) == "X" && *(s+6) == "X" && *(s+4) != "O"){  ///Checks if player X could win diagonally (3-5-7)
        return 5;
    }
    else if (*(s+2) == "X" && *(s+4) == "X" && *(s+6) != "O"){  ///Checks if player X could win diagonally (3-5-7)
        return 7;
    }
    return -1; ///Used to tell the program that there is no danger yet of the player winning
}

 ///Takes the chance to win the match
 int winMove(string* s){
    for (int i = 0; i < 9; i+= 3){ ///Checks if COM could win horizontally
        if (*(s+i+1) == "O" && *(s+i+2) == "O" && *(s+i) != "X"){
            return i+1;
        }
        if (*(s+i) == "O" && *(s+i+2) == "O" && *(s+i+1) != "X"){
            return i+2;
        }
        if (*(s+i) == "O" && *(s+i+1) == "O" && *(s+i+2) != "X"){
            return i+3;
        }
    }
    for (int i = 0; i < 3; i++){ ///Checks if COM could win vertically
        if (*(s+i+3) == "O" && *(s+i+6) == "O" && *(s+i) != "X"){
            return i+1;
        }
        if (*(s+i) == "O" && *(s+i+6) == "O" && *(s+i+3) != "X"){
            return i+4;
        }
        if (*(s+i) == "O" && *(s+i+3) == "O" && *(s+i+6) != "X"){
            return i+7;
        }
    }
    if (*(s+4) == "O" && *(s+8) == "O" && *s != "X"){      ///Checks if COM could win diagonally (1-5-9)
        return 1;
    }
    else if (*s == "O" && *(s+8) == "O" && *(s+4) != "X"){      ///Checks if COM could win diagonally (1-5-9)
        return 5;
    }
    else if (*s == "O" && *(s+4) == "O" && *(s+8) != "X"){      ///Checks if COM could win diagonally (1-5-9)
        return 9;
    }
    else if (*(s+4) == "O" && *(s+6) == "O" && *(s+2) != "X"){  ///Checks if COM could win diagonally (3-5-7)
        return 3;
    }
    else if (*(s+2) == "O" && *(s+6) == "O" && *(s+4) != "X"){  ///Checks if COM could win diagonally (3-5-7)
        return 5;
    }
    else if (*(s+2) == "O" && *(s+4) == "O" && *(s+6) != "X"){  ///Checks if COM could win diagonally (3-5-7)
        return 7;
    }
    return -1; ///Used to tell the program that there are no possibilities yet for the computer to win the game
 }

 ///makeMove for PvP
void makeMove (string* sign, bool &player, int playerMove, bool isAvailable(string*, int)){
    if (isAvailable(sign, playerMove)){
        if (player){ ///Move for player O
            *(sign+(playerMove-1)) = "O";
            player = false;
        }
        else { ///Move for player X
            *(sign+(playerMove-1)) = "X";
            player = true;
        }
    }
    else if (playerMove == -1) {} ///This makes the game skip this upcoming "cout" if player enters "out of bounds" integer.
    else {
        cout << "I'm sorry but that place is already occupied, please select a different place.\n";
    }
}

 ///Overloaded makeMove for PvC
void makeMove(string* sign, bool &player, int playerMove, bool isAvailable(string*, int), int blockMove(string*)){
    if (isAvailable(sign, playerMove)){
        if (player){
            if (winMove(sign) != -1){ ///Means that if there is a chance for computer to win, it'll go for it, instead of blocking the player
                *(sign+(winMove(sign)-1)) = "O";
                player = false;
            }
            else if (blockMove(sign) != -1){ ///Means that there are 2/3 Xs already in a row/column or diagonally and there is a need to block them off
                *(sign+(blockMove(sign)-1)) = "O";
                player = false;
            }
            else { ///This is accessed if there is no danger of X's win on the upcoming move
                *(sign+(playerMove-1)) = "O";
                player = false;
            }
        }
        else {
            *(sign+(playerMove-1)) = "X";
            player = true;
        }
    }
    else if (playerMove == -1) {} ///Same as above
    else {
        cout << "I'm sorry but that place is already occupied, please select a different place.\n";
    }
}

bool checkDraw(string* s){
    if (*s != "1" && *(s+1) != "2" && *(s+2) != "3" && *(s+3) != "4" && *(s+4) != "5" && *(s+5) != "6" && *(s+6) != "7" && *(s+7) != "8" && *(s+8) != "9"){
        return true;
    } ///A very long if statement. Used to check if all values have been changed to something else than numbers
    else return false;
}

bool checkWin(string* s, bool checkDraw(string*)){
    /// Can make 16 if statements (8 per player) to check winning conditions, OR v
    /// Can make 4 for loops (2 per player) and 4 if statements (2 per player) to check winning conditions
    for (int i = 0; i < 9; i+= 3){ ///Checks if player X won horizontally
        if (*(s+i) == "X" && *(s+i+1) == "X" && *(s+i+2) == "X"){
            cout << "Player X Wins!\n";
            return false;
        }
    }
    for (int i = 0; i < 9; i+= 3){ ///Checks if player O won horizontally
        if (*(s+i) == "O" && *(s+i+1) == "O" && *(s+i+2) == "O"){
            cout << "Player O Wins!\n";
            return false;
        }
    }
    for (int i = 0; i < 3; i++){ ///Checks if player X won vertically
        if (*(s+i) == "X" && *(s+i+3) == "X" && *(s+i+6) == "X"){
            cout << "Player X Wins!\n";
            return false;
        }
    }
    for (int i = 0; i < 3; i++){ ///Checks if player O won vertically
        if (*(s+i) == "O" && *(s+i+3) == "O" && *(s+i+6) == "O"){
            cout << "Player O Wins!\n";
            return false;
        }
    }
    if (*s == "X" && *(s+4) == "X" && *(s+8) == "X"){      ///Checks if player X won diagonally (1-5-9)
        cout << "Player X Wins!\n";
        return false;
    }
    else if (*s == "O" && *(s+4) == "O" && *(s+8) == "O"){      ///Checks if player O won diagonally (1-5-9)
        cout << "Player O Wins!\n";
        return false;
    }
    else if (*(s+2) == "X" && *(s+4) == "X" && *(s+6) == "X"){  ///Checks if player X won diagonally (3-5-7)
        cout << "Player X Wins!\n";
        return false;
    }
    else if (*(s+2) == "O" && *(s+4) == "O" && *(s+6) == "O"){  ///Checks if player O won diagonally (3-5-7)
        cout << "Player O Wins!\n";
        return false;
    }
    else if (checkDraw(s)){
        cout << "It's a draw! Good Game.\n";
        return false;
    }

    return true;
}

int main(){
    string signs[9] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
    string* s = signs; ///Points to the first value (s for sign)
    bool player = false; ///Used to check which player's move it is; false for X, true for O
    int playMode = 0; ///Player chooses either to play against another human(0), or a CPU(1)
    int playerMove; ///used for the values from 1-9 to make a move
    cout << "The game works like this: \n 1. Player one (X) writes the number of the place in the board ";
    cout << "he wants to place his X\n ";
    cout << "2. Player two (O), if the place is not occupied, writes the number of the place he ";
    cout << "wants to place his O (Player 2 is the CPU if chosen \"vs CPU\" mode)\n ";
    cout << "3. The game goes on like this until either one of the players places his sign 3 ";
    cout << "times in a row horizontally, vertically or diagonally, or the board is filled   ";
    cout << "without making 3 in a row, ending the game in a draw\n\n";
    cout << "If you want to play against a player, write 0, if against a CPU, write 1\n";
    /// Determines the playing mode of the game
    while(true){
        try {
            cout << "Gamemode: "; cin >> playMode;
            if (playMode != 0 && playMode != 1){
                throw 0;
            }
            else break;
        }
        catch (int error){
            cout << "Error, your only choices are 0 and 1\n\n";
        }
    }

    /// Game Loop
    if (playMode == 0){ /// Player vs Player
        while(checkWin(s, checkDraw)){
            printBoard(s);
            if (player) cout << "\nYour move, Mister O\n"; ///Explained in definition of boolean player
            else cout << "\nYour move, Mister X\n";

            try {
                cout << "Place your sign in square Nr.: "; cin >> playerMove; cout << endl;
                if (playerMove < 1 || playerMove > 9){
                    throw 1;
                }
            } catch(int error){
                cout << "Error, out of bounds, please select a number 1 through 9\n";
                playerMove = -1; ///Used for additional check in "isAvailable"
            }

            makeMove(s, player, playerMove, isAvailable); ///makeMove function (takes a boolean function parameter (isAvailable)) makeMove function will change the players accordingly
        }
    }
    else { /// Player vs Computer
        mt19937 random(time(0));
        uniform_real_distribution<> compMove(1,9);
        while (checkWin(s, checkDraw)){
            printBoard(s);
            if (player){
                cout << "\nComputer's Move: ";
                while(true){ ///Just in case computer would generate a number already taken
                    playerMove = compMove(random);
                    if (isAvailable(s, playerMove)) cout<< playerMove << endl; break;
                }
            }
            else {
                cout << "\nYour move, Mister X\n";
                try {
                    cout << "Place your sign in square Nr.: "; cin >> playerMove; cout << endl;
                    if (playerMove < 1 || playerMove > 9){
                        throw 1;
                    }
                } catch(int error){
                    cout << "Error, out of bounds, please select a number 1 through 9\n";
                    playerMove = -1; ///Used for additional check in "isAvailable"
                }
            }

            makeMove(s, player, playerMove, isAvailable, blockMove);
        }
    }
    printBoard(s); ///The board of the end game result
    return 0;
}
