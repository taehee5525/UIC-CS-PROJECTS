// Prog5Pentago.cpp
// Play the two-player game of Pentago, trying to get 5 pieces in a row.
//
// Author: Tae Hee Park
// Program: #5, Pentago using classes
// 04/10/2020
//

#include <iostream>  // Needed to avoid compiler error for the exit() command
#include <cctype>    // For toupper()
#include <iomanip>  // For setfill/setw

using namespace std;



//-------------------------------------------------------------------------------------
void welcomeMessage() {
    cout << "Welcome to Pentago, where you try to get 5 of your pieces in a line." << endl;
    cout << "At any point enter 'x' to exit, 'i' for instructions, or 'u' to undo. " << endl;
    cout << endl;
}

void displayInstructions()
{
    cout << "\n"
        << "Play the two-player game of Pentago. Be the first to get 5 in a row. \n"
        << "                                                                 \n"
        << "Pentago is played on a 6 by 6 board, divided into four 3 by 3    \n"
        << "quadrants.  There are two players, X and O, who alternate turns. \n"
        << "The goal of each player is to get five of their pieces in a row, \n"
        << "either horizontally, vertically, or diagonally.                  \n"
        << "                                                                 \n"
        << "Players take turns placing one of their pieces into an empty     \n"
        << "space anywhere on the board, then choosing one of the four       \n"
        << "board quadrants to rotate 90 degrees left or right.              \n"
        << "                                                                 \n"
        << "If both players get five in a row at the same time, or the       \n"
        << "last move is played with no five in a row, the game is a tie.    \n"
        << "If a player makes five a row by placing a piece, there is no need\n"
        << "to rotate a quadrant and the player wins immediately.            \n"
        << "                                                                 \n"
        << "     Play online at:  https://perfect-pentago.net                \n"
        << "     Purchase at:     www.mindtwisterusa.com                     \n"
        << "                                                                 \n"
        << "For each move provide four inputs:                               \n"
        << "   row (A-F), column (1-6), quadrant (1-4), rotation direction (L or R) \n"
        << "For instance input of B32R places the next piece at B3 and then  \n"
        << "would rotate quadrant 2 (upper-right) to the right (clockwise).  \n"
        << "                                                                 \n"
        << "At any point enter 'x' to exit the program or 'i' to display instructions." << endl;
} // end displayInstructions()



class Board {
public:
    char positions[6][6]; //This declares 2d array 6x6

    Board(); //This is the default constructor and will assign each board position with '.'

    void displayBoard(); //function used to display the board.

    void playGame(char rows, char cols, char playertoMove, char quad, char rotate); //It will receive the user input, and place the marks on the board.

    void boardRotation(char quad, char rotate); //These function rotates the quadrant.
    void rotationR(char quad, char rotate);
    void rotationL(char quad, char rotate);

    void errorMsg(int errorCheck); // this displays the error message if the error is detected.
    int errorCheck(char rows, char cols, char quad, char rotate); //It detects the error.

    //below functions are used to check if the win conditions were met.
    void winCondition();
    int winHorizontal();
    int winVertical();
    int winDiagonal(); //found 3 different diagonal cases
    int Diag1();
    int Diag2();
    int Diag3();

private:
    int counter = 1; //This will track which turn the user is on.
};

Board::Board() {//This will assign each board position with '.' using for loop. the default constructor.
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            positions[i][j] = '.';
        }
    }
}


