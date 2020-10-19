// AutocompleteList.h
// Tae Hee Park. tpark32
// University of Illinois at Chicago
// CS 251: Spring 2020
// Project #03 - Autocomplete.
// AutocompleteList class
// Has all the function needed for application.
// It uses binary search to find the one that matches the prefix
// Using C-style array.

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

struct Term {
    string query;
    long long int weight;
    // need this for autograding
    bool operator==(const Term& term) const {
        return (query == term.query && weight == term.weight);
    }
};

//
// AutocompleteList
//
class AutocompleteList {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, terms, to store a list of
    // Terms.  As a result, you must also keep track of the number of elements
    // stored (size).
    //
    Term* terms;  // pointer to a C-style array
    int size;  // number of elements in the array
    string sortType;  // records how list is sorted

    //
    // Private member function.
    // Returns the index of the first word in terms[] that contains the prefix,
    // or -1 if there are no words containing the prefix. This search should be
    // implemented using a variation of the binary search algorithm.
    // Performance requirement: O(logn), n is size.
    //

    /* This function will find a query that starts with the prefix
        Then, the function findFirst will find the first Index, 
        the function findLast will find the last index.
        I've brought this up to the one of the TAs, and he told me that 
        since the size of searching the first and the last are much smaller
        than the size we do for the binary search, it can be neglected,
        therefore, it is still considered O(logN) instead of O(N)*/
    int binarySearch(string prefix) {
        int low = 0;
        int high = this->size -1;
        int mid;

        while (low <= high) {
            mid = (low+high) /2;
            if (terms[mid].query.find(prefix) == 0) {
                return mid;
                // Reeturns the index number once found
            } else if (terms[mid].query > prefix) {
                high = mid - 1;
                // If the word is bigger than the prefix,
                // the high should decrease
            } else {
                low = mid + 1;
            }  // Otherwise, increase the low
        }
        return -1;  // If it did not find any, returns -1.
    }

    // Helper function to find the first index
    // using the index that was retunred from the binary search.
    int findFirst(int &index, string prefix) {
        for (int i = index; i >= 0; i--) {
            if (terms[i].query.find(prefix) != 0) {
                return (i+1);
            }
            // It stops at the one non-matching. Therfore,
            // it should incresae +1 to get the first Index.

            if (terms[0].query.find(prefix) == 0) {
                return 0;
            }  // If the index is 0, return 0.
        }
        return -1;
    }  // Linear search to find the first index

    int firstIndexOf(string prefix) {
        int index = 0;
        int firstIndex = 0;
        index = binarySearch(prefix);
        firstIndex = findFirst(index, prefix);
        return firstIndex;
    }

    //
    // Private member function.
    // Returns the index of the last word in terms[] that contains the prefix,
    // or -1 if there are no words containing the prefix. This search should be
    // implemented using a variation of the binary search algorithm.
    // Performance requirement: O(logn), n is size.
    //
    /* Same logic as the finding the first index. */
    int findLast(int &index, string prefix) {
        for (int i = index; i < this->size; i++) {
            if (terms[i].query.find(prefix) != 0) {
                return (i-1);
            }
            if (terms[this->size-1].query.find(prefix) == 0) {
                return this->size-1;
            }
        }
        return -1;
    }  // Linear search to find the last.

    int lastIndexOf(string prefix) {
        int index = 0;
        int lastIndex = 0;
        index = binarySearch(prefix);
        lastIndex = findLast(index, prefix);
        return lastIndex;
    }

    //
    // Private member function.
    // This function sorts the terms array by lexicographic order of the query
    // string.
    // Set sortType to "lex".
    // Performance requirement: O(nlogn), n is size.
    //
    void sortByLexOrder() {
        sort(this->terms, this->terms + this->size,
            [&](Term &left, Term &right) {
                return left.query < right.query;
            });  // Needs to be passed as references,
            // otherwise it will create a memory leak error.
        this->sortType = "lex";
    }  // Reference: Professor's lecture

    //
    // Private member function.
    // This function sorts the terms array by decreasing weight order.
    // Set the sortType to "weight".
    // Performance requirement: O(nlogn), n is size.
    //
    void sortByWeightOrder() {
        sort(this->terms, this->terms + this->size,
            [&](Term &left, Term &right) {
                return left.weight > right.weight;
            });
        this->sortType = "weight";
    }  // Reference: Professor's lecture

 public:
    //
    // default constructor:
    //
    // Called automatically by C++ to create a AutocompleteList.
    // When this is called, intialize terms to a nullptr and set size to 0.
    // Set sortType to "none".
    // Performance requirement: O(1)
    //
    AutocompleteList() {
        terms = nullptr;
        size = 0;
        sortType = "none";
    }

    //
    // a second constructor:
    //
    // Parameter passed in determines size of terms.
    // When this is called, allocate memory for n Terms and
    // set size accordingly.
    // Set sortType to "none".
    // Performance requirement: O(1)
    //
    AutocompleteList(int n) {
        this->size = n;
        this->terms = new Term[this->size];
        this->sortType = "none";
    }  // Reference: ourvector.h

    //
    // a third constructor:
    //
    // Parameter passed in is name of file to read in.
    // This constructor will build Autocomplete list from file.
    // Assume file format is:
    // line 1: "<size>"
    // lines 2 thru size+1: "weight query"
    // The list should be sorted lexicographic order by the query string.
    // Set sortType to "lex".
    // Performance requirement: O(nlogn), n is size.
    //
    // Removing the tab space before the query
    void removeTab(string &word) {
        size_t pos = word.find("\t");
        word = word.substr(pos+1, word.size());
    }  // This was from the project 1.

