// Written by Robby Sanchez
// GS 189 Assignment 4
// Counting Nodes on an AVL Tree

// FILE: Driver.cpp
#include "AVLtree.h"

// FUNCTION PROTOTYPES:

// enter a number from keyboard (templatized for numeric types):
template <typename T>
void cinNbr(T&);

// function to setup console window:
void SetWindow(const int Width, const int Height);

// Retrieve the data from AvlTree in a two-dimensional vector.
// Only used with small amount of data:
void Generate_Display(AvlTree T, vector< vector<int> > & Display, const int nbrLines, const int nbrColumns);

// Display tree containing small amount of data:
void display(const AvlTree T);

//the 3 non-member functions
//Count Nodes
int countNodes(const AvlTree & T, int & ctrNodesParam, int & ctrCallsParam);
//Count leaf nodes
int countLeaves(const AvlTree & T, int & ctrNodesParam, int & ctrCallsParam);
//Count Full nodes in AVL Tree
int countFullNodes(const AvlTree & T, int & ctrNodesParam, int & ctrCallsParam);

int main()
{
	HWND consoleWindow = GetConsoleWindow(); // set the console position at 0 , 50
	SetWindowPos(consoleWindow, 0, 0, 50, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	const int ConsoleWidth = 205;
	const int ConsoleHeight = 50;
	SetWindow(ConsoleWidth, ConsoleHeight); //This sets the size of the console

	AvlTree T;
	T = ClearTree(NULL); // set T to NULL
	cout << "Enter the original number of elements to be stored (1 to "
		<< MAX_COUNT << ", display tree with up to " << MAX_DISPLAY << "): ";
	cinNbr(ctrElements);
	size_t max_var;
	if (ctrElements > MAX_COUNT)
		ctrElements = MAX_COUNT;
	if (ctrElements <= MAX_DISPLAY)
		max_var = MAX_DISPLAY; // for display limitations only;
	else
		max_var = MAX_COUNT;

	int* Numbers; // pointer to dynamic array
	try // check if memory allocation OK
	{
		Numbers = new int[ctrElements];
	}
	// if memory allocation failed:
	catch (...) // executes in case of exception (error)
	{
		cout << "Error encountered... quitting, sorry!\n";
		system("pause");
		exit(EXIT_FAILURE); // quit
	}

	// ******** experiment with the 2 different ways to populate the tree *******
	// by commenting or uncommenting the statement below:
	//#define ASCENDING

#ifdef ASCENDING
	// populate complete AVL tree at once (ascending)
	for (size_t i = 0; i < ctrElements; i++) // create array of numbers
		Numbers[i] = i + 1;
#else
	// by selecting an original number of elements = 16 and no additional values,
	// the following sequences recreate the example from our textbook:
	// populate lower half of AVL tree (ascending)
	for (size_t i = 0; i < (ctrElements - 1) / 2; i++)
		Numbers[i] = i + 1;
	// populate higher half of AVL tree (descending)
	for (size_t j = (ctrElements - 1) / 2; j < ctrElements; j++)
		Numbers[j] = ctrElements + (((ctrElements - 1) / 2) - j);
#endif
	// **************************************************************************

	if (ctrElements <= MAX_DISPLAY)
	{
		cout << "Original values:\n";
		for (size_t i = 0; i < ctrElements; i++) // display numbers
		{
			cout.fill(' ');
			if (i % 40 == 0 && i != 0)
				cout << endl;
			cout << setw(3) << Numbers[i] << " ";
		}
		cout << endl;
	}

	// populate AVL tree:
	for (size_t ctr = 0; ctr < ctrElements; ctr++)
		Insert(Numbers[ctr], T);

	if (ctrElements < max_var) // add more values?
	{
		if (max_var <= MAX_DISPLAY)
			cout << "\nInsert more integers (between -99 and 99 for display limitations)?\n";
		else
			cout << "\nInsert more integers (between " << MININT << " and " << MAXINT << ")?\n";
		cout << "Separate entries by a space, \"c\" to continue: ";
		int val = 0;
		while (ctrElements < max_var) // and while valid integer is entered
		{
			cin >> val;
			if (cin.fail() == false)
			{
				Insert(val, T);
				ctrElements++;
			}
			else
				break; // invalid input
		}
		cin.clear(); // clear and ignore bad input
		cin.ignore(80, '\n');
	} // end of adding more values

	if (ctrElements >= max_var)
		cout << "\nMaximum of " << max_var << " values has been reached!\n";

	if (max_var <= MAX_DISPLAY)
	{
		cout << "\nFinal values stored on tree:\n";
		inorder_print(T);
		cout << endl;
	}

	display(T); // display statistics and tree if not too large

	Position found = NULL;
	int calls = 0;
	cout << "Enter a value to be searched: ";
	int target; // experiment with different cases
	cinNbr(target);

	found = Find(target, T, calls);
	if (found != NULL)
		cout << target << " found at Height " << found->Height << endl;
	else
		cout << target << " not found\n";
	double log2 = log10(ctrElements) / log10(2); // convert to log base 2
	cout << "AVL Tree, number of elements (n): " << ctrElements << "    calls: " << calls <<
		"    log base 2 of n: " << log2 << endl << endl;

	//code at end of main() to call the functions
	cout << "ASSIGNMENT 5:\n";
	int ctrNodes = 0, ctrCalls = 0;
	cout << "Counting nodes result: " << countNodes(T, ctrNodes, ctrCalls);
	cout << ", Nbr of calls: " << ctrCalls << endl;
	ctrNodes = 0, ctrCalls = 0;
	cout << "Counting leaves result: " << countLeaves(T, ctrNodes, ctrCalls);
	cout << ", Nbr of calls: " << ctrCalls << endl;
	ctrNodes = 0, ctrCalls = 0;
	cout << "Counting full nodes result: " << countFullNodes(T, ctrNodes, ctrCalls);
	cout << ", Nbr of calls: " << ctrCalls << endl << endl;

	delete[] Numbers; // release array from the freestore
	ClearTree(T); // release memory on the freestore and set T to NULL
	system("pause");
	return 0;
}

// enter a number from keyboard (templatized for numeric types):
template<typename T>
void cinNbr(T& var)
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

// function to setup console window:
void SetWindow(const int Width, const int Height)
{
	_COORD coord;
	coord.X = Width;
	coord.Y = Height;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle
	SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size
	SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size
}

// Retrieve the data from AvlTree in a two-dimensional vector.
// Only used with small amount of data:
void Generate_Display(AvlTree T, vector< vector<int> > & Display, const int nbrLines, const int nbrColumns)
{
	AdjustHeights(T); // will move the nodes as high as possible
	static int ColumnCtr[7] = { 0 }; // keep track of last value for each line (max. 7 lines)
	if (T != NULL)
	{
		int line = nbrLines - T->Height - 1;
		int increment = nbrColumns / (int)pow(2, line); // 64 for line 0, 2 for lines 5 & 6
		int nextIndex = (increment / 2) + (ColumnCtr[line]++ * increment);
		if (nextIndex < nbrColumns)
			Display[line][nextIndex] = (T->data); // save data on corresponding line

		if (T->Left != NULL) // next left node present
			Generate_Display(T->Left, Display, nbrLines, nbrColumns);
		else if (line < nbrLines - 1) // save empty (9999) on left children if applicable
		{
			int tmpIncrement = increment / 2;
			int tmpLine = line + 1;
			int tmpIndex = (tmpIncrement / 2) + (ColumnCtr[tmpLine]++ * tmpIncrement);
			if (tmpIndex < nbrColumns)
				Display[tmpLine][tmpIndex] = 9999; // save empty (9999) on left
			if (tmpLine < nbrLines - 1)
			{
				tmpLine++;
				tmpIncrement /= 2; // 64 for line 0, 1 for line 6
				tmpIndex = (tmpIncrement / 2) + (ColumnCtr[tmpLine]++ * tmpIncrement);
				if (tmpIndex < nbrColumns)
					Display[tmpLine][tmpIndex] = 9999; // save empty (9999) on left
				tmpIndex = (tmpIncrement / 2) + (ColumnCtr[tmpLine]++ * tmpIncrement);
				if (tmpIndex < nbrColumns)
					Display[tmpLine][tmpIndex] = 9999; // save empty (9999) on right
			}
		}

		if (T->Right != NULL) // next right node present
			Generate_Display(T->Right, Display, nbrLines, nbrColumns);
		else if (line < nbrLines - 1) // save empty (9999) on right children if applicable
		{
			int tmpIncrement = increment / 2;
			int tmpLine = line + 1;
			int tmpIndex = (tmpIncrement / 2) + (ColumnCtr[tmpLine]++ * tmpIncrement);
			if (tmpIndex < nbrColumns)
				Display[tmpLine][tmpIndex] = 9999; // save empty (9999) on right
			if (tmpLine < nbrLines - 1)
			{
				tmpLine++;
				tmpIncrement /= 2; // 64 for line 0, 1 for line 6
				tmpIndex = (tmpIncrement / 2) + (ColumnCtr[tmpLine]++ * tmpIncrement);
				if (tmpIndex < nbrColumns)
					Display[tmpLine][tmpIndex] = 9999; // save empty (9999) on left
				tmpIndex = (tmpIncrement / 2) + (ColumnCtr[tmpLine]++ * tmpIncrement);
				if (tmpIndex < nbrColumns)
					Display[tmpLine][tmpIndex] = 9999; // save empty (9999) on right
			}
		}
	}
}

// Display tree containing small amount of data:
void display(const AvlTree T)
{
	int min = Retrieve(FindMin(T));
	cout << "\nMin is " << min << "   ";
	int max = Retrieve(FindMax(T));
	cout << "Max is " << max << endl;
	cout << "Total number of values is " << ctrElements << endl << endl;

	// only used with small amount of data:
	if (ctrElements <= MAX_DISPLAY)
	{
		const int nbrLines = (T->Height) + 1;
		const int nbrColumns = 64;
		// vector of vectors of int with value set to empty (9999):
		vector< vector<int> > Display(nbrLines, vector<int>(nbrColumns, 9999));
		Generate_Display(T, Display, nbrLines, nbrColumns);
		HANDLE console_handle;
		console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		int Current_Row = 20; // defines which line the display resumes
		int Current_Column = 0;
		COORD cursor_coord;
		cursor_coord.X = 0;
		cursor_coord.Y = Current_Row;

		for (int i = 0; i < nbrLines; i++)
		{
			Current_Row += 2;
			cursor_coord.Y = Current_Row;
			cursor_coord.X = 0;
			SetConsoleCursorPosition(console_handle, cursor_coord);
			cout << "Height " << nbrLines - 1 - i << ": ";
			if (i == nbrLines - 1) // last row
				cout << " ";
			for (int j = 0; j < nbrColumns; j++)
			{
				if (Display[i][j] == 9999) // empty element
					cout << "   ";
				else
					cout << setw(3) << setfill(' ') << Display[i][j];
			}
			cout << endl;
		}
		cout << "\n\n";

	
	}
}
/*Count nodes*/
int countNodes(const AvlTree & T, int & ctrNodesParam, int & ctrCallsParam)
{
	if (T == NULL){
		ctrNodesParam = ctrNodesParam + 1;

		return 0;
	}
	ctrCallsParam += 1;

	return 1 + countNodes(T->Left, ctrNodesParam, ctrCallsParam) + countNodes(T->Right, ctrNodesParam, ctrCallsParam);
}

/*Count leaves*/
int countLeaves(const AvlTree & T, int & ctrNodesParam, int & ctrCallsParam)
{
	if (T == NULL){
		return 0;
	}

	if (T->Left == NULL && T->Right == NULL)
	{
		ctrCallsParam++;
		ctrNodesParam += 1;
		return 0;
	}

	ctrCallsParam +=1;
	return 1 + countLeaves(T->Left, ctrNodesParam, ctrCallsParam) + countLeaves(T->Right, ctrNodesParam, ctrCallsParam);
}

/*Count number of full nodes are  present in avl tree*/
int countFullNodes(const AvlTree & T, int & ctrNodesParam, int & ctrCallsParam)
{
	/*Recursion Termination condition*/
	if (T == NULL){
		return 0;
	}
	
	/*Full nodes are those which have both node left child and right child*/
	if (T->Left != NULL && T->Right != NULL){
		ctrNodesParam += 1;
	}

	/*Process Left Node of AVL Tree*/
	countFullNodes(T->Left, ctrNodesParam, ctrCallsParam);
	ctrCallsParam +=1;
	/**Process Right Node of AVL Tree*/
	countFullNodes(T->Right, ctrNodesParam, ctrCallsParam);
	return ctrNodesParam;
}

//*********Ouput**********
/*
Enter the original number of elements to be stored (1 to 1000000, display tree with up to 80): 10
Original values:
  1   2   3   4  10   9   8   7   6   5

Insert more integers (between -99 and 99 for display limitations)?
Separate entries by a space, "c" to continue: c

Final values stored on tree:
  1   2   3   4   5   6   7   8   9  10

Min is 1   Max is 10
Total number of values is 10










Height 3:                                                                                                   4

Height 2:                                                   2                                                                                               7

Height 1:                           1                                               3                                               6                                               9

Height 0:                                                                                                                5                                               8                      10


Enter a value to be searched: 4
4 found at Height 3
AVL Tree, number of elements (n): 10    calls: 1    log base 2 of n: 3.32193

ASSIGNMENT 5:
Counting nodes result: 10, Nbr of calls: 10
Counting leaves result: 5, Nbr of calls: 10
Counting full nodes result: 4, Nbr of calls: 10

Press any key to continue . . .
*/