void Board::displayBoard() { //Simple displaying the board function. Made up with the while and for loop with if-else statement
    int row = 0;
    int col = 0;
    char letter = 'A';
    cout << endl;
    cout << setfill(' ') << setw(5) << "1" << setfill(' ') << setw(4) << "2" << setfill(' ') << setw(4) << "3" << setfill(' ') << setw(4)
        << "4" << setfill(' ') << setw(4) << "5" << setfill(' ') << setw(4) << "6" << "   " << endl;
    cout << setfill(' ') << setw(3) << "1" << setfill('-') << setw(24) << "2" << endl;


    while (row < 6) {
        cout << letter << " | ";
        for (col = 0; col < 6; col++) {
            if (col == 2 || col == 5) {
                cout << positions[row][col] << " | ";
            }
            else {
                cout << positions[row][col] << "   ";
            }

        }
        cout << letter;

        if (row == 2) {
            cout << endl << setfill(' ') << setw(3) << "|" << setfill('-') << setw(12) << "+" << setfill('-') << setw(12) << "|";
        }
        if (row != 2 && row != 5) {
            cout << endl << "  |           |           | ";
        }

        cout << endl;
        row++;
        letter++;
    }
    cout << setfill(' ') << setw(3) << "3" << setfill('-') << setw(24) << "4" << endl;
    cout << setfill(' ') << setw(5) << "1" << setfill(' ') << setw(4) << "2" << setfill(' ') << setw(4) << "3" << setfill(' ') << setw(4)
        << "4" << setfill(' ') << setw(4) << "5" << setfill(' ') << setw(4) << "6" << "   " << endl;
}

//It receives the input from the user, and determines where to place the marker and which quadrant to rotate.
void Board::playGame(char rows, char cols, char playertoMove, char quad, char rotate) {
    rows = tolower(rows);
    rotate = tolower(rotate);
    int intRows = rows - 'a'; //This was given from the piazza, which makes the character value to int value.
    int intCols = cols - '1'; //Same as above.
    positions[intRows][intCols] = playertoMove; //places either X or O on the board.
    boardRotation(quad, rotate); //Once the mark is placed on the board, it rotates the quadrant. 
}

//This function will rotate the quadrant.
void Board::boardRotation(char quad, char rotate) { //receives the input from the user which quadrant to rotate which direction.
    //the rotate is already lowered in the function palyGame, therefore did not have to repeat tolower/toupper rotate.
    // r indicates right, l indicates left.
    rotationR(quad, rotate);
    rotationL(quad, rotate);
}

//Right rotation
void Board::rotationR(char quad, char rotate) {
    if (rotate == 'r') {
        if (quad == '1') {
            char temp = positions[0][0];
            positions[0][0] = positions[2][0];
            positions[2][0] = positions[2][2];
            positions[2][2] = positions[0][2];
            positions[0][2] = temp;
            temp = positions[0][1];
            positions[0][1] = positions[1][0];
            positions[1][0] = positions[2][1];
            positions[2][1] = positions[1][2];
            positions[1][2] = temp;
        }
        else if (quad == '2') {
            char temp = positions[0][3];
            positions[0][3] = positions[2][3];
            positions[2][3] = positions[2][5];
            positions[2][5] = positions[0][5];
            positions[0][5] = temp;
            temp = positions[0][4];
            positions[0][4] = positions[1][3];
            positions[1][3] = positions[2][4];
            positions[2][4] = positions[1][5];
            positions[1][5] = temp;
        }
        else if (quad == '3') {
            char temp = positions[3][0];
            positions[3][0] = positions[5][0];
            positions[5][0] = positions[5][2];
            positions[5][2] = positions[3][2];
            positions[3][2] = temp;
            temp = positions[3][1];
            positions[3][1] = positions[4][0];
            positions[4][0] = positions[5][1];
            positions[5][1] = positions[4][2];
            positions[4][2] = temp;
        }
        else if (quad == '4') {
            char temp = positions[3][3];
            positions[3][3] = positions[5][3];
            positions[5][3] = positions[5][5];
            positions[5][5] = positions[3][5];
            positions[3][5] = temp;
            temp = positions[3][4];
            positions[3][4] = positions[4][3];
            positions[4][3] = positions[5][4];
            positions[5][4] = positions[4][5];
            positions[4][5] = temp;
        }
    }
}

