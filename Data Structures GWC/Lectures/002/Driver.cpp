// FILE: Driver.cpp
#include <iostream>
#include "List.h"
using namespace std;

template <typename T>
void cinNbr(T&); // enter a number from keyboard

void displayItems(const List<double>&);
void addItems(List<double>&);
void searchItem(const List<double>&);
void removeItem(List<double>&);
void removeCopies(List<double>&);

int main()
{
	List<double> l1;
	int menuChoice = 0;
	bool quit = false;
	while (!quit)
	{
		system("cls"); // clears the console screen
		cout << "1. Show List contents\n";
		cout << "2. Add item(s) to the List\n";
		cout << "3. Search for an item in the List\n";
		cout << "4. Withdraw single item from the List\n";
		cout << "5. Withdraw all copies of an item from the List\n";
		cout << "6. Exit the program\n\n";
		cout << "What would you like to do? Select a number (1 - 6), then press Enter: ";
		cinNbr(menuChoice);
		switch (menuChoice)
		{
		case 1:
			displayItems(l1);
			system("pause"); // causes program to pause until user hits a key
			break;
		case 2:
			cout << endl << "You chose to add value(s) to the List.\n";
			cout << "Type the double(s) that will be stored,\n";
			addItems(l1);
			system("pause"); // causes program to pause until user hits a key
			break;
		case 3:
			cout << endl << "You chose to search for a value in the List.\n";
			cout << "Type the double to be searched:\n";
			searchItem(l1);
			system("pause"); // causes program to pause until user hits a key
			break;
		case 4:
			cout << endl << "You chose to remove a value from the List,\n";
			cout << "Type the double to be removed:\n";
			removeItem(l1);
			system("pause"); // causes program to pause until user hits a key
			break;
		case 5:
			cout << endl << "You chose to remove all copies of a value from the List,\n";
			cout << "Type the double to be completely removed:\n";
			removeCopies(l1);
			system("pause"); // causes program to pause until user hits a key
			break;
		case 6:
			quit = true;
			cout << endl;
			break;
		default:
			cout << endl << "Invalid menu choice. Please try again.\n\n";
			system("pause"); // causes program to pause until user hits a key
		}
	}
	cout << "Closing...\n";
	return 0;
}

template<typename T>
void cinNbr(T& var) // enter a number from keyboard
{
	cin >> var;
	while (cin.fail() || cin.get() != '\n') // if error encountered
	{
		cout << "Invalid entry!  Please re-enter value: ";
		cin.clear(); // clears any error flag
		cin.ignore(80, '\n'); // clears input buffer
		cin >> var;
		}
	cin.clear();
}

void displayItems(const List<double>& doubles)
{
	if (doubles.size() == 0)
		cout << "List empty!\n";
	else if (doubles.size() > 100)
	{
		cout << "List too long to be displayed!\n";
		cout << "List size: " << doubles.size() << endl << endl;
	}
	else
	{
		cout << "Here are the contents:\n";
		for (List<double>::const_iterator iLoc = doubles.begin(); iLoc != doubles.end(); iLoc++)
			cout << (double)*iLoc << ", ";
		cout << "\b\b  \n"; // delete last space and comma
		cout << "List size: " << doubles.size() << endl << endl;
	}
}

void addItems(List<double>& doubles)
{
	cout << "Press \"q\" when you are done:\n";
	double itemInput;
	while (true) // while valid double is entered
	{
		cin >> itemInput;
		if (cin.fail() == false)
			doubles.push_back(itemInput);
		else
		{
			cin.clear(); // clear and ignore bad input
			cin.ignore(80, '\n');
			break; // invalid input
		}
	}
}

void searchItem(const List<double>& doubles)
{
	if (doubles.size() == 0)
		cout << "List empty!\n";
	else
	{
		double itemInput;
		cinNbr(itemInput);
		size_t index = 0;
		List<double>::const_iterator iLoc = doubles.begin();
		while (iLoc != doubles.end())
		{
			if (*iLoc == itemInput)
			{
				cout << "Value " << itemInput << " found at node # " << index << endl;
				break;
			}
			index++;
			iLoc++;
		}
		if (iLoc == doubles.end())
			cout << "Value " << itemInput << " not found!\n";
	}
}

void removeItem(List<double>& doubles)
{
	if (doubles.size() == 0)
		cout << "List empty!\n";
	else
	{
		double itemInput;
		cinNbr(itemInput);
		size_t index = 0;
		List<double>::iterator iLoc = doubles.begin();
		while (iLoc != doubles.end())
		{
			if (*iLoc == itemInput)
			{
				cout << "Value " << itemInput << " removed from node # " << index << endl;
				doubles.erase(iLoc);
				break;
			}
			index++;
			iLoc++;
		}
		if (iLoc == doubles.end())
			cout << "Value not found!\n";
	}
}

void removeCopies(List<double>& doubles)
{
	if (doubles.size() == 0)
		cout << "List empty!\n";
	else
	{
		double itemInput;
		cinNbr(itemInput);
		size_t index = 0;
		size_t nbrDeleted = 0;
		List<double>::iterator iLoc = doubles.begin();
		while (iLoc != doubles.end())
		{
			if (*iLoc == itemInput)
			{
				cout << "Value " << *iLoc << " removed from node # " << index << endl;
				iLoc = doubles.erase(iLoc);
				nbrDeleted++;
			}
			else
				iLoc++;
			index++;
		}
		if (nbrDeleted == 0)
			cout << "Value not found!\n";
	}
}
