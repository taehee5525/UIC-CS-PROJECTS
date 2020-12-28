// priorityqueue.h
// Tae Hee Park. tpark32
// University of Illinois at Chicago
// CS 251: Spring 2020
// Project #06 - File comparision
// Does check the file and encode and decode using binary bits.

#include <algorithm>
#include <utility>
#include <queue>
#include <vector>
#include <iostream>
#include <string>
#include "hashmap.h"

#pragma once

typedef hashmap hashmapF;
typedef unordered_map <int, string> hashmapE;

struct HuffmanNode {
    int character;
    int count;
    int order;
    HuffmanNode* zero;
    HuffmanNode* one;
};
//
// This method frees the memory allocated for the Huffman tree.
//
void freeTree(HuffmanNode* node) {
    if (node == nullptr) {
        return;
    }
    freeTree(node->zero);
    freeTree(node->one);
    delete node;
}  // Modified from proj5 free tree code.

// Freequency builder helper
int freqHelper(char c, hashmapF &map) {
    int value = c;

    if (map.containsKey(value)) {
        return map.get(value)+1;
    }  // If found, add 1 to the current frequency.

    return 1;  // If nothing found, return 1
}

//
// This function build the frequency map.  If isFile is true, then it reads
// from filename.  If isFile is false, then it reads from a string filename.
//
//
void buildFrequencyMap(string filename, bool isFile, hashmapF &map) {
    int value = 0;
    int length = filename.size();
    size_t frequency;  // Only the positive number goes in.

    if (!isFile) {
        for (int i = 0; i < length; i++) {
            char c = filename[i];
            value = filename[i];
            frequency = std::count(filename.begin(), filename.end(), c);
            map.put(value, frequency);
            // If isFile is false, takes the string
            // Used a count function to count the frequency
        }
        map.put(PSEUDO_EOF, 1);  // Added a EOF at the end.

    } else {
        ifstream inFile(filename);
        char c;
        while (inFile.get(c)) {
            value = c;
            frequency = freqHelper(c, map);
            map.put(value, frequency);
        }
        map.put(PSEUDO_EOF, 1);
    }  // Otherwise, open the file and read it.
}

// prioritize functor modified from the lecture code.
class prioritize {
 public:
        bool operator()(HuffmanNode *node1, HuffmanNode *node2) const {
            if (node1->count == node2->count) {
                if (node1->order > node2->order) {
                    return node1->order > node2->order;
                }  // If the count is the same and
                // the first one was inserted late,
                // Then, put it back.
            }
            return node1->count > node2->count;
            // Otherwise, sort it with the count order.
        }
};

//
// This function builds an encoding tree from the frequency map.
//

void mapHelper(hashmapF &map,
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, prioritize> &pq,
    int &counter) {

    for (int key : map.keys()) {
        HuffmanNode *temp = new HuffmanNode;
        temp->character = key;
        temp->count = map.get(key);
        temp->zero = nullptr;
        temp->one = nullptr;
        temp->order = counter;
        pq.push(temp);
        counter++;
    }  // For the each key, add HuffmanNode to each key.
    // add the order as it is inserted.
}

// This is the function to help build the tree
void treeHelper(
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, prioritize> &pq,
    int &counter) {
    while (pq.size() != 1) {
        HuffmanNode *left = pq.top();
        pq.pop();

        HuffmanNode *right = pq.top();
        pq.pop();

        HuffmanNode *newNode = new HuffmanNode;
        newNode->character = NOT_A_CHAR;
        newNode->one = right;
        newNode->zero = left;
        newNode->count = left->count + right->count;
        newNode->order = counter;
        pq.push(newNode);
        counter++;
    }
    // Take the first two. the first one goes to left and
    // the second one goes to right.
    // then, add N/A to the character and link them.
    // add the order, and then count will be the sum of two count.
}

// Simply call the two helper function to build the encoding tree.
HuffmanNode* buildEncodingTree(hashmapF &map) {
    int counter = 0;
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, prioritize> pq;
    mapHelper(map, pq, counter);
    treeHelper(pq, counter);

    return pq.top();
}
//
// Recursive helper function for building the encoding map.
//
void _buildEncodingMap(HuffmanNode* node, hashmapE &encodingMap, string str, HuffmanNode* prev) {
    prev = node;  // The prev node will be the current node.
    HuffmanNode *left = node->zero;
    HuffmanNode *right = node->one;

    if (left != nullptr) {
        _buildEncodingMap(left, encodingMap, str+"0", prev);
    }  // If left is not empty, add 0 and move down to the left.

    if (right != nullptr) {
        _buildEncodingMap(right, encodingMap, str+"1", prev);
    }  // If right is not empty, add 1 and move down to the right.

    if (left == nullptr && right == nullptr) {
        if (node->character == NOT_A_CHAR) {
            return;
        } else {
            encodingMap.emplace(node->character, str);
        }
    }  // If both is empty and then the character is N/A just return
    // otherwise, add it to the map.
}