//Left rotation
void Board::rotationL(char quad, char rotate) {
    if (rotate == 'l') {
        if (quad == '1') {
            char temp = positions[0][0];
            positions[0][0] = positions[0][2];
            positions[0][2] = positions[2][2];
            positions[2][2] = positions[2][0];
            positions[2][0] = temp;
            temp = positions[0][1];
            positions[0][1] = positions[1][2];
            positions[1][2] = positions[2][1];
            positions[2][1] = positions[1][0];
            positions[1][0] = temp;
        }
        else if (quad == '2') {
            char temp = positions[0][3];
            positions[0][3] = positions[0][5];
            positions[0][5] = positions[2][5];
            positions[2][5] = positions[2][3];
            positions[2][3] = temp;
            temp = positions[0][4];
            positions[0][4] = positions[1][5];
            positions[1][5] = positions[2][4];
            positions[2][4] = positions[1][3];
            positions[1][3] = temp;
        }
        else if (quad == '3') {
            char temp = positions[3][0];
            positions[3][0] = positions[3][2];
            positions[3][2] = positions[5][2];
            positions[5][2] = positions[5][0];
            positions[5][0] = temp;
            temp = positions[3][1];
            positions[3][1] = positions[4][2];
            positions[4][2] = positions[5][1];
            positions[5][1] = positions[4][0];
            positions[4][0] = temp;
        }
        else if (quad == '4') {
            char temp = positions[3][3];
            positions[3][3] = positions[3][5];
            positions[3][5] = positions[5][5];
            positions[5][5] = positions[5][3];
            positions[5][3] = temp;
            temp = positions[3][4];
            positions[3][4] = positions[4][5];
            positions[4][5] = positions[5][4];
            positions[5][4] = positions[4][3];
            positions[4][3] = temp;
        }
    }
}

//This is the error checking function. It detects the error with the given input from the user.
int Board::errorCheck(char rows, char cols, char quad, char rotate) {
    rows = tolower(rows);
    rotate = tolower(rotate);
    int intRows = rows - 'a';
    int intCols = cols - '1';

    if (rows >= 'a' && rows <= 'f') { //The first case is when the user gave the wrong row. which is not in (A~F) range.
        if (positions[intRows][intCols] != '.') { //This gives the error# 2if the position is already occuipied.
            return 2;
        }
        else if (!(cols >= '1' && cols <= '6')) { //gives the error# 4 if it goes beyond the column range which is (1~6)
            return 4;
        }
        else if (!(quad >= '1' && quad <= '4')) { //gives the error# 5if it goes beyond the quadrant range which is (1~4)
            return 5;
        }
        else if (!(rotate == 'l' || rotate == 'r')) { //gives the error# 6 if it tries to rotate in the weird direction other than right or left.
            return 6;
        }
        else {
            return 1;
        }
    }
    else if (!(rows >= 'a' && rows <= 'f')) { //if the row input is beyond (A~F) range, it gives the error# 3
        return 3;
    }
    return 0;
}

//It displays the error message.
void Board::errorMsg(int errorCheck) {
    switch (errorCheck) {
    case 1:
        break; //if no error was detected, nothing happens
    case 2:
        cout << "   *** That board location is already taken.  Please retry.\n";
        break; //if the error # 2 is detected
    case 3:
        cout << "    *** Invalid move row.  Please retry.\n";
        break; //if the error # 3 is detected
    case 4:
        cout << "    *** Invalid move column.  Please retry.\n";
        break; // if the error # 4 is detected
    case 5:
        cout << "    *** Selected quadrant is invalid.  Please retry.\n";
        break; // if the error # 5 is detectedd.
    case 6:
        cout << "    *** Quadrant rotation direction is invalid.  Please retry.\n";
        break; // if the rror # 6 is detected.
    }

}

void Board::winCondition() { //This determines the win condition.
    //I used 3 int functions. each returns 3 if the X made the win condition, and 2 if the O made the win condtion.
    //If both user made the win condition, it will return 3 and 2 which makes 5. 
    if ((winHorizontal() + winVertical() + winDiagonal()) == 5) {
        cout << "     ***Both X and O have won. Game is a tie.";
        displayBoard();
        cout << "Thanks for playing.  Exiting... ";
        exit(0);
    }

    if ((winHorizontal() + winVertical() + winDiagonal()) == 3) {
        cout << "     *** X has won the game! ";
        displayBoard();
        cout << "Thanks for playing.  Exiting... ";
        exit(0);
    }

    if ((winHorizontal() + winVertical() + winDiagonal()) == 2) {
        cout << "     *** O has won the game! ";
        displayBoard();
        cout << "Thanks for playing.  Exiting... ";
        exit(0);
    }
}

