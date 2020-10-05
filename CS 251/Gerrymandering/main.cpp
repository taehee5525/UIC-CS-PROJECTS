// Main.cpp
// Tae Hee Park. tpark32
// University of Illinois at Chicago
// CS 251: Spring 2020
// Project#01 - Gerrymandering
// An application that loads the voting data, search a specific state
// and plot votes of states, and display the calculatied stats.
// Also, display the voter turnout percentage.

#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "ourvector.h"

using namespace std;

// This function will make the user choice case insensitive.
void caseInsen(string &noCase) {
    transform(noCase.begin(), noCase.end(), noCase.begin(), ::tolower);
}

// This function will check if the data is correctly loaded or not.
string dataCheck(ourvector<string> &distState, ourvector<string> &eliState) {
    // Vector used to store district info.
    // Vector used to store the eligible_voters.txt info.

    if (distState.size() != 0 && eliState.size() != 0) {
        return "Yes";
    }  // If both files were loaded, the data is loaded.
    return "No";
}

// This function will get the state name from the districts.txt file.
void getState(string &varName, int &counter) {
    // The varname contains a state's info.
    // counter is to calculate district numbers.

    int size = varName.size();  // Declares the size of the string

    for (int i = 0; i < size; i++) {
        if (varName[i] == ',') {
            counter++;
        }  // Each time it hits the comma, counts.
    }

    counter = counter /3;  // Because there are three types of data.
    // To count district number, must be divided by 3.
    size_t pos = varName.find(',');
    varName = varName.substr(0, pos);
    // This gets state name. Code was learned from lecture
}

// This does loading, and putting the data into each vetor for the first file.
void distVector(ifstream &fileName, ourvector<string> &distState,
                ourvector<string> &lineByline) {
                    // fileName is for districts.txt
                    // distState is to store the state name
                    // lineByline is to store the information by the state.

    string varName;

    while (!fileName.eof()) {
        getline(fileName, varName, '\n');
        lineByline.push_back(varName);
    }  // puts each line into the vector.

    for (int i = 0; i < lineByline.size()-1; i++) {
        // if not reduced by 1, dist vec will contain an empty line.

        int counter = 0;
        varName = lineByline[i];
        getState(varName, counter);  // Receives the statename
        distState.push_back(varName);  // stores the information.

        cout << "..." << distState[i] << "..."
        << counter<< " districts total" << endl;
    }

    cout << endl;
}

// This function checks if the states from both files are matching
void matchState(ourvector<string> &distState, string stateName,
                ourvector<string> &eliState) {
                    // distState will be the standard
                    // stateName to match the state name
                    // add the state to elistate if state is found

    for (int i = 0; i < distState.size(); i++) {
        if (stateName == distState[i]) {
            eliState.push_back(stateName);
        }
    }
}

// Also, this function will add the votes to eliVoters vector.
void matchVotes(ourvector<string> &eliState, ourvector<int> &eliVoters,
                string stateName, string eligibleVoters) {
                    // eliState, to get the index
                    // eliVoters, to add the element
                    // stateName, to see if the state exists in eliState vector
                    // eligibleVoters, will be added to eliVoters vector.

    int numVotes = stoi(eligibleVoters);  // change to string to int.

    for (int i = 0; i < eliState.size(); i++) {
        if (eliState[i] == stateName) {
            eliVoters.push_back(numVotes);
        }
    }
}

// This function will load the second txt file and add data to vectors.
void eliVector(ifstream &fileName, ourvector<string> &eliState,
                ourvector<string> &distState, ourvector<int> &eliVoters) {
                    // fileName, to read the eligible_voters.txt fileName
                    // eliState and distState to match the states
                    // eliVoters, add elements to this vector.

    string stateName;
    string eligibleVoters;

    while (!fileName.eof()) {
        getline(fileName, stateName, ',');
        getline(fileName, eligibleVoters, '\n');
        matchState(distState, stateName, eliState);
        // Receives the correct state names
        matchVotes(eliState, eliVoters, stateName, eligibleVoters);
        // add the vote data
    }

    for (int i = 0; i < eliState.size(); i++) {
        cout << "..." << eliState[i] << "..." << eliVoters[i]
        << " eligible voters" << endl;
    }

    cout << endl;
}

// This function will load the data from each text file.
// This function is for the secondfile.
void loadSecfile(ourvector<string> &distState, ourvector<string> &eliState,
                 ourvector<int> &eliVoters) {
                      // distState to match the right states
                      // eliState to receive the state info from sec file.
                      // eliVoters to receive the votes information

    string secondTxt;
    ifstream secFile;
    cin >> secondTxt;

    secFile.open(secondTxt);

    if (!secFile.is_open()) {
        cout << "Invalid second file, try again." << endl;
        cout << endl;
        return;
    }  // Returns the error if it cannot open the second file.

    cout << "Reading: " << secondTxt << endl;
    eliVector(secFile, eliState, distState, eliVoters);
    // Will add data to vectors.
    secFile.close();
}

