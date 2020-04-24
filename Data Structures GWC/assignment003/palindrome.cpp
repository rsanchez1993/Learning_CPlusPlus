#include<iostream>
#include<cstring>		// comparing strings
#include<stack>			// provides STL stack
#include<queue>			// provides STL queue
#include<cstdlib>		// for exit() function cause program termination
#include<string>		// Use for string objects
using namespace std;

int main() {
	stack<char> palinStack;	//local stack object
	queue<char> palinQueue;	// STL queue holding plain(input of first text)
	std::string line;
	std::string newStr = "";
	int nochar = 0;
	//Use at least one iterator to traverse the input string:
	string::iterator inPtr;
	int choice = 0;
	bool isPalin = true;
	
	//Menu
	while (true) {
		cout << "1. Enter new string\n";
		cout << "2. Test string\n";
		cout << "3. Exit\n";
		cout << "Please enter your menu choice ( 1 - 3 ): \n";
		cin >> choice;
		//1
		if (choice == 1) {
			newStr = "";
			nochar = 0;
			cin.ignore();
			cout << "\nEnter string to be tested : " << endl;
			getline(cin, line);
			//Allows user to enter string
			for (inPtr = line.begin(); inPtr != line.end(); inPtr++) {
				if(isalpha(*inPtr)) {
					char changeUpper = toupper(*inPtr);
					newStr += changeUpper;
					palinQueue.push(changeUpper);
					palinStack.push(changeUpper);
					nochar++;
				}
			}
			cout << "Here is the filtered input: " << newStr << endl;

			//2
		} else if (choice == 2) {
			if (newStr != "") {
				isPalin = true;
				/****Check text is a palindrome or not****/
				while(nochar--) {
					char stackValue = palinStack.top();
					palinStack.pop();
					char queueValue = palinQueue.front();
					palinQueue.pop();
					if (stackValue != queueValue) {
						isPalin = false;
					}
				}
				//if,else statement if palindrome or not
				if (isPalin) {
					cout << newStr << " ... IS a palindrome!! GOOD JOB!!\n"
							<< endl;
					isPalin = false;
				} else {
					cout << newStr << " ... is NOT a palindrome\n" << endl;
					isPalin = false;

				}
			} else {
				cout << "\nTest for palindrome"<< endl;
				cout << "Please enter a STRING!!!\n" << endl;
			}
			//3
		} else if (choice == 3) {
			cout << "GOODBYE!!" << endl;
			exit(0);
		}
	}
	return 0;
}

//     *********My Output*************
/*
1. Enter new string
2. Test string
3. Exit
Please enter your menu choice ( 1 - 3 ):
2

Test for palindrome
Please enter a STRING!!!

1. Enter new string
2. Test string
3. Exit
Please enter your menu choice ( 1 - 3 ):
2

Test for palindrome
Please enter a STRING!!!

1. Enter new string
2. Test string
3. Exit
Please enter your menu choice ( 1 - 3 ):
1

Enter string to be tested :
dog 1 rer god
Here is the filtered input: DOGRERGOD
1. Enter new string
2. Test string
3. Exit
Please enter your menu choice ( 1 - 3 ):
*/