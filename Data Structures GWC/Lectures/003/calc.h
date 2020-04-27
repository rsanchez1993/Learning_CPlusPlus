// FILE: calc.h
#include <iostream>
#include <stack> // Uses STL
#include <string> // Uses STL
using namespace std;

void evaluate_stack_tops(stack<double> & numbers, stack<char> & operations);

double read_and_evaluate(string line)
{
	const char RIGHT_PARENTHESIS = ')';
	stack<double> numbers; // local stack object
	stack<char> operations; // local stack object
	double number;
	char symbol;
	size_t position = 0;
	while (position < line.length())
	{
		if (isdigit(line[position]))
		{
number = line[position++] - '0'; // get value
			numbers.push(number);
		}
		else if (strchr("+-*/", line[position]) != NULL)
		{
			symbol = line[position++];
			operations.push(symbol);
		}
		else if (line[position] == RIGHT_PARENTHESIS && !operations.empty())
		{
			position++;
			evaluate_stack_tops(numbers, operations);
		}
		else
			position++;
	}
	if (!operations.empty())
		evaluate_stack_tops(numbers, operations);
	return numbers.top();
}

void evaluate_stack_tops(stack<double> & numbers, stack<char> & operations)
{
	double operand1, operand2;
	operand2 = numbers.top();
	numbers.pop();
	operand1 = numbers.top();
	numbers.pop();
	switch (operations.top())
	{
	case '+': numbers.push(operand1 + operand2); break;
	case '-': numbers.push(operand1 - operand2); break;
	case '*': numbers.push(operand1 * operand2); break;
	case '/': numbers.push(operand1 / operand2); break;
	}
	operations.pop();
}

