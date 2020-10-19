// Application.cpp
// Tae Hee Park. tpark32
// University of Illinois at Chicago
// CS 251: Spring 2020
// Project #03 - Autocomplete.
// An application that reads the text file that user input.
// Gives two choices whether the user wants to try the regular search
// Or the creative search
// The creative search includes an error message.
// If it has no match, tells user to retry and go back to the search portion.
// It asks if the user wants to add to the previous string, and returns
// the search history, what the user had input, in the end.


#include <iostream>
#include "AutocompleteList.h"

using namespace std;
/* The function descriptions are above each function.*/
void startMsg(string &fileName, char &input);
void searchMsg();
void createMsg();
void searchS(string fileName);
void searchC(string fileName);
string checkHistory(string &searchHistory, string lookFor, int &counter);
void creativeS(AutocompleteList list, string &addHere);

int main() {
    string fileName;
    char input;
    string lookFor;

    startMsg(fileName, input);

    if (input == 's') {
        searchMsg();
        searchS(fileName);
    }

    if (input == 'c') {
        createMsg();
        searchC(fileName);
    }

    return 0;
}

// Reads the file, and check what the user wants to do.
void startMsg(string &fileName, char& input) {
    cout << "Enter filename: ";
    cin >> fileName;
    cout << "Enter s-search or c-creative search: ";
    cin >> input;
    char returnChar = ' ';
    returnChar = getchar();  // Captures the carriage return after the input.
}

// Prints out a welcome message for input 's'
void searchMsg() {
    cout << "Welcome!" << endl;
    cout << "Type your search below, press enter for autocomplete ";
    cout << "(# to stop)." << endl;
}

// Prints out a welcome message for input 'c'
void createMsg() {
    cout << "Welcome! This is my creative search" << endl;
    cout << "Type your search below, press enter for autocomplete " << endl;
    cout << "You can add to your previous search, and in the end" << endl;
    cout << "You can check your search history!" << endl;
    cout << "Press # to stop anytime!" << endl;
}

/* Reads the data from the text file that user previously entered
    Then prompts to the prefix instruction.
    the user gets to see the list of words that contain the prefix. */
void searchS(string fileName) {
    string lookFor;
    AutocompleteList list(fileName);

    while (true) {
        cout << "Search: ";
        getline(cin, lookFor, '\n');
        if (lookFor == "#") {
            break;
        }

        AutocompleteList list2 = list.allMatches(lookFor);
        list2.print();
    }
}
/* The creative search function. */
void searchC(string fileName) {
    string lookFor;
    string addHere;
    string searchHistory;
    int counter = 0;
    AutocompleteList list(fileName);
    
    while(true) {
        cout << "Search: ";
        getline(cin, lookFor, '\n');
        addHere = addHere + lookFor;  // Adds to the previous string.

        if (lookFor == "#") {
            break;
        }

        creativeS(list, addHere);
        // Does the search with many error  handling messages.
        searchHistory = checkHistory(searchHistory, lookFor, counter);
        // Updates the search history.
    }

    cout << "Here's your search History " << endl;
    cout << searchHistory << endl;
}
// This function tracks what the user has input.
string checkHistory(string &searchHistory, string lookFor, int &counter) {
    if (lookFor.length() == 0) {
        return searchHistory;
    }  // If the input has nothing, it returns an empty search histroy
    // Does not increment the counter.

    if (counter ==0) {
        counter++;
        return searchHistory = lookFor;
    }  // If the input was the first valid input
    // it returns the input by itself

    counter++;
    return searchHistory + ", " + lookFor;  // Otherwise it adds to the list.
}

void creativeS(AutocompleteList list, string &addHere) {
    char command;
    string empty;

    if (addHere.length() == 0) {
        cout << "Please enter a valid input" << endl;
        return;
    }  // The search only takes the valid input.

    if (list.numberOfMatches(addHere) == 0) {
        cout << "Sorry, no matches please try again." << endl;
        addHere = empty;
        return;
    }  // If nothing matches, it retunrs an empty string.

    AutocompleteList list2 = list.allMatches(addHere);
    list2.print();

    cout << "Do you want to add a letter or a word to your"
    << " previous search? (Y/N)";
    cin >> command;
    char returnChar = ' ';
    returnChar = getchar();  // Captures the carriage return after the input.

    if (tolower(command) == 'y') {
        return;  // If yes, return back without clearing the string.
    } else {
        cout << "Press # to exit. Ohterwise, keep searching!" << endl;
        addHere.clear();  // If no, then clears the sring.
    }
}