// loads the first file then second file.
void loadFile(ourvector<string> &distState, ourvector<string> &lineByline,
                ourvector<string> &eliState, ourvector<int> &eliVoters) {
                    // distState to receive the state name information
                    // lineByline to receive the data by the state.
                    // eliState and eliVoters for the second file.

    string firstTxt;
    ifstream firFile;
    string dummy;

    cin >> firstTxt;

    if (distState.size() != 0)  {
        cout << "Already read data in, exit and start over." << endl;
        cout << endl;
        cin >> dummy;
        return;
    }  // This prevents the user to load the data twice.

    firFile.open(firstTxt);

    // The first portion, which is to load the districts.txt file
    if (!firFile.is_open()) {
        cout << "Invalid first file, try again." << endl;
        cout << endl;
        cin >> dummy;
        return;
    }  // Returns the error when the file cannot be opened.

    cout << "Reading: " << firstTxt << endl;
    distVector(firFile, distState, lineByline);
    // will add elements to the vectors.

    firFile.close();

    loadSecfile(distState, eliState, eliVoters);
}

// It will find an index to receive the state name.
void findIndex(ourvector<string> &distState, string inputState, int &index) {
            // distState and inputState to find if the userinput is correct.
            // index number to indicate.

    for (int i =0; i< distState.size(); i++) {
        string properState = distState[i];
        caseInsen(inputState);
        caseInsen(properState);
        // Need to compare both strings with lower to prevent an error

        if (inputState == properState) {
            index = i;
            return;
        }  //When it receives the right index, return back to the function.
    }

    if (index < 0 || index > distState.size()) {
        cout << "State does not exist, search again." << endl;
        cout << endl;
        return;
    }  // If index can't be found, display error.
}

// This function will search for the sate
void searchState(ourvector<string> &distState, string &state,
                string inputState) {
                // distState vector to be the standard.
                // inputState has the user input.

    int index = 100;
    // index declaration.

    findIndex(distState, inputState, index);
    // Veryify if the user has the correct input.

    if (index != 100) {
        state = distState[index];  // updates the state information.
    } else {
        return;  // If not found, return back do not update.
    }
}

// This function will find the line which has a particular state information.
string vectorSearch(ourvector<string> &lineByline, ourvector<string> &distState,
                    string state) {
                    // vector from lineByline will be used to extract the data
                    // distState and state to find the right vector location

    int index = 0;

    for (int i =0; i< distState.size(); i++) {
        if (state == distState[i]) {
            index = i;
        }
    }  // If the state is found, return the index

    return lineByline[index];  // Return the line which contains the data
}

// This will calculate the wasted votes.
void calcVote(int repVotes, int demVotes, int &wastedRep, int &wastedDem) {
                // republican and democrat votes by distrcits
                // the wasted votes by the districfts.
    int total = repVotes + demVotes;
    int overhalf = (total/2) +1;
    // Basic formula taken from project description.

    if (repVotes > demVotes) {
        // If republicans win, all the democrats votes are wasted.
        wastedRep = abs(overhalf- repVotes);
        wastedDem = demVotes;
    } else if (demVotes > repVotes) {
        wastedRep = repVotes;
        wastedDem = abs(overhalf- demVotes);
    }  // If democrats win, all the republicans votes are wasted.
}

// calculate the total votes.
int totalVotes(int repVotes, int demVotes) {  // rep. dem. votes.
    return (repVotes + demVotes);
}

// calculate the Efficiency gap for the state.
double effGap(int total, int totalRep, int totalDem) {
                // the total votes of republican and democrat
                // the total republican votes and total democrat votes.

    double gap = abs(totalRep - totalDem);
    // the gap calculation.
    return (100* (gap / (double)total));
    // make it percentage.
}

// This will calculate which party is dominant.
string gerryAgainst(int totalRep, int totalDem) {
                        // the total votes from each party is used.

    if (totalRep > totalDem) {
        return "Republicans";
    } else {
        return "Democrats";
    }
}

// This will display the Efficiency gap with all the necessary information.
void displayEff(string &isIt, int total, int totalDem, int totalRep) {
                // indicator if the state is gerrymandered.
                // the total votes from both party.
                // the total votes from each party.

    double gap = effGap(total, totalRep, totalDem);  // calculates the gap

    if (gap > 7.0) {  // taken from the project description.
        isIt = "Yes";
        cout << "Gerrymandered: " << isIt << endl;
        cout << "Gerrymandered against: " <<
        gerryAgainst(totalRep, totalDem) << endl;
        cout << "Efficiency Factor: " << gap << "%" << endl;
    }  // dispalys the gap and necessary information only if the gap is > 7
}

