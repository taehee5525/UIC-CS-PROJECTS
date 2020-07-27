 /* ----------------------------------------------------------- 
    Program 2: Cuatro 
    
    Class: CS 141, Spring 2020.  Tues 3pm lab
    System: Zybooks
    Author: Tae Hee Park

         -----------------------------------------------------------
  */
#include <iostream>   // for cin and cout
#include <iomanip>    // for setw()
#include <cctype>     // for toupper()
#include <string>
using namespace std;  // so that we don't need to preface every cin and cout with std::

// Global variables to represent the 16 board pieces and C++ strings representing
// the pieces that have not yet been played.  Since these are global they don't
// need to be passed as parameters to functions, and are shared over the entire program.
// Normally global variables will not be allowed.
char p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16;
string upperRowPiecesToPlay = "OO/CC  II/ZZ";
string lowerRowPiecesToPlay = "oo/cc  ii/zz";


//-------------------------------------------------------------------------------------
void displayInstructions()
{
	cout << "Welcome to the game of Cuatro, where you try to complete a set      \n"
		 << "of four pieces that are alike.  Players take turns making moves.    \n"
		 << "On each move your OPPONENT chooses the piece, then YOU get to       \n"
		 << "place it on the board.  If you create a set of four alike when      \n"
		 << "you place your piece, then you win!       \n"
		 << "\n"
		 << "A set of four alike can be completed by using four all upper (or all\n"
		 << "lower) case characters, four all vowels (or all consonants), or four\n"
		 << "all curved (or all straight-lined). Curved letters are 'O' and 'C'\n"
		 << "(upper or lower), and straight-line letters are 'I' and 'Z' (upper or\n"
		 << "lower). Groups of four can be created in a row, column, diagonal, or\n"
		 << "corner quadrant.\n"
		 << "\n"
		 << "When prompted for input you may also enter 'x' or 'X' to exit." << endl;
}// end displayInstructions()


// You should have lots more functions here.
void displayBoard() // this function will make the board 
{
	cout << endl;
	cout << "     " << "---------" << "    " << "Square #" << endl;
	cout << setfill(' ') << setw(5) << "|" << " " << p1 << " " << p2 << " " << p3 << " " << p4 << " " << "|"
		 << "  " << "1" << "  2" << "  3" << "  4" << endl;
	cout << setfill(' ') << setw(5) << "|" << " " << p5 << " " << p6 << " " << p7 << " " << p8 << " " << "|"
		 << "  " << "5" << "  6" << "  7" << "  8" << endl;
	cout << setfill(' ') << setw(5) << "|" << " " << p9 << " " << p10 << " " << p11 << " " << p12 << " " << "|"
		 << "  " << "9" << " 10" << " 11" << " 12" << endl;
	cout << setfill(' ') << setw(5) << "|" << " " << p13 << " " << p14 << " " << p15 << " " << p16 << " " << "|"
		 << " " << "13" << " 14" << " 15" << " 16" << endl;
	cout << "     "  << "---------" << endl;
	cout << "     " << "Pieces:" << "      " << "Curved Straight" << endl;
	
	/* Since the upper and lower row pieces are declared outside the function (the global variables), instead of writing it down
	I can simply say upperRowPiecesToPlay and lowerRowPiecesToPlay. */
	
	cout << setfill(' ') << setw(11+7) << "Upper: " << " " << upperRowPiecesToPlay << endl;
	cout << setfill(' ') << setw(11+6) << "Lower:" << "  " << lowerRowPiecesToPlay << endl; 
	cout << "                  " << "Vowel/Consonant" << endl;
}

