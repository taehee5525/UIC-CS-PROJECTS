/*  textGenerator.cpp
    Tae Hee Park. tpark32
    University of Illinois at Chicago
    CS 251: Spring 2020
    Project#02 - Generating text
    This program takes the words from a text file.
    Then 'b' -> builds a map based off on N-gram theory.
    'p' -> prints out the map that is created.
    'g' -> generates a line of random text based off on user input.
    's' -> start over , 'x' -> exit the program.
 */

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "myrandom.h"  // This file contains a "random" function.

using namespace std;

typedef map<vector<string>, vector<string>> theMap;
typedef vector<string> vecStr;
// makes the code looks shorter and cleaner.

// Function prototypes. Explnations are on each function.
void inputFile(int &valueN, int &wordGen, string &fileName);
void getValues(int &valueN, int &wordGen);
int menuOption(int valueN, int wordGen, string &fileName);
void buildMap(theMap &myMap, int valueN, string fileName);
void buildHelper(theMap &myMap, vecStr &nMinusOne,
                vecStr &nthOne, string words);
void displayBuild(string fileName);
void printMap(theMap &myMap);
void printHelper(vecStr &firstVec, vecStr &secVec);
void genText(int wordGen, theMap &myMap);
void genHelper(vecStr &window, int &wordGen, theMap &myMap);

int main() {
    int valueN = 0;  // N-gram.
    int wordGen = 0;  // Amount of words.
    int pExit = 1;  // Exit condition.
    string fileName;

    while (pExit == 1) {
        cout << "Welcome to the Text Generator." << endl;
        cout << "This program makes random text based on a document." << endl;
        cout << "Input file name?  ";
        inputFile(valueN, wordGen, fileName);  // Check if file's open.
        pExit = menuOption(valueN, wordGen, fileName);  // The main function.
    }
    return 0;
}

// This will check if the file is open. Does not read what is inside.
void inputFile(int &valueN, int &wordGen, string &fileName) {
                // N value, words user wants to display, text file's name.
    cin >> fileName;
    ifstream inFile(fileName);

    while (!inFile.is_open()) {
        cout << "Invalid file, try again:  ";
        cin >> fileName;
        inFile.open(fileName);
    }

    getValues(valueN, wordGen);  // Gets the integer values.
    inFile.close();
    return;
}

// This function will store the integer data of user input.
void getValues(int &valueN, int &wordGen) {
    cout << "Value of N?  ";
    cin >> valueN;

    while (valueN <= 1) {
        cout << "N must be > 1, try again:  ";
        // Error condition
        cin >> valueN;
    }

    cout << "Total words you'd like to generate?  ";
    cin >> wordGen;

    while (wordGen < valueN) {
        cout << "Total words must be at least N, try again: ";
        // Error condition.
        cin >> wordGen;
    }
}

/*  The menu function. It reads the file and builds the map.
    Then, it prints out the map that is built.
    Then, menu 'g' would print out the generated random text.
    menu 's' does start over with clearing the map
    menu 'x' exits the function, exits the program.
*/
int menuOption(int valueN, int wordGen, string &fileName) {
                // N value, # of words user wants to display
                // the file name that user wants to load.
    theMap myMap;
    char menu;

    while (menu != 's' || menu != 'x') {
        cout << "Type b-build map, p-print map, ";
        cout << "g-generate text, s-start over, x-to exit: ";
        cin >> menu;

        if (menu == 'b') {
            displayBuild(fileName);
            buildMap(myMap, valueN, fileName);
            continue;
        } else if (menu == 'p') {
            printMap(myMap);
        } else if (menu == 'g') {
            genText(wordGen, myMap);
        } else if (menu == 's') {
            myMap.clear();
            return 1;
        } else if (menu == 'x') {
            return 0;
        }
    }
    /* When 'x', the exit condition becomes 0, then exits the program. */
    return 0;
}

// This displays the file what is "successfully" loaded.
void displayBuild(string fileName) {
    cout << "...Building map: " << fileName << "..." << endl;
    cout << endl;
}

