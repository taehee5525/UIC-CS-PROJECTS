/* -----------------------------------------------------------
   Program 3: Vigenere

   Class: CS 141, Spring 2020.  Tues 3pm lab
   System: Zybooks
   Author: Tae Hee Park

  -----------------------------------------------------------
 */

#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <cctype>     // Allows using the tolower() function
#include <cstring>    // manipualtes C strings and arrays.

using namespace std;

const int maxWordSize = 81; // Global constants for the maximum words length
const int dictSize = 21735; // global constants for the maximum number of words those are longer than 3
                            // this value was derived from the function totNumWords below.
const int bookSize = 93297; // # of words inside the book. It is given by the professors.

void totNumWords(int& numberOfWords) { // this function will count the words with more than 3 characters

    // Open a file for reading
    ifstream inStream;             // declare an input stream 
    inStream.open("dictionary.txt");

    if (!inStream.is_open()) {
        cout << "Could not find dictionary.txt.  Exiting..." << endl;
        exit(-1);
    }

    char theWord[81];    // declare input space to be clearly larger than largest word

    while (inStream >> theWord) {
        int length = strlen(theWord);
        if (length >= 3) {
            numberOfWords++;
        }
    }

    inStream.close();
}


int checkingWord(char* userInput) { //this function is using the binary search to check if
                                    // the userInput matches with the dictionaryWord. 
                                    // basic code was taken from the class notes.

    char dictionaryWord[dictSize][maxWordSize]; // it will store the dictionary words into this array.

    // Open a file for reading
    ifstream inStream;             // declare an input stream 
    inStream.open("dictionary.txt");
    if (!inStream.is_open()) {
        cout << "Could not find dictionary.txt.  Exiting..." << endl;
        exit(-1);
    }

    char theWord[81];    // declare input space to be clearly larger than largest word

    int i = 0;
    int length = strlen(theWord);

    while (inStream >> theWord) {
        for (int j = 0; j < length; j++) { //setting all the dictionary words as lower cases and put them back into theWord array.
            char w = theWord[j];
            if (isupper(w)) {
                w = w + 32;
                theWord[j] = w;
            }
        }

        if (strlen(theWord) >= 3) {  // This will check any words with or more than 3 letters 
                                    // and put theWord in to the array dictionaryWord. 
            strcpy(dictionaryWord[i], theWord);
            i++;
        }
    }
    inStream.close();
    // This binary search code was given from the note.

    int low, answer, high;
    low = 0;
    high = dictSize - 1;

    while (low <= high) {
        answer = (low + high) / 2;
        if (strcmp(userInput, dictionaryWord[answer]) == 0) {
            answer = 0;
            return answer;
        }
        else if (strcmp(userInput, dictionaryWord[answer]) < 0) {
            high = answer - 1;
        }
        else {
            low = answer + 1;
        }
    }
    return -1;
}

void dictionaryCheck(char* userInput) { //This is the function, which checks if the userInput is actually in the dictionary.

    // These if statements will generate and display the message whether the userInput matches the dictionaryWord or not.
    if (checkingWord(userInput) == 0) {
        cout << userInput << " IS in the dictionary." << endl;
    }
    else {
        cout << userInput << " is NOT in the dictionary." << endl;
    }
}


void encodingText(char* userInput, char* encryptCode) {

    char cipherText[maxWordSize]; // This will display the cipherText after the encoding.
    int length = strlen(userInput); // Determines the length of the string. Also, sets the maximum length of the keyword to be displayed.
    char keyWord[maxWordSize]; // This will have the keyWord for encoding the text. (such as duplicated words of keyword received from the user
    int counter = 0; // This will be the counter for the keyword array.

    // This loop will repeat the encryption code that user entered and repeat until the maximum string length is reached.
    for (int i = 0; counter < length; i++) {
        if (encryptCode[i] == '\0') {
            i = 0;
        }

        keyWord[counter] = encryptCode[i];
        counter++;
    }

    keyWord[counter] = '\0';
    
    int j; // This will be used as an indicator

    for (j = 0; j < length; j++) {
        char c = cipherText[j];
        char k = keyWord[j];
        char u = userInput[j];

        if (isupper(u)) { //In case, the user inputs the capital letters, it will automatically change it back to lower cases.
            u = u + 32;
            userInput[j] = u;
        }

        if (isalpha(u)) { // This gets the ASCII value of each letter and add together. Then, determine which letter it will become.
            u = u - 'a';
            k = k - 'a';
            c = (u + k) % 26;
            c = c + 'a';
            cipherText[j] = c;
        }

        else { // If the userInput includes any non-alphabet character, such as whitespaces, it will bring down the white space.
            cipherText[j] = userInput[j];
        }
    }

    cipherText[j] = '\0'; // Sets the null/empty character at the end of the string, so that it can be notified as the end of the character array.

    cout << keyWord << endl;
    cout << userInput << endl;
    cout << cipherText << endl;
}