int Board::winHorizontal() { //This will check for the horizontal win condtion.
    int winCounter = 0;
    int Xcounter = 0;
    int Ocounter = 0;

    for (int j = 0; j < 6; j++) {
        Xcounter = 0;
        Ocounter = 0;
        for (int i = 0; i < 6; i++) {
            if (positions[j][i] == 'X') { //If the X is found 5 times returns 3
                Xcounter++;
                if (Xcounter == 5) {
                    winCounter = 3;
                    break;
                }
            }
            if (positions[j][i] == 'O') {//If the O is found 5 times..
                Ocounter++;
                if (Ocounter == 5) {
                    winCounter = 2;
                    break;
                }
            }
        }
    }
    return winCounter; // when the counter did not make 5 nothing happens.

}

int Board::winVertical() { //same as the horizontal one.
    int winCounter = 0;
    int Ocounter = 0;
    int Xcounter = 0;

    for (int i = 0; i < 6; i++) {
        Xcounter = 0;
        Ocounter = 0;
        for (int j = 0; j < 6; j++) {
            if (positions[j][i] == 'X') {
                Xcounter++;
                if (Xcounter == 5) {
                    winCounter = 3;
                    return winCounter;
                    break;
                }
            }
            if (positions[j][i] == 'O') {
                Ocounter++;
                if (Ocounter == 5) {
                    winCounter = 2;
                    return winCounter;
                    break;
                }
            }
        }
    }
    return winCounter;
}

int Board::winDiagonal() { //This checks if any diagonal cases were met during the win condition check.
    int winCounter = 0;
    if (Diag1() == 3 || Diag2() == 3 || Diag3() == 3) {
        winCounter = 3;
        return winCounter;
    }
    if (Diag1() == 2 || Diag2() == 2 || Diag3() == 2) {
        winCounter = 2;
        return winCounter;
    }
    return winCounter;
}

int Board::Diag1() {//checks the diagonal case from A 1 and 6 corner.
    int Xcounter = 0;
    int Xcounter2 = 0;
    int Ocounter = 0;
    int Ocounter2 = 0;
    int winCounter = 0;

    for (int i = 0; i < 6; i++) {
        if (positions[i][i] == 'X') {
            Xcounter++;
        }
        else if (positions[i][5 - i] == 'X') {
            Xcounter2++;
        }
    }
    for (int i = 0; i < 6; i++) {
        if (positions[i][i] == 'O') {
            Ocounter++;
        }

        else if (positions[i][5 - i] == 'O') {
            Ocounter2++;
        }
    }

    if (Xcounter == 5 || Xcounter2 == 5) {
        winCounter = 3;
        return winCounter;
    }
    if (Ocounter == 5 || Ocounter2 == 5) {
        winCounter = 2;
        return winCounter;
    }
    return winCounter;
}

int Board::Diag2() {//Checks the diagonal win case from B1 and B6 corner
    int Xcounter = 1;
    int Xcounter2 = 1;
    int Ocounter = 1;
    int Ocounter2 = 1;
    int winCounter = 1;

    for (int i = 0; i < 6; i++) {
        if (positions[1 + i][i + 1] == 'X') {
            Xcounter++;
        }
        else if (positions[i + 1][5 - i] == 'X') {
            Xcounter2++;
        }
    }
    for (int i = 0; i < 6; i++) {

        if (positions[1 + i][i + 1] == 'O') {
            Ocounter++;
        }

        else if (positions[i + 1][5 - i] == 'O') {
            Ocounter2++;
        }
    }

    if (Xcounter == 5 || Xcounter2 == 5) {
        winCounter = 3;
        return winCounter;
    }
    if (Ocounter == 5 || Ocounter2 == 5) {
        winCounter = 2;
        return winCounter;
    }

    return winCounter;
}

int Board::Diag3() {//Checks the diagonal win case from E1 and E6 corner.
    int Xcounter = 0;
    int Xcounter2 = 0;
    int Ocounter = 0;
    int Ocounter2 = 0;
    int winCounter = 0;

    for (int i = 0; i < 6; i++) {
        if (positions[4 - i][i] == 'X') {
            Xcounter++;
        }
        else if (positions[4 - i][5 - i] == 'X') {
            Xcounter2++;
        }
    }
    for (int i = 0; i < 6; i++) {
        if (positions[4 - i][i] == 'O') {
            Ocounter++;
        }

        else if (positions[4 - i][5 - i] == 'O') {
            Ocounter2++;
        }
    }

    if (Xcounter == 5 || Xcounter2 == 5) {
        winCounter = 3;
        return winCounter;
    }
    if (Ocounter == 5 || Ocounter2 == 5) {
        winCounter = 2;
        return winCounter;
    }

    return winCounter;
}


