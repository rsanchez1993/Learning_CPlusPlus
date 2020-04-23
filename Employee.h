#include<iostream>
#include<string>
#include "List.h"

using namespace std;

template<typename T>
void cinNbr(T& var) // enter a number from keyboard
{
	cin >> var;
	while (cin.fail() || cin.get() != '\n') // if error encountered
	{
		cout << "Invalid entry! Please re-enter value: ";
		cin.clear(); // clears any error flag
		cin.ignore(80, '\n'); // clears input buffer
		cin >> var;
	}
	cin.clear();
}

class Employee{
private:
	char name[50];
	int id;
	double salary;

public:
	void displayItems(const List<Employee>&);			//1
	void addItems(List<Employee>&);						//2
	void searchItem(const List<Employee>&);				//3
	void removeItem(List<Employee>&);					//4
};

//Option 1 
void Employee::displayItems(const List<Employee>& doubles){
	if (doubles.size() == 0)
		cout << "There is nothing in the list!"<<endl;
	else if (doubles.size() > 100)
	{
		cout << "List too long to be displayed!n";
		cout << "List size: " << doubles.size() << endl << endl;
	}
	else
	{
		cout << "Here are the contents:\n";
		for (List<Employee>::const_iterator iLoc = doubles.begin(); iLoc != doubles.end(); iLoc++)
		{
			cout << "name: " << (*iLoc).name << " ID:" << (*iLoc).id << " Salary:" << (*iLoc).salary <<endl;
		
		}
		cout << "List size: " << doubles.size() << endl << endl;
	}
}

//Option 2
void Employee::addItems(List<Employee>& doubles)
{
	cout << "Press 'n' when you are done:\n";
	Employee itemInput;
	char choice;
	while (true) // while valid double is entered
	{
		cout << "Enter name: ";
		cin.getline(itemInput.name,50);

		cout << "Enter ID: ";
		cinNbr(itemInput.id);

		cout << "Salary: ";
		cinNbr(itemInput.salary);

		if (cin.fail() == false)
		{
			doubles.push_back(itemInput);
		}
		else
		{
			cin.clear(); // clear and ignore bad input
			cin.ignore(80, 'n');
			break; // invalid input
		}
		//Anothe one?
		cout << "Enter another employee (y/n)? ";
		cinNbr(choice);
		if (choice == 'n')
		{
			break;
		}
	}
}

//option 3
void Employee::searchItem(const List<Employee>& doubles)
{
	if (doubles.size() == 0)
		cout << "\nList Empty!\n";
	else
	{
		int itemInput;
		cinNbr(itemInput);
		size_t index = 0;
		List<Employee>::const_iterator iLoc = doubles.begin();
		while (iLoc != doubles.end())
		{
			if ((*iLoc).id == itemInput)
			{
				//User enter employee search
				cout << "Name: " << (*iLoc).name << " ID:" << (*iLoc).id << " Salary:" << (*iLoc).salary << endl;
				cout << " found at node # " << (index+1) << endl;
				break;
			}
			index++;
			iLoc++;
		}
		if (iLoc == doubles.end())
			cout << "Value " << itemInput << " not found!\n";
	}
}

//Option 4
void Employee:: removeItem(List<Employee>& doubles)
{
	if (doubles.size() == 0)
		cout << "\nList Empty!\n";
	else
	{
		int itemInput;
		cinNbr(itemInput);
		size_t index = 0;
		List<Employee>::iterator iLoc = doubles.begin();
		while (iLoc != doubles.end())
		{
			if ((*iLoc).id == itemInput)
			{
				//User removes choice of employee
				cout << "Name: " << (*iLoc).name << " ID:" << (*iLoc).id << " Salary:" << (*iLoc).salary << endl;
				cout << " removed  at node # " << (index+1) << endl;
				doubles.erase(iLoc);
				break;
			}
			index++;
			iLoc++;
		}//not there
		if (iLoc == doubles.end())
			cout << "Value " << itemInput << " not found!\n";
	}
}