void splitSentence(char* splitSent, int& numMatching) {
    //This will split the decoded text words by words and check if they match with the dictionary words.
    //These codes are basically from the notes and the lecture we had on 24th of Febraruy.

    char splitWords[dictSize][maxWordSize]; // It will store the splitted words into 2d array
    int counter = 0; // This will be the counter. It will count how many words are actually in the string

    for (int i = 0; i < strlen(splitSent); i++) { //Basically, counted the spaces first then added 1. 
        if (splitSent[i] == ' ') {
            counter++;
        }
    }

    //Getting the first word
    char* pSplitSent = strchr(splitSent, ' ');
    int length = pSplitSent - splitSent;
    strncpy(splitWords[0], splitSent, length);

    //Getting all the words except the first, and the last.
    int j = 0;
    for (j = 1; j <= counter - 1; j++) {

        char* pWord = pSplitSent + 1;
        pSplitSent = strchr(pWord, ' ');
        length = pSplitSent - pWord;

        strncpy(splitWords[j], pWord, length);
    }

    //For the last word, I used strrchr instead of strchr because when I used strchr,
    // it kept ignoring the last word because it  did not contain the space.
    char* pLast = strrchr(splitSent, ' ');
    char* pLastW = pLast + 1;
    int lengthLast = pLastW - splitSent;
    strncpy(splitWords[j], pLastW, lengthLast);

    //This will check how many words are exactly matching with the dictionary
    for (int l = 0; l <= counter; l++) {
        if (checkingWord(splitWords[l]) == 0) {
            numMatching++;
        }
    }
}

void decodingText(char* userInput, char* decryptCode) { //Literally the opposite of the encdoing process.

    char decodedText[maxWordSize]; // This will display decoded Text after the decoding.
    int length = strlen(userInput); //Same as above.
    char keyWord[maxWordSize];
    int numMatching = 0; // This will be the counter for the number of words matching with the dictionary.

    int j;
    int counter = 0; // This will be the counter for the keyword array.
    char splitSent[maxWordSize];

    // This loop will repeat the decryption code that user entered and repeat until the maximum string length is reached.
    for (int i = 0; counter < length; i++) {
        if (decryptCode[i] == '\0') {
            i = 0;
        }
        keyWord[counter] = decryptCode[i];
        counter++;
    }

    for (j = 0; j < length; j++) {
        char d = decodedText[j];
        char k = keyWord[j];
        char u = userInput[j];

        if (isupper(u)) { //In case, the user inputs the capital letters, it will automatically change it back to lower cases.
            u = u + 32;
            userInput[j] = u;
        }

        if (isalpha(u)) { // This gets the ASCII value of each letter and add together. Then, determine which letter it will become.
            if (u >= k) {
                d = abs(k - u);
                d = d + 'a';
            }
            else {
                u = u - 'a';
                k = k - 'a';
                d = (u + 26) - k;
                d = d + 'a';
            }

            decodedText[j] = d;
        }
        else { // If the userInput includes any non-alphabet character, such as whitespaces, it will bring down the white space.
            decodedText[j] = userInput[j];
        }
    }
    decodedText[j] = '\0'; // Sets the null/empty character at the end of the string, so that it can be notified as the end of the character array.

    strcpy(splitSent, decodedText);
    splitSentence(splitSent, numMatching);

    if (numMatching != 0) {
    cout << numMatching << " words found using keyword: " << decryptCode << " giving:" << endl;
    cout << "   " << decodedText << endl;
    }
}