// This builds the map and store them into myMap.
void buildMap(theMap &myMap, int valueN, string fileName) {
                // The main map which stores the 2 vector strings.
    vecStr firstNwords, nthOne;  // Stores the first N-1 words the Nth word.
    string words;  // Receive the strings from the file.
    int counter = 1;  // Tracker for N value.
    ifstream inFile(fileName);  // Opening the file

    while (counter < valueN) {  // Starts the file reading.
        inFile >> words;
        firstNwords.push_back(words);
        counter++;
    }
    vecStr nMinusOne = firstNwords;  // It will stroe the N-1 words.

    while (inFile >> words) {
        if (counter < valueN) {
            nMinusOne.push_back(words);
        } else if (counter == valueN) {
            buildHelper(myMap, nMinusOne, nthOne, words);  // Builds the map.
            counter = valueN-1;
        }
        counter++;
    }  // The file reading ends here.

    for (string word : firstNwords) {
        buildHelper(myMap, nMinusOne, nthOne, word);
        // Wraps around, and builds the map.
    }
    inFile.close();
}

// Helper function for the building map.
void buildHelper(theMap &myMap, vecStr &nMinusOne,
                vecStr &nthOne, string words) {
                // The main map which stores two vectors
                // The first one is for N-1 words second for nth
    nthOne.push_back(words);

    if (myMap.count(nMinusOne)) {  // If there's existing key update.
        nthOne = myMap[nMinusOne];
        // Retrieve the value from existing key.
        nthOne.push_back(words);
        myMap[nMinusOne] = nthOne;
    }  // If not, just add it to the map.

    myMap.emplace(nMinusOne, nthOne);
    nMinusOne.erase(nMinusOne.begin());
    // Removes the first string to proceed.
    nthOne.clear();
    nMinusOne.push_back(words);  // Takes the last word into N-1.
}

// Prints the N-gram words and Nth words separately.
void printMap(theMap &myMap) {
    for (auto a : myMap) {
        vecStr firstVec = a.first;  // The N-gram vector
        vecStr secVec = a.second;  // The Nth vector.
        printHelper(firstVec, secVec);
    }
}

// Heleper function for printing.
void printHelper(vecStr &firstVec, vecStr &secVec) {
    // The first one for the N-gram vector, second for Nth vector.
    int firstSize = firstVec.size();
    int secSize = secVec.size();

    cout << "{";
    for (int i =0; i < firstSize; i++) {
        if (i < firstSize-1) {
            cout << firstVec[i] << " ";
        } else {
            cout << firstVec[i] << "} ";  // Close when reached end
        }
    }

    cout << "-> {";
    for (int j =0; j <secSize; j++) {
        if (j < secSize-1) {
            cout << secVec[j] << " ";
        } else {
            cout << secVec[j] << "}" << endl;
        }
    }
}

// This code generates the random text.
// I received help from TA. on 17th of September.
void genText(int wordGen, theMap &myMap) {
    vector<vecStr> keys;
    // Stores the vector of vecStr from myMap.
    int randomIndex = randomInteger(0, myMap.size()-1);
    // The first "Random" index.

    for (auto elements : myMap) {
        keys.push_back(elements.first);
    }  // Gets the vectors from myMap to assign to keys.

    vecStr window = keys[randomIndex];
    // Each vecStr will be the "window" to find the value of myMap.
    cout << "...";
    genHelper(window, wordGen, myMap);  // Generates then prints out.
    cout << "..." << endl;
}

/*  Helper function of generating text.
    It generates the random text and prints out.
*/
void genHelper(vecStr &window, int &wordGen, theMap &myMap) {
    vecStr genLine;  // This will stroe the generated lines.
    int newIndex = 0;  // declartion of new random index.
    int winSize = window.size();
    // size of the window vector.
    int wordLength = wordGen - winSize;
    // Length of rest of the words need to be printed.

    for (int i =0; i< winSize; i++) {
            cout << window[i] << " ";
    }  // Prints out the first "key"

    for (int i =0; i< wordLength; i++) {
        genLine = myMap[window];
        // Then prints out the values of random index
        newIndex = randomInteger(0, genLine.size()-1);
        if (i <wordLength-1) {
            cout << genLine[newIndex] << " ";
        } else {
            cout << genLine[newIndex];
        }
        window.erase(window.begin());
        window.push_back(genLine[newIndex]);
    }  // Same algorithm as building map.
}
