// FILE: AVLtree.h
#ifndef AVL_H // multiple inclusion guard
#define AVL_H

#include <iostream>
#include <vector>
#include <windows.h>
#include <iomanip>
using namespace std;

// Global variables:
const size_t MAX_COUNT = 1000000; // for execution time limitations only
const size_t MAX_DISPLAY = 80;
size_t ctrElements; // counter actual elements

struct AvlNode
{
	int      data;
	AvlNode* Left;
	AvlNode* Right;
	int      Height;
};


typedef struct AvlNode* Position;
typedef struct AvlNode* AvlTree;

AvlTree ClearTree(AvlTree T) // AvlTree "constructor & destructor"
{
	if (T != NULL)
	{
		ClearTree(T->Left);
		ClearTree(T->Right);
		delete T; // release memory
	}
	return NULL;
}

Position Find(const int X, const AvlTree T, int& calls)
{
	calls++;
	if (T == NULL)
		return NULL;
	if (X < T->data)
		return Find(X, T->Left, calls);
	else
	if (X > T->data)
		return Find(X, T->Right, calls);
	else
		return T;
}

Position FindMin(const AvlTree T)
{
	if (T == NULL)
		return NULL;
	else
	if (T->Left == NULL)
		return T;
	else
		return FindMin(T->Left);
}

Position FindMax(AvlTree T)
{
	if (T != NULL)
	while (T->Right != NULL)
		T = T->Right;
	return T;
}

int Retrieve(const Position P)
{
	return P->data;
}

static int Height(const Position P)
{
	if (P == NULL)
		return -1;
	else
		return P->Height;
}

static int Max(const int Lhs, const int Rhs)
{
	return Lhs > Rhs ? Lhs : Rhs;
}

/* This function can be called only if K2 has a left child */
/* Perform a rotate between a node (K2) and its left child */
/* Update heights */
//static Position SingleRotateRight( Position K2 )
void SingleRotateRight(Position& K2)
{
	Position K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;

	K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1; // max of K2
	K1->Height = Max(Height(K1->Left), K2->Height) + 1; // max of K1 left & K2

	K2 = K1;
}

/* This function can be called only if K1 has a right child */
/* Perform a rotate between a node (K1) and its right child */
/* Update heights */
//static Position SingleRotateLeft( Position & K1 )
void SingleRotateLeft(Position& K1)
{
	Position K2 = K1->Right;
	K1->Right = K2->Left;
	K2->Left = K1;

	K1->Height = Max(Height(K1->Left), Height(K1->Right)) + 1; // max of K1
	K2->Height = Max(Height(K2->Right), K1->Height) + 1; // max of K1 & K2 right

	K1 = K2;
}

/* This function can be called only if K3 has a left */
/* child and K3's left child has a right child */
/* Do the left-right double rotation */
/* Update heights */
void DoubleRotateLeftRight(Position& K3)
{
	/* Rotate between K1 and K2 */
	SingleRotateLeft(K3->Left);

	/* Rotate between K3 and K2 */
	SingleRotateRight(K3);
}

/* This function can be called only if K1 has a right */
/* child and K1's right child has a left child */
/* Do the right-left double rotation */
/* Update heights */
void DoubleRotateRightLeft(Position& K1)
{
	/* Rotate between K3 and K2 */
	SingleRotateRight(K1->Right);

	/* Rotate between K1 and K2 */
	SingleRotateLeft(K1);
}

void Balance(AvlTree& T)
{
	const int ALLOWED_INBALANCE = 1;

	if (T == NULL)
	{
		return;
	}
	if (Height(T->Left) - Height(T->Right) > ALLOWED_INBALANCE)
	{
		if (Height(T->Left->Left) >= Height(T->Left->Right))
			SingleRotateRight(T);
		else
			DoubleRotateLeftRight(T);
	}
	else if (Height(T->Right) - Height(T->Left) > ALLOWED_INBALANCE)
	{
		if (Height(T->Right->Right) >= Height(T->Right->Left))
			SingleRotateLeft(T);
		else
			DoubleRotateRightLeft(T);
	}
	T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
}

void AdjustHeights(AvlTree& T) // will move the nodes as high as possible
{
	if (T == NULL)
	{
		return;
	}
	if (T->Left != NULL) // next left node present
	{
		T->Left->Height = T->Height - 1;
		AdjustHeights(T->Left);
	}
	if (T->Right != NULL) // next right node present
	{
		T->Right->Height = T->Height - 1;
		AdjustHeights(T->Right);
	}
}

void Insert(const int X, AvlTree& T)
{
	if (T == NULL)
	{
		try // check if memory allocation OK
		{
			// Create and return a one-node tree on the freestore
			T = new AvlNode;
		}
		// if memory allocation failed:
		catch (...) // executes in case of exception (error)
		{
			cout << "Error encountered... quitting, sorry!\n";
			system("pause");
			exit(EXIT_FAILURE); // quit
		}

		T->data = X;
		T->Height = 0;
		T->Left = T->Right = NULL;
	}
	else if (X < T->data) // X less than T->data
		Insert(X, T->Left);
	else // X greater than or equal (duplicate) to T->data
		Insert(X, T->Right);
	Balance(T);
}

void inorder_print(const AvlTree p)
{
	static int i = 0; // count values to create lines of 40
	if (p != NULL)
	{
		// process the nodes in the left subtree:
		inorder_print(p->Left);

		// create lines of maximum 40 values:
		if (i % 40 == 0 && i != 0)
		{
			cout << endl;
			i = 0;
		}
		i++;

		// process the root:
		cout << setw(3) << Retrieve(p) << " ";

		// process the nodes in the right subtree:
		inorder_print(p->Right);
	}
}


#endif