class Node {
public:
    char oldPlayer;
    int lastCount;
    Board oldBoard;
    Node* pNext;
};

void displayList(Node* pTemp) {
    cout << "List of moveNumber:playerToMove is ";
    while (pTemp != NULL) {
        cout << pTemp->lastCount << ":" << pTemp->oldPlayer;
        if (pTemp->pNext != NULL) {
            cout << "->";
        }
        pTemp = pTemp->pNext;
    }
    cout << endl;
}

void prependNode(Node*& pHead, int counter, char playerToMove, Board theBoard) {
    Node* pTemp = new Node;

    pTemp->lastCount = counter;
    pTemp->oldPlayer = playerToMove;
    pTemp->oldBoard = theBoard;
    pTemp->pNext = pHead;
    pHead = pTemp;
}

void deleteNode(Node*& pHead, int &counter, char &playerToMove, Board &theBoard) {
    if (pHead->pNext == NULL) {
        cout << "*** You cannot undo past the beginning of the game.  Please retry. ***" << endl;
    }
    else {
        cout << "* Undoing move * " << endl;
        Node* pTemp = pHead;
        pHead = pHead->pNext;
        delete pTemp;

        counter = pHead->lastCount;
        playerToMove = pHead->oldPlayer;
        theBoard = pHead->oldBoard;
    }
}

//-------------------------------------------------------------------------------------
int main() {
    char quad = 'a';
    char rows = 'b';
    char cols = 'c';
    char rotate = 'd'; //This will collect each input from the user.
    int counter = 1;

    char playertoMove = 'X'; // The user's mark
    char otherPlayer = 'O'; // The other user's mark

    Board theBoard;            // Create the board as an instance of the Board class
    Node* pHead = NULL;
    prependNode(pHead, counter, playertoMove, theBoard);

    welcomeMessage();          // generates the welcome message for the user    prependNode(pHead, counter, playertoMove);
    while (counter <= 36) { //when the board is filled up with the 'X's and 'O's, it will stop even if the win condition was not met.
        theBoard.displayBoard();
        displayList(pHead);
        cout << counter << ". Enter row, column, quadrant, direction for " << playertoMove << ":";
        cin >> rows;

        //the first input, which is the rows, will determine if the user wants to display the instruction, or exit the program. as well as the rows for the game.
        if (tolower(rows) == 'x') {
            cout << "Exiting program...";
            exit(0);
            break;
        }

        if (tolower(rows) == 'u') {
            deleteNode(pHead, counter, playertoMove, theBoard);
            continue;
        }
        if (tolower(rows) == 'i') {
            displayInstructions();
            continue; //goes back once the instruction is shwon.
        }

        cin >> cols >> quad >> rotate; //Getting the input for the columns, quadrant, and rotation direction.

        //Error checking is needed befroe the move is made.
        if (theBoard.errorCheck(rows, cols, quad, rotate) != 1) {
            theBoard.errorMsg(theBoard.errorCheck(rows, cols, quad, rotate));
            continue; //if the error is detected, it goes back to the function and not increase the counter
        }

        theBoard.playGame(rows, cols, playertoMove, quad, rotate); //if the error was not deteced, the player makes the move.
        theBoard.winCondition(); //After the user makes the move, it checks if any win condition is met. for both users. If any line with 5 same character is made, whoever the marker indicated, wins the game.
        counter++;
        if (playertoMove == 'X') {
            playertoMove = otherPlayer;
        }
        else {
            playertoMove = 'X';
        }

        prependNode(pHead, counter, playertoMove, theBoard);

    }

    if (counter > 36) { //if the counter goes beyond 36, the program terminates with a tie.
        cout << "     *** No one has won.  Game is a tie.\n";
        theBoard.displayBoard();
        cout << "Thanks for playing. Exiting...";
        exit(0);
    }

    return 0;

} // end main()
