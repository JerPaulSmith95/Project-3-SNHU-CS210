#include <iostream>
#include <string>
#include "ItemSearch.h"

using namespace std;

void ItemSearch::SetUserItem(string userItemChoice) {
	this->userItem = userItemChoice;
}

void ItemSearch::SetItemNum(int groceryItemNum) {
	this->itemNum = groceryItemNum;
}

string ItemSearch::GetUserItem() {
	return userItem;
}

int ItemSearch::GetItemNum() {
	return itemNum;
}