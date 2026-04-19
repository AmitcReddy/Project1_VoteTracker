/*
Title: Proj1.cpp
Author: Amit Reddy
Date: 9/17/2025
Description: This program reads a list of votes from an input file, where each vote is represented by a
candidate's full name. It tallies the number of votes for each candidate, stores the results using parallel arrays, 
and displays both the total votes per candidate and a histogram using asterisks for visual representation.
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Prototypes 
string getFileName();
int    loadVotes(ifstream &inFile, string candidates[], int counts[]);
int    findCandidateIndex(string candidates[], int numCandidates, string name);
void   printVoteCounts(string candidates[], int counts[], int numCandidates);
void   printHistogram(string candidates[], int counts[], int numCandidates);
string toLower(string s);
string toTitle(string s);

//Main-Manages the program by calling functions in order
int main() {
    // 1) Ask for file name
    string filename = getFileName();

    // 2) Try to open file
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Failed to open vote file." << endl;
        return 0;
    }

    // 3) Prepare arrays to hold candidates and counts
    const int MAX_CANDIDATES = 5;
    string candidates[MAX_CANDIDATES];
    int counts[MAX_CANDIDATES];

    for (int i = 0; i < MAX_CANDIDATES; i++) {
        counts[i] = 0;
        candidates[i] = "";
    }

    // 4) Load votes and close file
    int numCandidates = loadVotes(inFile, candidates, counts);
    inFile.close();

    // 5) Print outputs
    printVoteCounts(candidates, counts, numCandidates);
    cout << endl;
    printHistogram(candidates, counts, numCandidates);

    return 0;
}

//This function opens the file and reads in each vote. It updates an array keeping track of the votes.  
int loadVotes(ifstream &inFile, string candidates[], int counts[]) {
    string name;
    int numCandidates = 0;

    bool keepReading = true;
    //do while loop to read each vote and update tallies
    do {
        if (!getline(inFile, name)) {
            keepReading = false; 
        } else {
            if (name.length() > 0) {
                name = toTitle(name); 

                int index = findCandidateIndex(candidates, numCandidates, name);
                if (index != -1) {
                    counts[index]++;
                } else {
                    candidates[numCandidates] = name;
                    counts[numCandidates] = 1;
                    numCandidates++;
                }
            }
        }
    } while (keepReading);

    return numCandidates;
}

//Iterates through the array of candidates and returns the index of where in the array that item exists
int findCandidateIndex(string candidates[], int numCandidates, string name) {
    for (int i = 0; i < numCandidates; i++) {
        if (candidates[i] == name) {
            return i;
        }
    }
    return -1;
}

//Prints the count for each of the candidates
void printVoteCounts(string candidates[], int counts[], int numCandidates) {
    cout << "Vote Counts:" << endl;
    for (int i = 0; i < numCandidates; i++) {
        cout << "   " << candidates[i] << ": " << counts[i] << endl;
    }
}

//Prints the count for each candidate as a histogram using asterisks
void printHistogram(string candidates[], int counts[], int numCandidates) {
    cout << "Histogram:" << endl;
    for (int i = 0; i < numCandidates; i++) {
        cout << "   " << candidates[i] << ": ";
        for (int j = 0; j < counts[i]; j++) {
            cout << "*";
        }
        cout << endl;
    }
}

//Converts the name of the candidate to be all lowercase
string toLower(string s) {
    int n = s.length();
    for (int i = 0; i < n; i++) {
        char c = s[i];
        if (c >= 'A' && c <= 'Z') {
            s[i] = char(c - 'A' + 'a');
        }
    }
    return s;
}

//Converts the name of the candidate to be title case
string toTitle(string s) {
    int n = s.length();
    for (int i = 0; i < n; i++) {
        char c = s[i];
        if (c >= 'A' && c <= 'Z') {
            s[i] = char(c - 'A' + 'a');
        }
    }
    bool newWord = true;
    for (int i = 0; i < n; i++) {
        char c = s[i];
        if (c == ' ') {
            newWord = true;
        } else if (newWord) {
            if (c >= 'a' && c <= 'z') {
                s[i] = char(c - 'a' + 'A');
            }
            newWord = false;
        }
    }
    return s;
}

//Asks the user for the name of the file to load
string getFileName() {
    string filename;
    cout << "What is the name of the file?" << endl;
    cin >> filename;
    return filename;
}