bool invalidPiece(char letter) { // This will test if there are any letters left for users to play. If certain letters are not there anymore,
								 // the program will make the user to retry.
	if ((upperRowPiecesToPlay.compare(3,2, "  ") == 0) && (letter == 'C')) {
		return false;
	}
	else if ((upperRowPiecesToPlay.compare(0,2, "  ") == 0) && (letter == 'O')) {
		return false;
	}
	else if ((upperRowPiecesToPlay.compare(7,2, "  ") == 0) && (letter == 'I')) {
		return false;
	}
	else if ((upperRowPiecesToPlay.compare(10,2, "  ") == 0) && (letter == 'Z')){
		return false;
	}
	else if ((lowerRowPiecesToPlay.compare(3,2, "  ") == 0) && (letter == 'c')) {
		return false;
	}
	else if ((lowerRowPiecesToPlay.compare(0,2, "  ") == 0) && (letter == 'o')) {
		return false;
	}
	else if ((lowerRowPiecesToPlay.compare(7,2, "  ") == 0) && (letter == 'i')) {
		return false;
	}
	else if ((lowerRowPiecesToPlay.compare(10,2, "  ") == 0) && (letter == 'z')) {
		return false;
	}
	else {
		return true;
	}
}

bool invalidDestination (int position) { //This function is checking if the destination is occupied. 
	switch(position) {
		case 1:
			if (p1 != '.') {
				return true;
			}
			break;
		case 2:
			if (p2 != '.') {
				return true;
			}
			break;
		case 3:
			if (p3 != '.') {
				return true;
			}
			break;
		case 4:
			if (p4 != '.') {
				return true;
			}
			break;
		case 5:
			if (p5 != '.'){
				return true;
			}
			break;
		case 6: 
			if (p6 != '.'){
				return true;
			}
			break;
		case 7:
			if (p7 != '.'){
				return true;
			}
			break;
		case 8:
			if (p8 != '.'){
				return true;
			}
			break;
		case 9:
			if (p9 != '.'){
				return true;
			}
			break;
		case 10:
			if (p10 != '.'){
				return true;
			}
			break;
		case 11:
			if (p11 != '.'){
				return true;
			}
			break;
		case 12:
			if (p12 != '.'){
				return true;
			}
			break;
		case 13:
			if (p13 != '.'){
				return true;
			}
			break;
		case 14:
			if (p14 != '.'){
				return true;
			}
			break;
		case 15:
			if (p15 != '.'){
				return true;
			}
			break;
		case 16:
			if (p16 != '.'){
				return true;
			}
			break;
	}
	return false;
}

void checkingPiece(char letter){ //This function checks if there are any letters left to be used.
								// Prof. Reed helped me for this function.
	for (int i = 0; i < upperRowPiecesToPlay.length(); i++) {
		if (letter == upperRowPiecesToPlay.at(i)) {
			upperRowPiecesToPlay.at(i) = ' ';
			break;
		}
	}
	for (int i = 0; i < lowerRowPiecesToPlay.length(); i++) {
		if (letter == lowerRowPiecesToPlay.at(i)) {
			lowerRowPiecesToPlay.at(i) = ' ';
			break;
		}
	}
}

void moveBoard(char letter, int position) { //It places the letter on the board.
	switch(position) {
		case 1:
			p1 = letter;
			break;
		case 2:
			p2 = letter;
			break;
		case 3:
			p3 = letter;
			break;
		case 4:
			p4 = letter;
			break;
		case 5:
			p5 = letter;
			break;
		case 6:
			p6 = letter;
			break;
		case 7:
			p7 = letter;
			break;
		case 8:
			p8 = letter;
			break;
		case 9:
			p9 = letter;
			break;
		case 10:
			p10 = letter;
			break;
		case 11:
			p11 = letter;
			break;
		case 12:
			p12 = letter;
			break;
		case 13:
			p13 = letter;
			break;
		case 14:
			p14 = letter;
			break;
		case 15:
			p15 = letter;
			break;
		case 16:
			p16 = letter;
			break;
	}
}

// There are 4 functions. They are checking the win condition. 
int isStraight(char position1, char position2, char position3, char position4) { // It checks if the letters on the given positions are striaght letters.
	int win = 0;
	
	if ((position1 == 'I' || position1 == 'i' || position1 == 'Z' || position1 == 'z') &&
		(position2 == 'I' || position2 == 'i' || position2 == 'Z' || position2 == 'z') &&
		(position3 == 'I' || position3 == 'i' || position3 == 'Z' || position3 == 'z') &&
		(position4 == 'I' || position4 == 'i' || position4 == 'Z' || position4 == 'z')) {
			
		win =1;
	}
	return win;
}

