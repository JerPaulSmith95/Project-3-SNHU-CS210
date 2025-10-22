#pragma once
#ifndef ITEM_SEARCH_H
#define ITEM_SEARCH_H

#include <string>

using namespace std;

class ItemSearch {												// Constructing the header class, primarily used in menu option 1
public:
	void SetUserItem(string userItemChoice);					// Setter for the item name
	void SetItemNum(int groceryItemNum);						// Setter for the item number
	string GetUserItem();										// Getter for the item name
	int GetItemNum();											// Getter for the item number

private:
	string userItem;											// Variable for the item name
	int itemNum;												// Variable for the item number
};


#endif
