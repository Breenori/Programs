#include<iostream>
using std::cout;
using std::cin;

void main() 
{
	cout << "Bitte geben Sie eine Zahl ein:";
	int in(0);
	cin >> in;

	int out(in);
	/*
	for (int i = 2; i <= 9; i++)
	{
		cout << out << " * " << i << " = ";
		out *= i;
		cout << out << std::endl;
	}

	for (int i = 2; i <= 9; i++)
	{
		cout << out << " / " << i << " = ";
		out /= i;
		cout << out << std::endl;
	}*/

	for (int i = 2; i <= 18; i++)
	{
		if (i <= 9)
		{
			cout << out << " * " << i << " = ";
			out *= i;
		}
		else if( i > 10)
		{
			cout << out << " / " << (i-9) << " = ";
			out /= (i-9);
		}

		if(i != 10)
			cout << out << std::endl;
	}
}