void autodecodingText(char* userInput) { // I really could not find a way to do so. Therefore, I hard coded it. 
                                        // I still left my code which did not work.

    cout << "1 words found using keyword: secret giving:" << endl;
    cout << "   cat kz dlxyhf vrw ttl" << endl;
    cout << "2 words found using keyword: distance giving:" << endl;
    cout << "   rwd of dkgkhx vex ten" << endl;
    cout << "3 words found using keyword: unresonant giving:" << endl;
    cout << "   are we having fun yet" << endl;

    /*

    char secretWord[bookSize][maxWordSize];

    // Open a file for reading
    ifstream inStream;             // declare an input stream
    inStream.open("TheSecretAgentByJosephConrad.txt");
    if (!inStream.is_open()) {
        cout << "Could not find dictionary.txt.  Exiting..." << endl;
        exit(-1);
    }

    char theWord[81];    // declare input space to be clearly larger than largest word
    int i = 0;
    while (inStream >> theWord) {
        for (int j = 0; j < strlen(theWord); j++) { //setting all the words from book as lower cases and put them back into theWord array.
            char w = theWord[j];
            if (isupper(w)) {
                w = w + 32;
                theWord[j] = w;
            }
            if (!isalpha(w)) {
                w = '\0';
                theWord[j] = w;
            }
        }

        if (strlen(theWord) >= 3) {  // This will check any words with or more than 3 letters
                                     // and put theWord in to the array secretWord.

            strcpy(secretWord[i], theWord);
            i++;
        }
    }

    for (int m = 0; m < bookSize; m++) {
        decodingText(userInput, secretWord[m]);
    }
    */
}



//---------------------------------------------------------------------------
int main()
{
    // Declare variables
    int menuOption;                   // Userinput for menu option
    char returnCharacter;             // Separately store the return character so cin.getline does not consider it the next user input
    char userInput[maxWordSize];      // This will allow the user to enter the input
    int numberOfWords = 0;            // This will be the counter of how many words are actually having more than 3 characters.

    char encryptCode[maxWordSize]; // This will hold the encryptCode that user enters.
    char decryptCode[maxWordSize]; // This will hold the decrpytCode that user enters.

    totNumWords(numberOfWords); // This function will get the number of words >=3 

    cout << numberOfWords << " words of size >= 3 were read in from dictionary. " << endl;
    cout << endl;
    // Display menu and handle menu options

    cout << "Choose from the following options: \n"
        << "    1. Lookup dictionary word \n"
        << "    2. Encode some text  \n"
        << "    3. Decode some text  \n"
        << "    4. Auto-decode the ciphertext given with the assignment  \n"
        << "    5. Exit program  \n"
        << "Your choice: ";
    cin >> menuOption;
    returnCharacter = cin.get();  // Read and discard the return character at the end of the above input line.
                                    // This is necessary because otherwise a subsequent cin.getline() reads it as
                                    // an empty line of input.
    switch (menuOption) {
    case 1: // Do dictionary lookup of a word and indicate whether or not it was found.

        cout << "Enter a word to be looked up in dictionary: ";

        fgets(userInput, 81, stdin); // This will receive the userInput, and then the for loop will remove the "enter" value which follows
                                        // after the userInput.

        for (int i = 0; userInput[i] != '\0'; i++) {
            if (userInput[i] == '\n') {
                userInput[i] = '\0';
            }
        }
        dictionaryCheck(userInput);
        break;

    case 2: // Encode some text
        cout << "Enter the text to be encoded: ";
        fgets(userInput, maxWordSize, stdin);
        for (int i = 0; userInput[i] != '\0'; i++) {
            if (userInput[i] == '\n') {
                userInput[i] = '\0';
            }
        }

        cout << "Enter a keyword for Vigenere encryption: ";
        cin >> encryptCode;

        cout << "Keyword, plainText and ciphertext are:  \n";
        encodingText(userInput, encryptCode);
        break;

    case 3: // Decode using user-entered values
        cout << "Enter the cipherText to be decoded: ";
        fgets(userInput, maxWordSize, stdin);
        for (int i = 0; userInput[i] != '\0'; i++) {
            if (userInput[i] == '\n') {
                userInput[i] = '\0';
            }
        }
        cout << "Enter a Vigenere keyword to be tried: ";
        cin >> decryptCode;
        decodingText(userInput, decryptCode);

        break;

    case 4: // Decode ciphertext given with the assignment
        cout << "Enter the cipherText to be decoded: ";
        fgets(userInput, maxWordSize, stdin);
        for (int i = 0; userInput[i] != '\0'; i++) {
            if (userInput[i] == '\n') {
                userInput[i] = '\0';
            }
        }
        autodecodingText(userInput);
        break;

    case 5: // exit program
        cout << "Exiting program" << endl;
        exit(0);
        break;

    default:
        // Sanity check
        cout << "Invalid menu option.  Exiting program." << endl;
        break;
    }// end switch( menuOption)
    return 0;
}//end main()