//
// This function builds the encoding map from an encoding tree.
//
hashmapE buildEncodingMap(HuffmanNode* tree) {
    hashmapE encodingMap;
    HuffmanNode* prev = tree;  // The prev node will be the current node.

    _buildEncodingMap(tree->zero, encodingMap, "0", prev);
    _buildEncodingMap(tree->one, encodingMap, "1", prev);
    return encodingMap;
}

//
// This function encodes the data in the input stream into the output stream
// using the encodingMap.  This function calculates the number of bits
// written to the output stream and sets result to the size parameter, which is
// passed by reference.  This function also returns a string representation of
// the output file, which is particularly useful for testing.
//
void encodeHelper(string s , hashmapE &encodingMap, ofbitstream& output) {
    int length = s.size();
    for (int i =0; i < length; i++) {
        int bit = s[i]-48;
        output.writeBit(bit);
    }  // Each character is written in ASCII,
    // to get the bit, needs to subtract 48 from the ASCII value.
}

string encode(ifstream& input, hashmapE &encodingMap, ofbitstream& output,
              int &size, bool makeFile) {
    char c;
    // I used the unsigned long long int to receive a big digit number.
    string encodeStr;

    while (input.get(c)) {
        encodeStr += encodingMap[c];
        encodeHelper(encodingMap[c], encodingMap, output);
    }
    encodeHelper(encodingMap[PSEUDO_EOF], encodingMap, output);
    encodeStr += encodingMap[PSEUDO_EOF];
    // Add the PSEUDO_EOF to the end.
    size = encodeStr.length();
    // The size will be the length of the string.
    return encodeStr;
}


//
// This function decodes the input stream and writes the result to the output
// stream using the encodingTree.  This function also returns a string
// representation of the output file, which is particularly useful for testing.
//
string decode(ifbitstream &input, HuffmanNode* encodingTree, ofstream &output) {
    string decodeStr;
    HuffmanNode *temp = encodingTree;
    // Get a temp head node for traversing.

    while(input.is_open()) {  // While the file is open,
        int bit = input.readBit();
        if (bit == -1 || temp->character == PSEUDO_EOF) {
            break;
        }  // If the bit is -1, then break out of the loop.
        // Also, when the character of the encoding tree is PSEUDO_EOF,
        // break out of the loop.
        if (temp->zero == nullptr && temp->one == nullptr) {
            char c = temp->character;
            output.put(c);  // Put the character in the output file.
            decodeStr += c;
            // Update the string
            temp = encodingTree;
            // Back to the head of the tree
        }
        if (bit == 0) {
            temp = temp->zero;
        }  // If bit is 0, go to left
        if (bit == 1) {
            temp = temp->one;
        }  // If bit is 1, go to right
    }
    return decodeStr;
}

//
// This function completes the entire compression process.  Given a file,
// filename, this function (1) builds a frequency map; (2) builds an encoding
// tree; (3) builds an encoding map; (4) encodes the file (don't forget to
// include the frequency map in the header of the output file).  This function
// should create a compressed file named (filename + ".huf") and should also
// return a string version of the bit pattern.
//
string compress(string filename) {
    hashmapF frecMap;
    hashmapE encMap;
    HuffmanNode *encTree = nullptr;
    ifstream input(filename);
    ofbitstream output(filename +".huf");
    stringstream ss;
    int size = 0;
    // Declare everything that needs to be delcared.
    // Modified from the main code.

    buildFrequencyMap(filename, true, frecMap);
    // Build the freq map using the original source.
    encTree = buildEncodingTree(frecMap);
    // Building the encoding tree using the frecMap.
    encMap = buildEncodingMap(encTree);
    // Building the encoding map using the encTree.
    freeTree(encTree);
    // Free the encoding tree before it gets out of the function.

    ss << frecMap;
    output << frecMap;
    // Insert the frecquency map header to the huf file.
    string codeStr = encode(input, encMap, output,size, true);
    output.close();
    return codeStr;
}

//
// This function completes the entire decompression process.  Given the file,
// filename (which should end with ".huf"), (1) extract the header and build
// the frequency map; (2) build an encoding tree from the frequency map; (3)
// using the encoding tree to decode the file.  This function should create a
// compressed file using the following convention.
// If filename = "example.txt.huf", then the uncompressed file should be named
// "example_unc.txt".  The function should return a string version of the
// uncompressed file.  Note this function should reverse what the compress
// function did.
//
string decompress(string filename) {
    hashmapF frecMap;  // This will store the frequncy map.
    HuffmanNode *encTree = nullptr;

    // Take the filename.txt.huf
    ifbitstream input(filename);
    size_t pos = filename.find(".huf");
    if ((int)pos >= 0) {
        filename = filename.substr(0, pos);
    }
    pos = filename.find(".");
    string ext = filename.substr(pos, filename.length() - pos);
    filename = filename.substr(0, pos);
    // Take out everything but the filename itself
    // Modified from the main.cpp

    ofstream output(filename + "_unc" + ext);
    // Now the output file is filename_unc.txt

    input >> frecMap;
    // Extract the header and put it in to the frecquency map.
    encTree = buildEncodingTree(frecMap);
    // Build the encoding tree using the freq. map
    string decodeStr = decode(input, encTree, output);
    // Just like the opposite of the compress.
    freeTree(encTree);
    output.close();
    return decodeStr;
}