    AutocompleteList(string filename) {
        ifstream inFile(filename);
        long long int num = 0;
        string word;
        int i = 0;

        inFile >> num;
        this->size = num;
        this->terms = new Term[size];

        while (!inFile.eof() && i < size) {
            inFile >> num;
            this->terms[i].weight = num;
            getline(inFile, word, '\n');  // Gets the word until the new line.
            removeTab(word);
            this->terms[i].query = word;
            i++;
        }

        sortByLexOrder();
    }

    //
    // copy constructor:
    //
    // Called automatically by C++ to create an AutocompleteList that contains
    // a copy of an existing AutocompleteList.  Example: this occurs when
    // passing AutocompleteList as a parameter by value.
    // Performance requirement: O(n), n is size.
    //
    AutocompleteList(const AutocompleteList& other) {
        terms = new Term[other.size];
        size = other.size;
        sortType = other.sortType;

        for (int i =0; i < other.size; i++) {
            terms[i] = other.terms[i];
        }
    }  // Reference: ourvector.h

    //
    // copy operator=
    //
    // Called when you assign one AutocompleteList into another,
    // i.e. this = other;
    // Performance requirement: O(n), n is size.
    //
    AutocompleteList& operator=(const AutocompleteList& other) {
        if (this == &other) {
            return *this;
        }

        delete[] terms;

        this->terms = new Term[other.size];
        this->size = other.size;
        this->sortType = other.sortType;
        
        for (int i =0; i <other.size; i++) {
            this->terms[i] = other.terms[i];
        }

        return *this;
    }  // Reference: ourvector.h

    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated by the Term.
    //
    virtual ~AutocompleteList() {
        if (terms != nullptr) {
            delete[] terms;
        }
    }  // Reference: ourvector.h

    //
    // Public member function.
    // Returns the size of the AutocompleteList.
    // Performance requirement: O(1).
    //
    int getSize() {
        return this->size;
    }

    //
    // Public member function.
    // Returns Term element in AutocompleteList.
    // This gives public access to Terms stored in the AutocompleteList.
    // If i is out of bounds, throw an out_of_range error message:
    // "AutocompleteList: i out of bounds"
    // Note:  This public function does not necessarily fit the design of this
    // abstraction but we are having you write it for testing purposes.
    // Performance requirement: O(1).
    //
    Term& operator[](int i) {
        if (i < 0 || i >= this->size) {
            throw out_of_range("AutocompleteList: i out of bounds");
        }
        return terms[i];
    }   // Reference: ourvector.h

    // Public member function.
    // Returns an AutocompleteList which stores a list of all Terms that
    // start with the prefix.  The AutocompleteList returned should be sorted
    // in descending order by weight.  Set the returned AutocompleteList's
    // sortType to "weight".
    // If prefix is empty string, return an empty AutocompleteList;
    // If there are no words in the list the start with the prefix, return an
    // empty AutocompleteList.
    // If *this* AutocompleteList's sortType does not equal "lex", then return
    // an empty AutocompleteList.  In other words, allMatches should only be
    // called on an AutocompleteList that is sorted in lexicographic order by
    // the query string.
    // Performance requirement: O(mlogm+logn), n is size and
    // where m is the number of matching terms.
    //
    AutocompleteList allMatches(string prefix) {
        AutocompleteList empty;
        if ((this->sortType != "lex") || (prefix.length() == 0) ||
            (numberOfMatches(prefix) == 0)) {
            return empty;
        }  // The edge cases mentioned above.

        long long int start = firstIndexOf(prefix);
        long long int end = lastIndexOf(prefix);
        int matchSize = (end - start) +1;

        AutocompleteList matchList(matchSize);

        int j = 0;
        for (int i = start; i < end+1; i++) {
            matchList.terms[j] = this->terms[i];
            j++;
        }  // copies the terms those were matching.

        matchList.sortByWeightOrder();
        return matchList;
    }
    // Public member function.
    // Returns the number of Terms that start with the given prefix.
    // If prefix is empty, return 0.
    // If *this* AutocompleteList's sortType does not equal "lex",
    // then return 0.
    // Performance requirement: O(logn), n is size.
    //
    int numberOfMatches(string prefix) {
        if ((prefix.length() == 0) || (this->sortType != "lex")) {
            return 0;
        }  // Edge cases mentioned above.

        if (firstIndexOf(prefix) == -1 || lastIndexOf(prefix) == -1) {
            return 0;
        } else {
            return lastIndexOf(prefix) - firstIndexOf(prefix) + 1;
        }
    }
    //
    // Public member function.
    // Prints the AutocompleteList.
    // Pad the front of the print with 8 spaces for nicely formatted search:
    // print: "        query, weight".
    // NOTE:  This is also useful for debugging purposes.
    // Performance requirement: O(n), n is size
    //
    void print() {
        for (int i =0; i < this->size; i++) {
            cout << "        " << terms[i].query << ", ";
            cout << terms[i].weight << endl;
        }
    }
    
    /* A public function that catches the sort type. This function is 
        created to test the constructors. */
    string getSortType() {
        return this->sortType;
    }
};
