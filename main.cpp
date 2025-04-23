/******************************************************************************
 * Author: Brendan Arseneau
 * Project: CS 210 Project Three – Corner Grocer
 * Description: This program reads grocery item data from an input file,
 *              calculates how many times each item was purchased, and provides
 *              a menu for the user to:
 *              1. Search for a specific item's purchase frequency
 *              2. Display all item frequencies
 *              3. Display a histogram of item frequencies
 *              4. Exit the program
 *
 *              It also generates a frequency.dat file with the item counts.
 * Date: April 15 2025
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

// Function to load item frequencies from input file
map<string, int> loadFrequencies(const string& filename) {
    ifstream inFile(filename);
    map<string, int> freqMap;
    string item;

    // Read each word from file and count it occurrences
    while (inFile >> item) {
        freqMap[item]++;
    }

    inFile.close(); // Always close the file
    return freqMap;
}

// Function to write frequency data to a new file (frequency.dat)
void writeFrequenciesToFile(const map<string, int>& freqMap, const string& outFileName) {
    ofstream outFile(outFileName);

    // Write each item and frequency to the output file
    for (const auto& pair : freqMap) {
        outFile << pair.first << " " << pair.second << endl;
    }

    outFile.close();
}

// Option 1: Look up frequency of specific item
void itemFrequency(const map<string, int>& freqMap) {
    string searchItem;
    cout << "Enter the item name: ";
    cin >> searchItem;

    // Check if item exists in the map and display frequency
    if (freqMap.count(searchItem)) {
        cout << searchItem << ": " << freqMap.at(searchItem) << endl;
    }
    else {
        cout << searchItem << " not found." << endl;
    }
}

// Option 2: Display all items and frequencies
void displayAllFrequencies(const map<string, int>& freqMap) {
    cout << "\nItem Frequencies:\n";
    for (const auto& pair : freqMap) {
        cout << pair.first << ": " << pair.second << endl;
    }
}

// Option 3: Display histogram using asterisks
void displayHistogram(const map<string, int>& freqMap) {
    cout << "\nHistogram of Item Frequencies:\n";
    for (const auto& pair : freqMap) {
        cout << setw(12) << left << pair.first << " ";
        for (int i = 0; i < pair.second; ++i) {
            cout << "*";
        }
        cout << endl;
    }
}

int main() {
    // Input and output file names
    string inputFile = "CS210_Project_Three_Input_File.txt";
    string outputFile = "frequency.dat";

    // Load data from input file into map / save to frequency.dat
    map<string, int> freqMap = loadFrequencies(inputFile);
    writeFrequenciesToFile(freqMap, outputFile);

    int choice;

    // Main menu loop
    do {
        // Display menu
        cout << "\n--- Corner Grocer Item Tracker ---\n";
        cout << "1. Search item frequency\n";
        cout << "2. Display all item frequencies\n";
        cout << "3. Display histogram\n";
        cout << "4. Exit\n";
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        // Handle user input
        switch (choice) {
        case 1:
            itemFrequency(freqMap);
            break;
        case 2:
            displayAllFrequencies(freqMap);
            break;
        case 3:
            displayHistogram(freqMap);
            break;
        case 4:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid option. Try again.\n";
        }

    } while (choice != 4); // Loop until user chooses to exit

    return 0;
}