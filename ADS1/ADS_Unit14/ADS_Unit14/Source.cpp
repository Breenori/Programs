#include<iostream>
#include<string>
#include "stack_machine.h"
using namespace std;

// Removes all whitespaces from a given string
void remove_whitespaces(string& str);

void main()
{
	string expression;
	cout << "Please enter the expression to be evaluated:\n";
	getline(cin, expression);
	cout << "\n";

	remove_whitespaces(expression);

	cout << "Result: " << evaluate(expression);
}

void remove_whitespaces(string& str)
{
	while (str.find(' ', 0) != string::npos)
	{
		str.replace(str.find(' ', 0), 1, "");
	}
}