// Tests.cpp
// Tae Hee Park. tpark32
// University of Illinois at Chicago
// CS 251: Spring 2020
// Project #03 - Autocomplete
// An application that tests some errors that I could think of.
// Does not fully cover all the possible errors.

#include <iostream>
#include "AutocompleteList.h"

using namespace std;

// Tests getSize() on first constructor
bool size_test1() {
    AutocompleteList  list;  // empty list
    if (list.getSize() == 0) {
        return true;
    }
    return false;
}
// Tests getSize() on second constructor
bool size_test2() {
    int n = 10;
    AutocompleteList  list(n);  // empty list
    if (list.getSize() == 10) {
        return true;
    }
    return false;
}
// Default constructor check.
bool firstConTest() {  // Default constructor check.
    AutocompleteList list;
    if (list.getSize() != 0) {
        return false;
    } else {
        return true;
    }  // Check if the size is still empty
}
// Second check on default constructor 
bool firstConTest2() {
    AutocompleteList list;
    if (list.getSortType() != "none") {
        return false;
    } else {
        return true;
    }
}

bool secConTest() {  // Second constructor check
    AutocompleteList list(3);
    AutocompleteList list2(5);  // Testing two of them at the same time.
    if (!(list.getSize() == 3 && list2.getSize() == 5)) {
        return false;
    } else {
        return true;
    }  // The parameter integer must match.
}

bool thirdConTest(string &first, string &second) {
    cout << "To test the thirdConTest, enter two file names : ";
    cin >> first >> second;
    AutocompleteList list(first);
    AutocompleteList list2(second);  // Tests two at the same time.

    if (list.getSize() != 0 && list2.getSize() != 0) {
        return true;
    } else {
        return false;
    }  // Check if the third constructor reads the file.
    // If it reads the file, it will have a size.
}

// This was not part of the public function, but I wanted to check.
bool sortTest(string &first, string &second) { // Checks if it's in lex order.
    AutocompleteList list(first);
    AutocompleteList list2(second);

    for (int i =0; i < list.getSize()-1; i++) {
        if (!(list[i].query <= list[i+1].query) ||
            !(list2[i].query <= list2[i+1].query)) {
            return false;
        }  // If it is not in order, it will return false.
    }
    return true;
}

bool copyConTest(string &first) {  // Checking copy constructor.
    AutocompleteList list(first);
    AutocompleteList list2(list);
    AutocompleteList list3(list2);

    for (int i =0; i < list.getSize()-1; i++) {
        if (!(list[i].query == list2[i].query) ||
            !(list[i].query == list3[i].query)) {
            return false;  // Checking two if any of them has fault.
        }
    }
    return true;
}

bool secCopyCon(string &first) {  // Checking copy operator.
    AutocompleteList list(first);
    AutocompleteList list2;
    AutocompleteList list3;
    list2 = list;
    list3 = list2;  // Checking two

    for (int i =0; i < list.getSize()-1; i++) {
        if (!(list[i].query == list2[i].query) &&
            !(list[i].query == list3[i].query)) {
            return false;
        }
    }

    return true;
}

bool accesOpTest() {  // Checking the operator [].
    int size = 0;
    cout << "Enter a number you want to check for accessOpTest" << endl;
    cin >> size;
    AutocompleteList list(size);
    
    for (int i =0; i < size; i++) {
        list[i].weight = i*10 +2;
    }  // First, checks if assigning with [] operator works

    for (int j =0; j <size; j++) {
        if(list[j].weight != j*10 +2) {
            return false;
        }  // Second, checks if accessing with [] operator.
    }
    return true;
}

bool matchTest(string &first, string &second) {
    string prefix;
    AutocompleteList list(first);
    AutocompleteList list2(second);
    cout << "The filenames you entered are : " << first << " ";
    cout << second << endl;
    cout << "Enter a prefix to check any match." << endl;
    cin >> prefix;

    if(list.numberOfMatches(prefix) < 0 ||
        list.numberOfMatches(prefix) > list.getSize() ||
        list2.numberOfMatches(prefix) < 0 ||
        list2.numberOfMatches(prefix) > list2.getSize()) {
        return false;  // the num of match shouldn't be less than 0,
        // or larger than the size of the list.
    } else {
        return true;
    }  // Checks the edge cases of number matching.
}

bool allMatchTest() {  // Checks if the all matching works fine.
    string fileName;
    string lookFor;
    cout << "Enter a file name to check matching " << endl;
    cin >> fileName;
    cout << "Enter a prefix that you want to look for " << endl;
    cin >> lookFor;
    AutocompleteList list(fileName);
    AutocompleteList list2 = list.allMatches(lookFor);
    
    if(list.numberOfMatches(lookFor) == list2.getSize()) {
        return true;
    } else {
        return false;
    }  // If the size of list2, which has all matches, is equal to
    // the num of matches from list, it is matching.
}

// Checks if the all matching function worked properly.
bool allMatchTest2() {
    string fileName;
    string lookFor;
    cout << "Second all matching checking " << endl;
    cout << "Enter a file name to check matching " << endl;
    cin >> fileName;
    cout << "Enter a prefix that you want to look for " << endl;
    cin >> lookFor;
    AutocompleteList list(fileName);
    AutocompleteList list2 = list.allMatches(lookFor);
    
    if (list2.getSortType() != "weight") {
        return false;
    } else {
        return true;
    }
}
// This function checks if the print function works fine.
void printTest(string &first, string &second) {
    AutocompleteList list(first);
    AutocompleteList list2(second);
    cout << "Printing Test " << endl;
    list.print();
    cout << endl;
    list2.print();
}

int main() {
    int passed = 0;
    int failed = 0;
    string first, second;
    // Run tests
    if (size_test1()) {
        passed++;
    } else {
        cout << "size_test1 failed" << endl;
        failed++;
    }

    if (size_test2()) {
        passed++;
    } else {
        cout << "size_test2 failed" << endl;
        failed++;
    }

    if (firstConTest()) {
        passed++;
    } else {
        cout << "firstConTest failed" << endl;
        failed++;
    }
    
    if (firstConTest2()) {
        passed++;
    } else {
        cout << "firstConTest2 failed" << endl;
        failed++;
    }

    if (secConTest()) {
        passed++;
    } else {
        cout << "secConTest failed" << endl;
        failed++;
    }

    if (thirdConTest(first, second)) {
        passed++;
    } else {
        cout << "defConTest failed" << endl;
        failed++;
    }

    if (sortTest(first, second)) {
        passed++;
    } else {
        cout << "sortTest failed" << endl;
        failed++;
    }

    if (copyConTest(first)) {
        passed++;
    } else {
        cout << "copyConTest failed" << endl;
        failed++;
    }

    if (secCopyCon(first)) {
        passed++;
    } else {
        cout << "secCopyCon failed" << endl;
        failed++;
    }

    if (accesOpTest()) {
        passed++;
    } else {
        cout << "accesOpTest failed" << endl;
        failed++;
    }

    if (matchTest(first, second)) {
        passed++;
    } else {
        cout << "matchTest failed" << endl;
        failed++;
    }

    if (allMatchTest()) {
        passed++;
    } else {
        cout << "allMatchTest failed" << endl;
        failed++;
    }
    
    if (allMatchTest2()) {
        passed++;
    } else {
        cout << "allMatchTest2 failed" << endl;
        failed++;
    }
    
    printTest(first, second);

    cout << "Tests passed: " << passed << " with 1 Print test " << endl;
    cout << "Tests failed: " << failed << endl;
    return 0;
}
