/* main.cpp
 *
 * Author: Tae Hee Park, Kyle Inthabandith
 * CS 141, Spring 2020
 * Program 4: Two codes
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

void choiceMenu() {
	cout << "Your choice: ";
}

// Once the user decided to continue with the program, this message will appear.
void displayMenu() {
	cout << "Select from the following choices: " << endl;
	cout << setw(3) << "W Enter word or phrase to find, and display enclosing text " << endl;
	cout << setw(3) << "X Exit program" << endl;
}

//It will guide the user to enter a word or phrase. 
void displayWordMenu() {
	cout << "Enter word or phrase: ";
}

//It will display the second menu once the user enters w for the first menu
void displaySecondMenu() {
	cout << "Select from the following choices: " << endl;
	cout << " W  Enter word or phrase to find, and display enclosing text " << endl;
	cout << " P  Display previous text " << endl;
	cout << " F  Display following text " << endl;
	cout << " A  Display all occurrences of found word or phrase " << endl;
	cout << " X  Exit program " << endl;
}

//This will function make the string all lower cases. And return
string lowerCase(string& wordInputlower) {
	char w;

	for (int i = 0; i < wordInputlower.size(); i++) {
		w = wordInputlower[i];
		w = tolower(w);
		wordInputlower[i] = w;

	}
	return wordInputlower;
}

//This will make the whole constitution in lower cases. 
string lowerString(string theParagraph) {
	string s;
	char w;

	//Takes the paragraph line by line and store it into a string s
	for (int i = 0; i < theParagraph.size(); i++) {
		s = theParagraph;
	}

	// change each character inside the string to lower case, then assign it back to the string
	for (int j = 0; j < s.size(); j++) { 
		w = s[j];
		w = tolower(w);
		s[j] = w;
	}
	return s;
}

//It will find the first paragraph or the first line that contains the user input.
//Although, this function will not directly display the line, but returning the lineNumber, so that it can be received in the different function.
void searchConstittution(vector<string> constitutionLower, string wordInputlower, int& lineNumber) {
	for (lineNumber = 0; lineNumber < constitutionLower.size(); lineNumber++) {
		string s = constitutionLower[lineNumber];

		//-1 appears if and only if it cannot find the target. Since the purpose of this function is to find the first par/line, it needs to be stopped right after.
		if (s.find(wordInputlower) != -1) { 
			break;
		}
	}
}
//It will search the whole constitution and find all lines that contain the userInput.
void searchAll(vector<string> constitutionOriginal, vector<string> constitutionLower, string wordInputlower, int lineNumber) {
	for (lineNumber = 0; lineNumber < constitutionLower.size(); lineNumber++) {
		string s = constitutionLower[lineNumber];

		// just like the searchconstitution, but this time it will display all the lines that contain the phrase/word user entered.
		if (s.find(wordInputlower) != -1) {
			cout << "Line " << lineNumber << ": " << endl;
			cout << constitutionOriginal[lineNumber] << endl;
		}
	}
}

//Once the program reads the constitution and finds the line, this function will display the line
void displayConstitution(vector<string> constitutionOriginal, int lineNumber) {
	if (lineNumber < 251 && lineNumber >= 0) {
		cout << "Line " << lineNumber << ": " << endl;
		cout << constitutionOriginal[lineNumber] << endl;
	}
}

//This will have the program read the constitution and store them.
// I used the basic code to load the file from last program, which was given to us.
void readConstitution(vector<string> constitutionOriginal, string wordInputlower) {

	ifstream inStream;                 // Declare an input stream
	inStream.open("ConstitutionAndBillOfRights.txt");
	if (!inStream.is_open()) {
		cout << "Could not find ConstitutionAndBillOfRights.txt.  Exiting..." << endl;
		exit(-1);
	}

	string theParagraph; //It will get all those pargraphs from the constitution.
	vector<string> constitutionLower; //It will hold the constitution as the lower cases
	char menuChoice; //It will get the menu choice once the user tries to find a word or phrase
	string userInput; // It will hold the userInput for the second 'w' option
	int lineNumber = 0; // This will indciate the lineNumber which will be used to display the specific line

	while (getline(inStream, theParagraph)) { //Instead of the character 2d array which was used last time, I used vector 
											  // I chose to store the original constitution into the constitution.original vector, later it will be used to display the specific line
											  // Also, declared constitutionlower, which will be used to search the constitution.
		if (theParagraph.length() > 1) {
			constitutionOriginal.push_back(theParagraph);
			constitutionLower.push_back(lowerString(theParagraph));
		}
	}

	//It will search the whole constitution for the first time and display
	searchConstittution(constitutionLower, wordInputlower, lineNumber);
	displayConstitution(constitutionOriginal, lineNumber);

	//This while loop will be used to re-display the menuoptions and menu chocies.
	while (true) {
		displaySecondMenu();
		choiceMenu();
		cin >> menuChoice;

		if (menuChoice == 'X' || menuChoice == 'x') {
			cout << "Exiting program." << endl;
			break;
		}

		else if (menuChoice == 'P' || menuChoice == 'p') { //It will display the previous line
			lineNumber = lineNumber - 1;

			if (lineNumber >= 0) {
				cout << "Line " << lineNumber << ": " << endl;
				cout << constitutionOriginal[lineNumber] << endl;
				continue;
			}
			else if (lineNumber < 0) { //Error checking and then return the value as 0, so that it can be still at line 0
				cout << "There is no previous file contents." << endl;
				lineNumber = 0; //The linenumber is not supposed to become lower than 0, therefore, change it to 0 once it displays the error message.
				continue;
			}
		}

		else if (menuChoice == 'F' || menuChoice == 'f') { //It will display the following line
			lineNumber = lineNumber + 1;

			if (lineNumber >= 0 && lineNumber < constitutionOriginal.size()) {
				cout << "Line " << lineNumber << ": " << endl;
				cout << constitutionOriginal[lineNumber] << endl;
				continue;
			}
			else if (lineNumber >= constitutionOriginal.size()) { //Error checking and then return the value back to the last line, so that i can be still at the very last line.
				cout << "There is no following file contents." << endl;
				lineNumber = constitutionOriginal.size() - 1;
				continue;
			}
		}

		else if (menuChoice == 'A' || menuChoice == 'a') { //It will search for all lines that contain the user input
			searchAll(constitutionOriginal, constitutionLower, wordInputlower, lineNumber);
			continue;
		}

		else if (menuChoice == 'W' || menuChoice == 'w') { //lets the user to re-enter the word or phrase and display then going back to the function again.. 
			char carriageReturn = cin.get();
			displayWordMenu();
			getline(cin, userInput);
			lowerCase(userInput);
			searchConstittution(constitutionLower, userInput, lineNumber);
			displayConstitution(constitutionOriginal, lineNumber);
			continue;
		}

		else {
			break;
		}

	} //end of the while loop.

	inStream.close(); // close the file
} //end of the readconstitution function.


//This will be the one of the most important function which will get the word, or phrase and then proceed.
// I decided to declare two word input. one to lower the case and compare with the constitution, and one for display what the original user input was.
// Also, the constitutionOriginal will hold the constitution before I lower them. So that we can easily compare both of them, and display the original ones to get the credit.

void findWord() {
	string wordInputOriginal; //This will hold the original user input (phrase or a word)
	string wordInputlower; // This will hold the original input as the lower cases
	vector<string> constitutionOriginal; // I declared the vector string here to contain the constitution line by line

	displayWordMenu();

	getline(cin, wordInputOriginal); //Instead of fgets we used for last program, since we are using string, I used getline.
	wordInputlower = lowerCase(wordInputOriginal); //assign the user input with all lower cases to the wordInputlower.

	readConstitution(constitutionOriginal, wordInputlower); //It will compare both strings
}

// This will be the first menu option function which will determine whether the user wants to terminate the program or continue.
void menuOption(string userInput) {
	if (userInput == "X" || userInput == "x") {
		cout << "Exiting program." << endl;
		exit(0);
	}
	if (userInput == "W" || userInput == "w") {
		findWord();
	}
}

int main() {
	string userInput; // This will hold the user input.
	char carriageReturn; // We learned that we need to have carriage return to hold the 'enter' after the cin from the last program.

	displayMenu();

	choiceMenu();
	cin >> userInput;
	carriageReturn = cin.get(); //Taking the enter at the end so that later fgets can function without any problem.

	menuOption(userInput);

	return 0;
}