// This function will display the rest of the states.
void displayStats(string &isIt, int totalDem, int totalRep) {
                    // indicator if the state is gerrymandered.
                    // the total votes from each party.

    if (isIt == "No") {
        cout << "Gerrymandered: " << isIt << endl;
    }
        cout << "Wasted Democratic votes: " << totalDem << endl;
        cout << "Wasted Republican votes: " << totalRep << endl;
}

// Check if the state has more than 3 states.
bool distCounter(string info) {
                    // receives the whole state info.
    int counter = 0;  // it will be the distrcit indicator.
    int size = info.size();  //  declaration of string size.

    for (int i =0; i< size; i++) {
        if (info[i] == ',') {
            counter++;
        }
    }

    counter = counter/3;  // the district number will be the total comma /3

    return (counter >= 3);
}

// This will calculate all the information for displaying stats.
void stateStats(ourvector<string> &lineByline, ourvector<string> &distState,
                string state) {
                // lineByline vector to extract the state data.
                // distState and state to find out the right state.

    string dummy, repVotes, demVotes;
    string isIt = "No";  // declaration of gerrymander indicator.

    int totalRep = 0;
    int totalDem = 0;
    int total = 0;

    string info = vectorSearch(lineByline, distState, state);

    stringstream ss(info);

    getline(ss, dummy, ',');
    // Information other than votes number are not needed.

    while (getline(ss, dummy, ',')) {
        int wastedDem = 0;
        int wastedRep = 0;

        getline(ss, demVotes, ',');
        int demVoted = stoi(demVotes);
        getline(ss, repVotes, ',');
        int repVoted = stoi(repVotes);

        total = total + totalVotes(repVoted, demVoted);
        // calculates the total vote
        calcVote(repVoted, demVoted, wastedRep, wastedDem);
        // calculates the wasted vote from each district.

        totalDem = totalDem + wastedDem;
        totalRep = totalRep + wastedRep;  // calculate the total wasted votes.
    }

    if (distCounter(info)) {  // only when there are more than 3 districts.
        displayEff(isIt, total, totalDem, totalRep);  // display Efficiency gap.
    }

    displayStats(isIt, totalDem, totalRep);
}

// This will display the eligible voter information.
void displayVoters(ourvector<int> &eliVoters, ourvector<string> &eliState,
                    string state) {
            // eliVoters to get the eligible voters counter
            // eliState vector and state to find out which state.

    int index = 0;

    for (int i = 0 ; i < eliState.size(); i++) {
        if (state == eliState[i]) {
            index =i;
        }
    }  // find out the index of state the user is looking for.

    cout << "Eligible voters: " << eliVoters[index] << endl;
    cout << endl;
}

// This will return the percentage of votes.
int returnPercent(double total, double votes) {
    return (votes/total) * 100;
}

// This function will calculate the information needed to plot.
void plotCalc(int counter, string strDem, string strRep) {
                // counter to indicate which District
                // strDem and strReP string version of votes.

    double demVotes = stod(strDem);
    double repVotes = stod(strRep);
    double total = repVotes + demVotes;

    cout << "District: " << counter << endl;

    for (int i =0; i < returnPercent(total, demVotes); i++) {
        cout << "D";
    }

    for (int j =0; j < 100 - returnPercent(total, demVotes); j++) {
        cout << "R";
    }
    // This will display the Ds and Rs based on the percentage of votes.
    cout << endl;
}

// This function will calculate and display the plots for the state user chose.
void plotFunction(ourvector<string> &lineByline, ourvector<string> &distState,
                string state) {
                // lineByline to extract the state's data
                // distState and state to match the state user looks for.

    string dummy;  // in plot function, only the votes data is needed.
    string strDem;
    string strRep;

    int counter = 0;

    string info = vectorSearch(lineByline, distState, state);
    // receive the line which contains the voting information
    stringstream ss(info);

    getline(ss, dummy, ',');

    while (getline(ss, dummy, ',')) {
        // Everything other than votes info will not be stored.
        counter++;  // for the district numbers.
        getline(ss, strDem, ',');
        getline(ss, strRep, ',');

        plotCalc(counter, strDem, strRep);
        // calculates the percentage and display the plot.
    }
        cout << endl;
}

// It will find the index of the state from the elistate vector.
int voterIndex(ourvector<string> &eliState, string state) {
                // eliState vector and state to find the state index.

    for (int i =0; i< eliState.size(); i++) {
        if (state == eliState[i]) {
            return i;
        }
    }

    return 0;
}

