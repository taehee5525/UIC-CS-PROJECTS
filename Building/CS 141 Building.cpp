/* Program 1: Building

	Class: CS 141, Spring 2020. Tues 3pm Lab
	System: Zybooks
	Author: Tae Hee Park
 */

#include <iostream>   // for cin and cout
#include <iomanip>    // for setw() and setfill()
using namespace std;  // so that we don't need to preface every cin and cout with std::

int main()
{
   for(;;){
    int menuOption = 0;
    
    cout << "Choose from among the following options:  \n"
         << "1. Display original graphic  \n"
		 << "2. Display building          " << endl
         << "3. Exit the program          \n"
         << "Your choice -> ";
    cin >> menuOption;
    cout << endl;   // Leave a blank line after getting the user input for the menu option.
    
    // See if exit was chosen
    if( menuOption == 3) {
		cout << "You chose " << menuOption << endl;
		cout << "Exit now.";
        exit( 0);
    }
    
    else if( menuOption == 1) {
        // My own graphic. Instead of the setw( 8) that was given from the sample, I used setw( 50).
		// Instead of using the for loops, I used setfill and set w to fill the top line.
		// Top line
		cout << setfill('*')
			 << setw( 50) << " "
			 << endl;
		
        /* The backslash '\' character is a signal to the system that the next character is something
        special.  When we want the backslash character itself to be displayed, we must put two
        backslash characters in a row, as illustrated below.
		*/
		
		// Now the main body. My original graphic will be the "UIC" in a circle.
		cout << setfill(' ');
		cout << setw(10) << " ";
		for ( int i =0; i <31; i++) {
			cout << "=";
		} // This for loop fills the top portion of the circle.
		cout << endl;
		
		cout << setw (9) << " " << "/" << setw(31) << " " << "\\" << endl; // This makes the curve of the circle
		cout << setw (9) << " " << "|"
			 << setw (1) << " " << ":;" << setw(4) <<" " << ";:" //Creates the top portion of U
			 << setw (4) << " " << "|++|" // Creates the top portion of I
			 << setw (7) << " " << "@@"
			 << setw (6) << "|" << endl; //Creates the top portion of C and closes
			 
		cout << setw (9) << " " << "|"
			 << setw (1) << " " << ":;" << setw(4) << " " << ";:"
			 << setw (4) << " " << "|++|"
			 << setw (5) << " " << "(%" << setw(3) << " " << "%("
			 << setw (3) << "|" << endl; //Created the second line of UIC
			 
		cout << setw (9) << " " << "|"
			 << setw (1) << " " << ":;" << setw(4) << " " << ";:"
			 << setw (4) << " " << "|++|"
			 << setw (5) << " " << "(%"
			 << setw (8) << "|" << endl;
			 
		cout << setw (9) << " " << "|"
			 << setw (1) << " " << ":;" << setw(4) << " " << ";:"
			 << setw (4) << " " << "|++|"
			 << setw (5) << " " << "(%" << setw(3) << " " << "%("
			 << setw (3) << "|" << endl; // At here, the C turns
			 
		cout << setw (9) << " " << "|"
			 << setw (4) << " " << "~~"
			 << setw (7) << " " << "|++|"
			 << setw (7) << " " << "@@"
			 << setw (6) << "|" << endl;
			 
		cout << setw (9) << " " << "\\" << setw(31) << " " << "/" << endl;
		// This part, just like the inverse of the top portion
		
		cout << setfill(' ');
		cout << setw(10) << " ";
		for ( int j =0; j <31; j++) {
			cout << "=";
		} // using the same loop so that I can close the circle
		cout << endl;
		cout << endl;
		for ( int k = 0; k<51; k++) {
			cout << "&";
		}
    } //end if( menuOption == 1)  // menu option to display custom graphic
    
	else if ( menuOption == 2) {
		// When the menuOption is 2, it will ask for the number of buildings that the user wants to display
		int buildingSec; //This will be the userInput for the building selection
		cout << "Number of building sections -> ";
		cin >> buildingSec;
		cout << endl;
		int buildingFloor = buildingSec + 1; // This will be used to determine the floor
		// Outputs the message guiding the user to put the buildings section number

		cout << setw(buildingFloor + 1) << " " << "/\\" << endl;
		cout << setw(buildingFloor + 1) << " " << "||" << endl;
		cout << setw(buildingFloor + 1) << " " << "||" << endl;
		cout << setw(buildingFloor + 1) << " " << "--" << endl;
		cout << setw(buildingFloor) << " " << "|++|" << endl;
		cout << setw(buildingFloor) << " " << "===="  << endl; //The very top portion
		//Each line was indented as it was shown on the assignment
		// The top 4 lines was indented 1 more than the floor levels therefore I added 1 more
		// rest of the lines were indented as many as the floor levels
		
		
		// Now the main body of the building
		for (int i = 0; i < buildingSec; i++) {
			int k;
			for (int j = 0; j < (i+1) ; j++) {
				
				for (k = 0; k <buildingFloor-i; k++) {
					cout << " ";
				}
				
				cout << "|";
				
				for (k = 0; k <j; k++) {
					cout <<":";
				}
				
				cout <<"\\";
				
				for (k = 0; k < 2*(i-j); k++) {
					cout <<":";
				}
				
				cout << "/";
				
				for (k = 0; k <j; k++) {
					cout <<":";
				}
				
				cout <<"|" << endl;
			}
			
			// the for-loop of j creates one line at a time 
			// This whole code is the top portion
			// Now this is the reflection of the first top portion.
			for (int j = 0; j < (i+1); j++) {
				
				for (k = 0; k <buildingFloor-i; k++) {
					cout << " ";
				}
				
				cout << "|";
				
				for (k = 0; k < i-j; k++) {
					cout << ":";
				}
				
				cout << "/";
				
				for (k = 0; k <2*j; k++) {
					cout << ":";
				}
				
				cout << "\\";
				
				for (k = 0; k<i-j; k++) {
					cout << ":";
				}
				
				cout << "|" << endl;
			}
			
			// Below codes create the line that separates the each floor
			for ( k = 0; k < buildingFloor-i; k++) {
				cout << " ";
			}
			
			cout << "/";
			
			for ( k = 0; k < 2* (i+1); k++) {
				cout << "-";
			}
			
			cout << "\\" << endl;
		}
				


		// This is the very bottom part
		// The first cout will set up the space
		// The for loop will set up the amount of . and + needed for the bottom
		
			if (buildingSec == 0) {
				cout << " ....";
			}
			else if (buildingSec == 1) {
				cout << " ......";
			}
		// For me, it was easier to create the case of 0 and 1 instead of making a for loop.
				
			else {
				cout << " ";
				
				for (int m = 0; m < 4 +(buildingSec * 2); m++) {

					cout << ".";
				}
			}
		cout << endl;
			if(buildingSec == 0) {
				cout << "++++++";
			}
			else if (buildingSec == 1) {
				cout << "++++++++";
			}
		// For me, it was easier to create the case of 0 and 1 instead of making a for loop.
			else {
				
				for (int n = 1; n <= 6 + (buildingSec* 2); n++) {
					cout << "+";
					
				}
			}
		cout << endl;
		
	}
	
    cout << endl;
    return 0;
}
}