int isCurve(char position1, char position2, char position3, char position4) { //It checks if the letters on the given positions are curved letters.
	int win =0;
	
	if ((position1 == 'C' || position1 == 'c' || position1 == 'O' || position1 == 'o') &&
		(position2 == 'C' || position2 == 'c' || position2 == 'O' || position2 == 'o') &&
		(position3 == 'C' || position3 == 'c' || position3 == 'O' || position3 == 'o') &&
		(position4 == 'C' || position4 == 'c' || position4 == 'O' || position4 == 'o')) {
			
		win =1;
	}
	return win;
}

int isVowel(char position1, char position2, char position3, char position4) { //It checks if the letters on the given positions are vowel.
	int win=0;
	
	if ((position1 == 'I' || position1 == 'i' || position1 == 'O' || position1 == 'o') &&
		(position2 == 'I' || position2 == 'i' || position2 == 'O' || position2 == 'o') &&
		(position3 == 'I' || position3 == 'i' || position3 == 'O' || position3 == 'o') &&
		(position4 == 'I' || position4 == 'i' || position4 == 'O' || position4 == 'o')) {

		win =1;
	}
	return win;
}

int isCons(char position1, char position2, char position3, char position4) { //It checks if the letters on the given positions are consonants.
	int win =0;
	
	if ((position1 == 'C' || position1 == 'c' || position1 == 'Z' || position1 == 'z') &&
		(position2 == 'C' || position2 == 'c' || position2 == 'Z' || position2 == 'z') &&
		(position3 == 'C' || position3 == 'c' || position3 == 'Z' || position3 == 'z') &&
		(position4 == 'C' || position4 == 'c' || position4 == 'Z' || position4 == 'z')) {
			
		win =1;
	}
	return win;
}

//This gathers the 6 different types of win conditions and generates boolean value, so that the function checkWin can determine whether the user won the game or not.
//TA helped me building this function. she taught me about isuppper & islower function. 
bool checkWinHelper(char position1, char position2, char position3, char position4) {
	if ((isupper(position1) && isupper(position2) && isupper(position3) && isupper(position4)) ||
		(islower(position1) && islower(position2) && islower(position3) && islower(position4)) ||
		(isStraight(position1, position2, position3, position4)) ||
		(isCurve(position1, position2, position3, position4)) ||
		(isVowel(position1, position2, position3, position4)) ||
		(isCons(position1, position2, position3, position4))) {
			
		return true;
	}
		
	else {
		return false;
	}
}

// This will let the user know if the user is won or not. It has all the types of possible winning sets.
bool checkWin() {
	if (checkWinHelper(p1, p2, p3, p4) || checkWinHelper(p5, p6, p7, p8) || checkWinHelper(p9, p10, p11, p12) || checkWinHelper (p13,p14,p15,p16) ||
		checkWinHelper(p1, p5, p9, p13) || checkWinHelper(p2, p6, p10, p14) || checkWinHelper(p3, p7, p11, p15) || checkWinHelper (p4, p8, p12, p16) ||
		checkWinHelper(p1, p6, p11, p16) || checkWinHelper(p4, p7, p10, p13) ||
		checkWinHelper(p1,p2,p5,p6) || checkWinHelper(p3,p4,p7,p8) || checkWinHelper(p9,p10, p13,p14) || checkWinHelper(p11, p12, p15,p16)) {
		return true;
		
	}
	else {
		return false;
	}
}

void displayError1 (int movingCounter, int currentPlayer) { //This generates an error message when the user tries to place a letter on already occupied position.
	if (currentPlayer ==1){
		cout << movingCounter << ". Player 1 enter piece, and Player 2 enter destination: " << endl;
		cout << "*** Sorry, that destination is occupied.  Please retry." <<endl;
	}
	else {
		cout << movingCounter <<". Player 2 enter piece, and Player 1 enter destination: " << endl;
		cout << "*** Sorry, that destination is occupied.  Please retry." << endl;
	}
}

void displayError2(int movingCounter, int currentPlayer) { // This generates the error if the user got the wrong input. Such as trying to get the third C. or
															// letters that are not used to play this game.
	if (currentPlayer ==1){
		cout << movingCounter << ". Player 1 enter piece, and Player 2 enter destination: " << endl;
		cout << "*** Sorry, that is an invalid piece.  Please retry." << endl;

	}
	else {
		cout << movingCounter << ". Player 2 enter piece, and Player 1 enter destination: " << endl;
		cout << "*** Sorry, that is an invalid piece.  Please retry." << endl;
	}
}

