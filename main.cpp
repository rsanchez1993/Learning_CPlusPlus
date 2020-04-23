/*
	Written by Robby Sanchez
	Exercise 2: List of Employees
*/

//Main.cpp file
#include <iostream>
#include "Employee.h"	
using namespace std;

int main()
{
	List<Employee> l1;
	Employee employee;
	int menuChoice = 0;
	bool quit = false;
	while (!quit)
	{
		system("cls"); // clears the console screen
		cout << "1. Show list contents\n";
		cout << "2. Add information to the list\n";
		cout << "3. Search for an item in the list\n";
		cout << "4. Withdraw one information item from the list\n";
		cout << "5. Exit the programn\n";
		cout << "What would you like to do? Select a number (1 - 5), then press Enter: ";
		cinNbr(menuChoice);
		switch (menuChoice)
		{
		case 1:
			employee.displayItems(l1);
			system("pause"); // causes program to pause until user hits a key
			break;
		case 2:
			cout << endl << "You chose to add employee(s) to the list.\n";
			cout << "Enter the Employee(s) that will be stored\n";
			employee.addItems(l1);
			system("pause"); // causes program to pause until user hits a key
			break;
		case 3:
			cout << endl << "You chose the search for a employee in the list.\n";
			cout << "Type employee ID# to be searched:";
			employee.searchItem(l1);
			system("pause"); // causes program to pause until user hits a key
			break;
		case 4:
			cout << endl << "You chose to remove a employee from the list\n";
			cout << "Type employee ID # to be removed from list:";
			employee.removeItem(l1);
			system("pause"); // causes program to pause until user hits a key
			break;
		case 5:
			quit = true;
			cout <<"Good-Bye..."<< endl;
			break;
		default:
			cout << endl << "Invalid menu choice. Please try again.\n\n";
			system("pause"); // causes program to pause until user hits a key
		}
	}
	cout << "Press any key to continue...\n";
	return 0;
}

//Option 2
/*

1. Show list contents
2. Add information to the list
3. Search for an item in the list
4. Withdraw one information item from the list
5. Exit the programn
What would you like to do? Select a number (1 - 5), then press Enter:
2

You chose to add employee(s) to the list.
Enter the Employee(s) that will be stored
Press 'n' when you are done:
Enter name: Robby Sanchez
Enter ID: 100
Salary: 123
Enter another employee (y/n)? y
Enter name: John Smith
Enter ID: 102
Salary: 1234
Enter another employee (y/n)? y
Enter name: John Doe
Enter ID: 104
Salary: 12345
Enter another employee (y/n)? n
Press any key to continue . . .

*/

//Option 3
/*

1. Show list contents
2. Add information to the list
3. Search for an item in the list
4. Withdraw one information item from the list
5. Exit the programn
What would you like to do? Select a number (1 - 5), then press Enter: 3

You chose the search for a employee in the list.
Type employee ID# to be searched:101
Value 101 not found!
Press any key to continue . . .

*/

//Option 3

/*

1. Show list contents
2. Add information to the list
3. Search for an item in the list
4. Withdraw one information item from the list
5. Exit the programn
What would you like to do? Select a number (1 - 5), then press Enter: 3

You chose the search for a employee in the list.
Type employee ID# to be searched:100
Name: Robby Sanchez ID:100 Salary:123
 found at node # 1
Press any key to continue . . .

*/

//Option 4

/*
1. Show list contents
2. Add information to the list
3. Search for an item in the list
4. Withdraw one information item from the list
5. Exit the programn
What would you like to do? Select a number (1 - 5), then press Enter: 4

You chose to remove a employee from the list
Type employee ID # to be removed from list:100
Name: Robby Sanchez ID:100 Salary:123
 removed  at node # 1
Press any key to continue . . .

*/

//Option 1

/*
1. Show list contents
2. Add information to the list
3. Search for an item in the list
4. Withdraw one information item from the list
5. Exit the programn
What would you like to do? Select a number (1 - 5), then press Enter: 1
Here are the contents:
name: John Smith ID:102 Salary:1234
name: John Doe ID:104 Salary:12345
List size: 2

Press any key to continue . . .
*/



