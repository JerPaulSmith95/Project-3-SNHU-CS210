#include <iostream>
#include <string>
#include <map>	
#include <iomanip>
#include <fstream>

#include "ItemSearch.h"

using namespace std;

void MenuOne(map<string, int>& groceryItemTracker) {																					// Function for menu option one, which is an item search function
	ItemSearch userSearch;
	string userInput;

	cout << "\n************ ITEM SEARCH ************" << endl;
	cout << "\nWhich item would you like to see?" << endl;																				// Header for the item search function
	cout << "To cancel your search, press 'q'" << endl;
	getline(cin, userInput);																											// Gets user input

	while (userInput != "q") {																											// "q" is assigned as the signal value to exit this part of the program

		userSearch.SetUserItem(userInput);
		if (groceryItemTracker.count(userInput) == 1) {																					// Check to see if the word that the user input was in the map, detecting a value of "1" if so and uses the setter to set the item name variable
			userSearch.SetItemNum(groceryItemTracker.at(userSearch.GetUserItem()));														// Set the number of items sold of the item that matches user input using the setter
			cout << "\nThere were " << userSearch.GetItemNum() << " " << userSearch.GetUserItem() << " sold today." << endl;			// Gets the item name from the name set and gets the item num from the number set and displays the information to the user
			cout << "What else would you like to search for?\n" << endl;
			getline(cin, userInput);
		}

		else if (groceryItemTracker.count(userInput) == 0) {
			cout << "\nSorry, there were no items of that type." << endl;																// "Error" message that display if the word that the user inputs was not in the list
			cout << "Would you like to search for something else?\n" << endl;															// Prompts user for next input
			getline(cin, userInput);
		}
	}
}

static void MenuTwo(map<string, int>& groceryItemTracker) {										// Function for menu option two, which diplays the full list of items and their counts

	cout << "\n\n********** ITEM LIST ************\n" << endl;									// Header for the list
	for (const auto& pair : groceryItemTracker) {
		cout << left << setw(15) << pair.first << right << pair.second << endl;					// For loop that goes through each item in the map and displays their counts
	}
	cout << "\n" << endl;																		// Padding for extra spaces to improve readability
}

static void MenuThree(map<string, int>& groceryItemTracker) {									// Function for menu option three, that displays a similar list to menu option two but instead shows a histogram for the items and their counts

	cout << "\n********** HISTOGRAM ************\n" << endl;									// Header for the histogram list
	for (const auto& pair : groceryItemTracker) {												// For loop that goes through each item in the list
		cout << left << setw(15) << pair.first;												
		for (int i = 1; i <= pair.second; ++i) {												// Nested for loop that displays one "[]" character for every item that was sold of that type
			cout << "[]";																		// "Character used in the histogram
		}	
		cout << "\n" << endl;																	// Padding for extra space to improve readability
	}
}

static void MenuDisplay() {																		
	cout << "\n********** Main Menu **********\n" << endl;
	cout << "1 --- Find Item and Quantity" << endl;
	cout << "2 --- Display Full Item List" << endl;												// Menu display function that will be shown to give the user their list of options
	cout << "3 --- Display Histogram Chart" << endl;
	cout << "4 --- Exit Program\n" << endl;
	cout << "*******************************\n" << endl;
}

void FileCreation(map<string, int>& groceryItemTracker) {										// File Creation function that will run before the program begins and creates the data backup file
	ofstream outFS;
	outFS.open("frequency.dat");																// Creates the new file

	if (!outFS.is_open()) {
		cout << "frequency.dat coudl not be opened" << endl;									// Checks to see if the file could be opened correctly
		return;
	}

	else {
		for (const auto& pair : groceryItemTracker) {
			outFS << left << setw(15) << pair.first << right << pair.second << endl;			// Displays the same list in the new file that would be seen if the user entered menu option two
		}
	}
}

int main() {
	map<string, int> groceryItemTracker;											// Declaration of the map that will be used
	string itemName;																// Declaration of the string varibale that will be used to get the name of the item in the file
	ifstream inFS;																	// Input stream variable declaration
	string userChoice;																// Varibale for reading the user's choice from the menu options

	inFS.open("CS210_Project_Three_Input_File.txt");								// Opens the .txt file

	while (!inFS.eof() && inFS.good()) {											// While statement that creates the map "groceryItemTracker" that will be used throughout the program
		getline(inFS, itemName);													// Gets the word from the line in the text file

		if (groceryItemTracker.count(itemName) == 0) {								// Checks to see if the word already exists in the map, returning 0 if it does not
			groceryItemTracker.emplace(itemName, 1);								// Emplaces the word into the map with a value (count) of 1 if it is not in the map already
		}

		else if (groceryItemTracker.count(itemName) == 1) {							// If the word is already in the map, returning a value of 1, then
			groceryItemTracker.at(itemName) += 1;									// updates the value associated with the key to add one onto it
		}
	}
	
	FileCreation(groceryItemTracker);												// Calling on the FileCreation function that will use the map to create a simple file with the items and their frequencies
	MenuDisplay();																	// Displays the menu on program start

	getline(cin, userChoice);														// Gets the first user input, with getline serving as one part of the input validation

	while (userChoice != "4") {														// Runs this loop while the user input is not "4"

		if (userChoice == "1") {													// On user input of "1", will open up the search function
			MenuOne(groceryItemTracker);
		}
		else if (userChoice == "2") {												// On user input of "2", will display the full list of items and their associated counts
			MenuTwo(groceryItemTracker);
		}

		else if (userChoice == "3") {												// On user input of "3", will display the histogram of items and their counts
			MenuThree(groceryItemTracker);
		}
			
		else {																		// Input validation
			cout << "Invalid Input..." << endl;
		}
							
		MenuDisplay();																// Displays menu again, showing user the options
		getline(cin, userChoice);													// Gets next user input

	}
}