// This will calculate how many people actulaly voted.
int realVoted(ourvector<string> &lineByline, ourvector<string> &distState,
                string state) {
                // lineByline vector to extract the state's data
                // distState and state to find out the correct state

    string dummy;
    string votesRep;
    string votesDem;
    int totalVoted = 0;

    string info = vectorSearch(lineByline, distState, state);
    // get the line which contains a particualr state's information.
    stringstream ss(info);

    getline(ss, dummy, ','); 
    // information other than votes will not be needed.

    while (getline(ss, dummy, ',')) {
        getline(ss, votesRep, ',');
        getline(ss, votesDem, ',');
        totalVoted = totalVoted + stoi(votesRep) + stoi(votesDem);
    }  // receives the total votes.

    return totalVoted;
}

// This will calculate the voter turnout
double turnoutCalc(int eligibleVotes, int votesDone) {
                        // eligible voters from the state
                        // the actual votes from the state.

    return ((double)votesDone / (double)eligibleVotes) * 100;
}

// This function will calculate the voter tunrout information.
void turnoutFunct(int index, int votesDone, ourvector<int> &eliVoters) {
                    // index to find the right state from eliVoters vector.
                    // votesDone is the total votes from the state
                    // eliVoters to show the eligible voters from the state.

    int eligibleVotes = eliVoters[index];  // the number of eligible voters.

    cout << "The amount of eligible voters of this particular state : "
    << eligibleVotes<< endl;
    
    cout << "Votes done : " << votesDone << endl;  // total votes
    cout << "The voter turnout percentage of this stae : "
    << turnoutCalc(eligibleVotes, votesDone) << "%" << endl;
    
    cout << endl;
}

// This function will display the error.
void displayError(string option, string data, string state) {
    if (option == "search" && data != "Yes") {
        string dummy;
        cin >> dummy;
        cout << "No data loaded, please load data first." << endl;
        cout << endl;
        return;   // no data loaded, but the user wants to search.
    } else if (option != "search") {
        if (data != "Yes") {
            cout << "No data loaded, please load data first." << endl;
            cout << endl;
            return;  // data not loaded, but user wants to do stats/plot/turnout
        } else if (state == "N/A") {
            cout << "No state indicated, please search for state first."
            << endl << endl;
            return;
        }  // when the state is not input.
    }
}

// This is the main application, which receives the userinput and proceed.
int gerrymandering(string &data, string &state, string &inputState) {
                // data to check if the data is correctly loaded.
                // state to display the correctly loaded state.
                // inputState is the user input for the state.

    string option;  // This will store the user choice
    ourvector<string> distState;  // Vector of state names from first txt
    ourvector<string> eliState;  // Vector of state names from second txt
    ourvector<int> eliVoters;  // Vector of # of eligible voters in second txt
    ourvector<string> lineByline;
    // Vector which broke down the whole texts into line by line

    while (true) {
        cout << "Data loaded? " << data << endl;
        cout << "State: " << state << endl << endl;
        cout << "Enter command: " << endl;
        cout << "-----------------------------" << endl << endl;

        cin >> option;  // This will determine what the user wants to does
        caseInsen(option);  // needs to be case insensitive.

        if (option == "exit") {
            return 0;  // This will terminate the program.
        }

        if (option == "load") {
            loadFile(distState, lineByline, eliState, eliVoters);  // loads file
            data = dataCheck(distState, eliState);
            // checck if the data is loaded.
        }

        if (option != "load") {
            displayError(option, data, state);  // error message.
        }

        if (option == "search" && data == "Yes") {
            char returnChar = ' ';
            returnChar = getchar();
            // this will prevent a whitspace issue.
            getline(cin, inputState, '\n');
            searchState(distState, state, inputState);
            // searchs for the state.
        }

        if (option == "stats" && data == "Yes" && state != "N/A") {
            stateStats(lineByline, distState, state);
            displayVoters(eliVoters, eliState, state);
        }  // gets the stats from the state and display.

        if (option == "plot" && data == "Yes" && state != "N/A") {
            plotFunction(lineByline, distState, state);
        }  // gets the plot information and display.

        if (option == "turnout" && data == "Yes" && state != "N/A") {
            int index = voterIndex(eliState, state);
            // get the index of the vector to correctly spot
            int votesDone = realVoted(lineByline, distState, state);
            // the total votes made from the state.
            turnoutFunct(index, votesDone, eliVoters);
        }  // will calculate the turnout and display.
    }
}

int main() {
    string data = "No";  // This will determine if the data is loaded or not.
    string state = "N/A";  // This will store the state information.
    string inputState;  // This will receive the user input.
    cout << "Welcome to the Gerrymandering App!" << endl;
    cout << endl;

    gerrymandering(data, state, inputState);  // the main application.

    return 0;
}