void displayError3(int movingCounter, int currentPlayer) { // This generates the error message if the destination is either less than 1 or larger than 16. 
	if (currentPlayer == 1) {
		cout << movingCounter << ". Player 1 enter piece, and Player 2 enter destination: " << endl;
		cout << "*** Sorry, that destination is invalid.  Please retry." << endl;
	}
	else {
		cout << movingCounter <<". Player 2 enter piece, and Player 1 enter destination: " << endl;
		cout << "*** Sorry, that destination is invalid.  Please retry." << endl;
	}
}

void displayEnding (char letter, int movingCounter, int currentPlayer) { //It generates the message if the user input is either X or x
	if ( letter == 'X' || letter == 'x') {
		if (currentPlayer == 1) {
			cout << movingCounter << ". Player 1 enter piece, and Player 2 enter destination: Exiting program..." << endl;
		}
		else {
			cout << movingCounter << ". Player 2 enter piece, and Player 1 enter destination: Exiting program..." << endl;
		}
	}
}

//-------------------------------------------------------------------------------------
int main()
{
	// Declare and initialize variables
	p1=p2=p3=p4=p5=p6=p7=p8=p9=p10=p11=p12=p13=p14=p15=p16='.'; // This assigns the position to dots. it will be used in the idsplay board
	int movingCounter = 1; //If the moving counter reaches 16, and the win condition is not met, the game will terminate automatically
	int position; //This variable will determine where the user wants to put the letter on.
	char letter; // This variable will determine what letter the user wants to put on the board.

	int currentPlayer = 1;

	displayInstructions();
	displayBoard(); // it recalls the displayBoard to be displayed.
	// Your main game-playing loop should go here.

	while( movingCounter <=16) { // Try to limit the turns so that the player does not have to play even after the board is filled.
		cin >> letter >> position;

		if (letter == 'X' || letter == 'x'){ // Needs to exit the program if it receives these two input
			break;
		}

		if (letter == 'C' || letter == 'c' || letter == 'O' || letter == 'o' || letter == 'I' || letter == 'i' || letter == 'Z' || letter == 'z') {
			if ((position > 0 && position < 17) && (invalidDestination(position))){ // This statement will display the error message if the destination is occuipied.
				displayError1(movingCounter, currentPlayer);
				displayBoard();
				continue;
			}
			else if (!invalidPiece(letter)) {//This checks if the user input is invalid or not. If the user tries to put the third letter, it will displays the error message.
				displayError2(movingCounter, currentPlayer);
				displayBoard();
				continue;
			}

			else if ((position > 0 && position < 17) && (!invalidDestination(position))) { //This is the condition where the user input the letter and the position right.
				checkingPiece(letter);													   // without any errors.
				moveBoard(letter, position); //This place the letters insdie the board.
				if (currentPlayer == 1) {
					cout << movingCounter << ". Player 1 enter piece, and Player 2 enter destination: ";
					currentPlayer++;
					displayBoard(); //It recalls the board so that the player can see the current board.
				}
				else if (currentPlayer == 2){
					cout << movingCounter << ". Player 2 enter piece, and Player 1 enter destination: ";
					currentPlayer--;
					displayBoard();
				}
				if (checkWin()) {
					cout << "***Player " << currentPlayer << " you won!" << endl;
					break;
				}
				movingCounter++;
			}
		
			else { // checking the error when the user got the right letter but wrong destination.
				displayError3(movingCounter, currentPlayer);
				displayBoard();
				continue;
			}
		}

		//checking the error when the user got the wrong letter. And display the error message.
		else if (position != 'C' || position != 'Z' || position != 'I' || position != 'O' || position != 'o' || position != 'c' || position != 'i' || position != 'z') {
			displayError2(movingCounter, currentPlayer);
			displayBoard();
			continue;
		}
	}
	
	// Getting message when the user input is either 'x' or 'X'
	displayEnding(letter, movingCounter, currentPlayer);
	return 0;
} // end main()
